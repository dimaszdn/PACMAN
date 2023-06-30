#include<Clyde.h>
#include<iostream>

Clyde::Clyde(sf::RenderWindow &window) : Ghost(window)
{
    use_door = 1;
}

void Clyde::setColor(sf::Shape &shape)
{
    shape.setFillColor(sf::Color(255, 125, 0));
}

void Clyde::update_target(const Position &pacman_position, unsigned char pacman_dir, const Position& blinky_pos)
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
            m_target = {0, CELL_SIZE * (MAP_HEIGHT - 1)};
        }
        else if (m_status == STATUS::CHASE)
        {
            float dist = sqrt(pow(m_position.x - pacman_position.x, 2) + pow(m_position.y - pacman_position.y, 2));
            if (CELL_SIZE * 4 <= dist)
            {
                m_target = pacman_position;
            }
            else
            {
                m_target = {0, CELL_SIZE * (MAP_HEIGHT - 1)};
            }
        }
    }
}