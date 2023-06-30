#pragma once
#include <SFML/Graphics.hpp>
#include<string>
#include<chrono>
#include<Ghost.h>
#include<Blinky.h>
#include<Clyde.h>
#include<Inky.h>
#include<Pinky.h>
#include<vector>
#include<Map.h>
#include<GameBar.h>

class Game
{
private:
    sf::RenderWindow* m_window;
    std::string m_caption;
    unsigned lag;
    std::chrono::time_point<std::chrono::steady_clock> previous_time;
    bool winGame;
    unsigned char current_wave;
    unsigned short wave_timer;
    unsigned short LONG_DURATION;
    unsigned short SHORT_DURATION;
    bool next_status;
    bool playGame;

    sf::Sprite m_preview;
    sf::Texture preview_tex;
    std::string preview_path = "files/font/preview.png";
    size_t image_x = 672, image_y = 672;
    unsigned char preview_timer = 0;
    unsigned char next_frame = 0;
    unsigned char time_start = 25;

public:
    Game();
    ~Game();
    void Setup();
    void setCaption(const std::string& str);
    void Run();
    void GameLogic(std::vector<Ghost*>& ghosts, Pacman& pacman, Map& map);
    Ghost* Factory(GhostType ghostType);
    void setPreview();
    void preview_anim();
};