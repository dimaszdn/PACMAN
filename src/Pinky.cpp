#include<Pinky.h>

Pinky::Pinky(sf::RenderWindow &window) : Ghost(window)
{
    use_door = 1;
}

void Pinky::setColor(sf::Shape &shape)
{
    shape.setFillColor(sf::Color(255, 125, 175));
}

void Pinky::update_target(const Position &pacman_position, unsigned char pacman_dir, const Position& blinky_pos)
{
    if (use_door == 1)
    {
        m_target = {160, 112};
        if (m_position.x == m_target.x && m_position.y == m_target.y)
        {
            use_door = 0;
        }
    }
    else
    {
        if (m_status == STATUS::SCATTER)
        {
            m_target = {0, 0};
        }
        else if (m_status == STATUS::CHASE)
        {
            m_target = pacman_position;
            switch (pacman_dir)
            {
                case 0:
                    m_target.y -= CELL_SIZE * 2;
                    break;
                case 1:
                    m_target.y += CELL_SIZE * 2;
                    break;
                case 2:
                    m_target.x += CELL_SIZE * 2;
                    break;
                case 3:
                    m_target.x -= CELL_SIZE * 2;
                    break;
            }
        }
    }
}