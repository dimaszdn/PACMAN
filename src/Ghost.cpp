#include<Ghost.h>
#include<Collision.h>
#include<iostream>
#include<cmath>

Ghost::Ghost(sf::RenderWindow& window) : m_window(window), GHOST_SPEED(1)
{
    m_status = STATUS::SCATTER;
}

void Ghost::setPosition(short x, short y)
{
    m_position = {x, y};
}

void Ghost::draw()
{
    circle.setRadius(CELL_SIZE / 2);
    circle.setPosition(m_position.x, m_position.y);

    rect.setSize(sf::Vector2f(circle.getRadius() * 2, circle.getRadius()));
    rect.setPosition(m_position.x, m_position.y + circle.getRadius());

    m_window.draw(circle);
    m_window.draw(rect);
}

void Ghost::setColor(sf::Shape& shape)
{
    shape.setFillColor(sf::Color(255, 255, 255));
}

void Ghost::update(std::vector<std::vector<CELL>>& map, Pacman& pacman, const Position& blinky_pos)
{
    bool move = 0;

    bool walls[4];
    walls[0] = map_collision(0, use_door, m_position.x, m_position.y - GHOST_SPEED, map); //UP WALL
    walls[1] = map_collision(0, use_door, m_position.x, m_position.y + GHOST_SPEED, map); //DOWN WALL
    walls[2] = map_collision(0, use_door, GHOST_SPEED + m_position.x, m_position.y, map); //RIGHT WALL
    walls[3] = map_collision(0, use_door, m_position.x - GHOST_SPEED, m_position.y, map); //LEFT WALL

    update_target(pacman.get_position(), pacman.get_direction(), blinky_pos);

    //RANDOM MOVING
    if (m_status != STATUS::SCARED)
    {
        move = 1;
        float short_dist = 0;
        unsigned char last_dir = m_direction;

        if ((walls[0] == 0) && (last_dir != 1))
        {
            float distance = get_target_dist(0);
            if ((distance < short_dist) || (short_dist == 0))
            {
                short_dist = distance;
                m_direction = 0;
            }
        }

        if ((walls[1] == 0) && (last_dir != 0))
        {
            float distance = get_target_dist(1);
            if ((distance < short_dist) || (short_dist == 0))
            {
                short_dist = distance;
                m_direction = 1;
            }
        }

        if ((walls[2] == 0) && (last_dir != 3))
        {
            float distance = get_target_dist(2);
            if ((distance < short_dist) || (short_dist == 0))
            {
                short_dist = distance;
                m_direction = 2;
            }
        }

        if ((walls[3] == 0) && (last_dir != 2))
        {
            float distance = get_target_dist(3);
            if ((distance < short_dist) || (short_dist == 0))
            {
                short_dist = distance;
                m_direction = 3;
            }
        }
    }

    if (move)
    {
        switch (m_direction)
        {
            case 0: //UP
                m_position.y -= GHOST_SPEED;
                break;
            case 1: //DOWN
                m_position.y += GHOST_SPEED;
                break;
            case 2: //RIGHT
                m_position.x += GHOST_SPEED;
                break;
            case 3: //LEFT
                m_position.x -= GHOST_SPEED;
                break;
        }
    }

    //teleport
    if (-CELL_SIZE >= m_position.x)
    {
        m_position.x = CELL_SIZE * MAP_WIDTH - GHOST_SPEED;
    }
    else if (CELL_SIZE * MAP_WIDTH <= m_position.x)
    {
        m_position.x = GHOST_SPEED - CELL_SIZE;
    }

    if (pacman_collision(pacman.get_position()) == 1)
    {
        pacman.set_dead(1);
    }
}

float Ghost::get_target_dist(unsigned char direction)
{
    short x = m_position.x;
    short y = m_position.y;

    switch (direction)
    {
        case 0:
            y -= GHOST_SPEED;
            break;
        case 1:
            y += GHOST_SPEED;
            break;
        case 2:
            x += GHOST_SPEED;
            break;
        case 3:
            x -= GHOST_SPEED;
            break;
    }

    return static_cast<float>(sqrt(pow(x - m_target.x, 2) + pow(y - m_target.y, 2)));
}

void Ghost::update_target(const Position &pacman_position, unsigned char pacman_dir, const Position& blinky_pos)
{

}

Position Ghost::get_position()
{
    return m_position;
}

void Ghost::settings()
{
    setColor(rect);
    setColor(circle);
}

bool Ghost::pacman_collision(const Position &pacman_position)
{
    if (m_position.x > pacman_position.x - CELL_SIZE && m_position.x < CELL_SIZE + pacman_position.x)
    {
        if (m_position.y > pacman_position.y - CELL_SIZE && m_position.y < CELL_SIZE + pacman_position.y)
        {
            return 1;
        }
    }
    return 0;
}

void Ghost::set_status(STATUS status)
{
    m_status = status;
}