#pragma once
#include <SFML/Graphics.hpp>
#include <Global.h>


class Pacman
{
private:
    Position m_position;
    sf::RenderWindow& m_window;
    unsigned char m_direction;
    bool m_dead;
    sf::CircleShape circle;
    int countGranules;
    unsigned char PACMAN_SPEED;

public:
    Pacman(sf::RenderWindow& window);
    void draw();
    void set_position(short x, short y);
    void update(std::vector<std::vector<CELL>>& map);
    unsigned char get_direction();
    Position get_position();
    void set_dead(bool dead);
    bool get_dead();
    int get_countGranules();
};
