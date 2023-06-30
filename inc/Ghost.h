#pragma once
#include<Global.h>
#include <SFML/Graphics.hpp>
#include<Pacman.h>

enum class STATUS
{
    SCATTER, //РАЗБРОСИ
    CHASE, //ПОГОНЯ
    SCARED, //ИСПУГАННЫЙ
    EATEN //СЪЕДЕННЫЙ
};

enum class GhostType
{
    BLINKY, //RED
    CLYDE, //ORANGE
    PINKY, //PINK
    INKY //BLUE
};

class Ghost
{
protected:
    Position m_position;
    Position m_target;
    sf::RenderWindow& m_window;
    unsigned char m_direction;
    bool use_door;
    STATUS m_status;
    unsigned char GHOST_SPEED;

    sf::CircleShape circle;
    sf::RectangleShape rect;


public:
    Ghost(sf::RenderWindow& window);
    void draw();
    virtual void setColor(sf::Shape& shape);
    void settings();

    void setPosition(short x, short y);
    void update(std::vector<std::vector<CELL>>& map, Pacman& pacman, const Position& blinky_pos);
    bool pacman_collision(const Position& pacman_position);

    virtual void update_target(const Position& pacman_position, unsigned char pacman_dir, const Position& blinky_pos);

    float get_target_dist(unsigned char direction);
    Position get_position();

    void set_status(STATUS status);
};