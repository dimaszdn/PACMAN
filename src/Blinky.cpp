#include<Blinky.h>

Blinky::Blinky(sf::RenderWindow &window) : Ghost(window)
{
    use_door = 0;
}

void Blinky::setColor(sf::Shape &shape)
{
    shape.setFillColor(sf::Color(255, 0, 0));
}

void Blinky::update_target(const Position &pacman_position, unsigned char pacman_dir, const Position& blinky_pos)
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
            m_target = {CELL_SIZE * (MAP_WIDTH - 1), 0};
        }
        else if (m_status == STATUS::CHASE)
        {
            m_target = pacman_position;
        }
    }
}