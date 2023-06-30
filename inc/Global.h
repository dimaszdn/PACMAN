#pragma once

//MAP
constexpr unsigned char CELL_SIZE = 16;
constexpr unsigned char MAP_HEIGHT = 21;
constexpr unsigned char MAP_WIDTH = 21;
constexpr unsigned char MAP_RESIZE = 2;

//WINDOW LAG
constexpr unsigned short FRAME_DURATION = 16667;

//PACMAN
//constexpr unsigned char PACMAN_SPEED = 2;

//GHOST
constexpr unsigned char GHOST_SPEED = 1;

enum class CELL
{
    WALL,
    EMPTY,
    DOOR,
    PACMAN,
    GHOST,
    GRANULES

};
struct Position
{
    short x;
    short y;
};
