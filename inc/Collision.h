#pragma once
#include<vector>
#include<Global.h>

bool map_collision(bool eat_granules, bool use_door, short pacman_x, short pacman_y, std::vector<std::vector<CELL>>& map);