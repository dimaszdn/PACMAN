#pragma once
#include<Ghost.h>

class Pinky : public Ghost
{
public:
    Pinky(sf::RenderWindow& window);
    void setColor(sf::Shape& shape) override;
    void update_target(const Position& pacman_position, unsigned char pacman_dir, const Position& blinky_pos) override;
};