#include<Collision.h>

bool map_collision(bool eat_granules, bool use_door, short x, short y, std::vector<std::vector<CELL>>& map)
{
    bool output = 0;

    float cell_x = x / static_cast<float>(CELL_SIZE);
    float cell_y = y / static_cast<float>(CELL_SIZE);

    for (unsigned char a = 0; a < 4; ++a)
    {
        short x = 0;
        short y = 0;

        switch (a)
        {
            case 0:
                x = static_cast<short>(floor(cell_x));
                y = static_cast<short>(floor(cell_y));
                break;
            case 1:
                x = static_cast<short>(ceil(cell_x));
                y = static_cast<short>(floor(cell_y));
                break;
            case 2:
                x = static_cast<short>(floor(cell_x));
                y = static_cast<short>(ceil(cell_y));
                break;
            case 3:
                x = static_cast<short>(ceil(cell_x));
                y = static_cast<short>(ceil(cell_y));
                break;
        }
        if (x >= 0 && y >= 0 && MAP_HEIGHT > y && MAP_WIDTH > x)
        {
            if (map[y][x] == CELL::WALL)
            {
                output = 1;
            }
            else if (use_door == 0 && map[y][x] == CELL::DOOR)
            {
                output = 1;
            }
            else if (eat_granules == 1 && map[y][x] == CELL::GRANULES)
            {
                map[y][x] = CELL::EMPTY;
            }
        }
    }
    return output;
}