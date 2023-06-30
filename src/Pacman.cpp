#include<Pacman.h>
#include<Collision.h>


Pacman::Pacman(sf::RenderWindow& window) : m_window(window), m_dead(0), PACMAN_SPEED(2)
{

}

void Pacman::set_position(short x, short y)
{
    m_position = {x, y};
}

void Pacman::draw()
{
    circle.setRadius(CELL_SIZE / 2);
    circle.setFillColor(sf::Color(255, 255, 0));
    circle.setPosition(m_position.x, m_position.y);
    m_window.draw(circle);
}

void Pacman::update(std::vector<std::vector<CELL>>& map)
{
    bool walls[4];
    walls[0] = map_collision(0, 0, m_position.x, m_position.y - PACMAN_SPEED, map); //UP WALL
    walls[1] = map_collision(0, 0, m_position.x, m_position.y + PACMAN_SPEED, map); //DOWN WALL
    walls[2] = map_collision(0, 0, PACMAN_SPEED + m_position.x, m_position.y, map); //RIGHT WALL
    walls[3] = map_collision(0, 0, m_position.x - PACMAN_SPEED, m_position.y, map); //LEFT WALL

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (walls[0] == 0)
        {
            m_direction = 0;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (walls[1] == 0)
        {
            m_direction = 1;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (walls[2] == 0)
        {
            m_direction = 2;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (walls[3] == 0)
        {
            m_direction = 3;
        }
    }

    if (walls[m_direction] == 0)
    {
        switch (m_direction)
        {
            case 0: //UP
                m_position.y -= PACMAN_SPEED;
                break;
            case 1: //DOWN
                m_position.y += PACMAN_SPEED;
                break;
            case 2: //RIGHT
                m_position.x += PACMAN_SPEED;
                break;
            case 3: //LEFT
                m_position.x -= PACMAN_SPEED;
                break;
        }
    }
    //Перенос в туннелях
    if (-CELL_SIZE >= m_position.x)
    {
        m_position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
    }
    else if (CELL_SIZE * MAP_WIDTH <= m_position.x)
    {
        m_position.x = PACMAN_SPEED - CELL_SIZE;
    }

    map_collision(1, 0, m_position.x, m_position.y, map);
}

unsigned char Pacman::get_direction()
{
    return m_direction;
}

Position Pacman::get_position()
{
    return m_position;
}

void Pacman::set_dead(bool dead)
{
    m_dead = dead;
}

bool Pacman::get_dead()
{
    return m_dead;
}

int Pacman::get_countGranules()
{
    return countGranules;
}