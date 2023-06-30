#pragma once
#include <SFML/Graphics.hpp>
#include<sstream>

class GameBar
{
private:
    sf::RenderWindow& m_window;
    sf::Text m_text;
    sf::Font m_font;
    std::string font_path = "files/font/BAUHS93.TTF";
    std::string m_str;
public:
    GameBar(sf::RenderWindow& window);
    void setStr(const std::string& str);
    void setFont();
    void draw();
    void setup();
};