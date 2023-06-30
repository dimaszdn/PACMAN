#include<Inky.h>

Inky::Inky(sf::RenderWindow &window) : Ghost(window)
{
    use_door = 1;
}

void Inky::setColor(sf::Shape &shape)
{
    shape.setFillColor(sf::Color(125, 255, 255));
}

void Inky::update_target(const Position &pacman_position, unsigned char pacman_dir, const Position& blinky_pos)
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
            m_target = {CELL_SIZE * (MAP_WIDTH - 1), CELL_SIZE * (MAP_HEIGHT - 1)};
        }
        else if (m_status == STATUS::CHASE)
        {
            m_target = pacman_position;
            switch (pacman_dir)
            {
                case 0:
                    m_target.y -= CELL_SIZE;
                    break;
                case 1:
                    m_target.y += CELL_SIZE;
                    break;
                case 2:
                    m_target.x += CELL_SIZE;
                    break;
                case 3:
                    m_target.x -= CELL_SIZE;
                    break;
            }
            m_target.x += m_target.x - blinky_pos.x;
            m_target.y += m_target.y - blinky_pos.y;
        }
    }
}