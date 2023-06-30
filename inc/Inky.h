#include<Ghost.h>

class Inky : public Ghost
{
public:
    Inky(sf::RenderWindow& window);
    void setColor(sf::Shape& shape) override;
    void update_target(const Position& pacman_position, unsigned char pacman_dir, const Position& blinky_pos) override;
};