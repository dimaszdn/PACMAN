#include<Game.h>
#include<Global.h>

Ghost* Game::Factory(GhostType ghostType)
{
    Ghost* ghost = nullptr;
    switch (ghostType)
    {
        case GhostType::BLINKY:
            ghost = new Blinky(*m_window);
            ghost->settings();
            break;
        case GhostType::CLYDE:
            ghost = new Clyde(*m_window);
            ghost->settings();
            break;
        case GhostType::PINKY:
            ghost = new Pinky(*m_window);
            ghost->settings();
            break;
        case GhostType::INKY:
            ghost = new Inky(*m_window);
            ghost->settings();
            break;
    }
    if (ghost != nullptr)
        return ghost;
    throw std::logic_error("There is no such ghost!");
}


Game::Game() : winGame(0), lag(0), current_wave(0), wave_timer(256), LONG_DURATION(512),
SHORT_DURATION(256), next_status(0), playGame(0)
{

}

Game::~Game()
{
    if (m_window != nullptr)
        delete m_window;
}

void Game::Setup()
{
    m_window = new sf::RenderWindow(sf::VideoMode(MAP_WIDTH * CELL_SIZE * MAP_RESIZE, MAP_HEIGHT * CELL_SIZE * MAP_RESIZE), m_caption);
    m_window->setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, CELL_SIZE  * MAP_HEIGHT)));

    setPreview();
    m_preview.setScale(0.5f, 0.5f); //resolution image / 2
    m_preview.setTexture(preview_tex);

    previous_time = std::chrono::steady_clock::now();
}

void Game::setCaption(const std::string &str)
{
    m_caption = str;
}

void Game::GameLogic(std::vector<Ghost*> &ghosts, Pacman& pacman, Map& map)
{
    if (winGame == 0 && pacman.get_dead() == 0 && playGame == 1)
    {
        winGame = 1;

        pacman.update(map.getMap());

        if (wave_timer == 0)
        {
            if (current_wave < 7)
            {
                current_wave++;
                if (next_status == 0)
                {
                    for (auto ghost: ghosts)
                    {
                        ghost->set_status(STATUS::CHASE);
                    }
                    next_status = 1;
                }
                else
                {
                    for (auto ghost: ghosts)
                    {
                        ghost->set_status(STATUS::SCATTER);
                    }
                    next_status = 0;
                }
            }
            if (current_wave % 2 == 1)
            {
                wave_timer = 1024;
            }
            else if (current_wave == 2)
            {
                wave_timer = LONG_DURATION;
            }
            else
            {
                wave_timer = SHORT_DURATION;
            }
        }
        else
        {
            wave_timer--;
        }

        for (auto ghost : ghosts)
            ghost->update(map.getMap(), pacman, ghosts[0]->get_position());

        for (unsigned char y = 0; y < MAP_HEIGHT; ++y)
        {
            for (unsigned char x = 0; x < MAP_WIDTH; ++x)
            {
                if (map.getMap()[y][x] == CELL::GRANULES)
                {
                    winGame = 0;
                    break;
                }
            }
            if (winGame == 0)
                break;
        }
    }
}

void Game::Run()
{
    //GameBar
    GameBar gameOver(*m_window);
    gameOver.setStr("GAME OVER");
    gameOver.setup();

    GameBar gameWin(*m_window);
    gameWin.setStr("VICTORY");
    gameWin.setup();

    //Pacman
    Pacman pacman(*m_window);

    //Ghost
    std::vector<Ghost*> ghosts;
    ghosts.push_back(Factory(GhostType::BLINKY));
    ghosts.push_back(Factory(GhostType::CLYDE));
    ghosts.push_back(Factory(GhostType::PINKY));
    ghosts.push_back(Factory(GhostType::INKY));

    //Map
    Map map(*m_window);
    map.loadingLevel();
    map.sketch_convert(pacman, ghosts);

    sf::Event event;
    while (m_window->isOpen())
    {
        unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();
        lag += delta_time;
        previous_time += std::chrono::microseconds(delta_time);

        while (FRAME_DURATION <= lag)
        {
            lag -= FRAME_DURATION;
            while (m_window->pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    m_window->close();
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                    m_window->close();
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                    playGame = 1;
            }

            GameLogic(ghosts, pacman, map);

            if (playGame == 0)
                preview_anim();

            if (FRAME_DURATION > lag)
            {
                m_window->clear();
                if (playGame == 1)
                {
                    if (winGame == 0 && pacman.get_dead() == 0)
                    {
                        map.draw();

                        for (auto ghost : ghosts)
                            ghost->draw();

                        pacman.draw();
                    }

                    if (pacman.get_dead())
                        gameOver.draw();
                    if (winGame == 1)
                        gameWin.draw();
                }
                else
                    m_window->draw(m_preview);

                m_window->display();
            }
        }
    }
    for (int i = 0; i < ghosts.size(); ++i)
    {
        delete ghosts[i];
    }
}

void Game::setPreview()
{
    if (!preview_tex.loadFromFile(preview_path))
        throw std::exception("Preview file not found!");
}

void Game::preview_anim()
{
    preview_timer++;
    m_preview.setTextureRect(sf::IntRect(next_frame * image_x, 0, image_x, image_y));
    if (preview_timer > time_start && preview_timer < time_start * 2)
        next_frame = 1;
    else if (preview_timer >= time_start * 2)
    {
        next_frame = 0;
        preview_timer = 0;
    }
}