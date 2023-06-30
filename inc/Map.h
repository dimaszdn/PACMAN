#pragma once
#include<vector>
#include <SFML/Graphics.hpp>
#include<string>
#include<Global.h>
#include<fstream>
#include<iostream>
#include<Pacman.h>
#include<Ghost.h>

class Map
{
private:
    sf::RenderWindow &m_window;
    std::vector<std::string> map_sketch;
    std::vector<std::vector<CELL>> m_map;
    std::ifstream map_file;
    std::string path_map = "files/map/map.txt";

public:
    Map(sf::RenderWindow& window) : m_window(window)
    {

    }

    ~Map()
    {
        map_file.close();
    }

    void sketch_convert(Pacman& pacman, const std::vector<Ghost*>& ghosts)
    {
        std::vector<std::vector<CELL>> map;
        for (unsigned char y = 0; y < MAP_HEIGHT; ++y)
        {
            std::vector<CELL> row;
            for (unsigned char x = 0; x < MAP_WIDTH; ++x)
            {
                switch (map_sketch[y][x])
                {
                    case ' ':
                        row.push_back(CELL::EMPTY);
                        break;
                    case '#':
                        row.push_back(CELL::WALL);
                        break;
                    case 'P':
                        row.push_back(CELL::PACMAN);
                        pacman.set_position(CELL_SIZE * x, CELL_SIZE * y);
                        break;
                    case '.':
                        row.push_back(CELL::GRANULES);
                        break;
                    case '1':
                        row.push_back(CELL::GHOST);
                        ghosts[0]->setPosition(CELL_SIZE * x, CELL_SIZE * y);
                        break;
                    case '2':
                        row.push_back(CELL::GHOST);
                        ghosts[1]->setPosition(CELL_SIZE * x, CELL_SIZE * y);
                        break;
                    case '3':
                        row.push_back(CELL::GHOST);
                        ghosts[2]->setPosition(CELL_SIZE * x, CELL_SIZE * y);
                        break;
                    case '4':
                        row.push_back(CELL::GHOST);
                        ghosts[3]->setPosition(CELL_SIZE * x, CELL_SIZE * y);
                        break;
                    case '-':
                        row.push_back(CELL::DOOR);
                        break;
                }
            }
            map.push_back(row);
        }
        m_map = map;
    }

    void loadingLevel()
    {
        map_file.open(path_map);
        if (!map_file.is_open())
            throw std::exception("Map file not found!");
        else
        {
            while (!map_file.eof())
            {
                std::string tmp = "";
                std::getline(map_file, tmp);
                map_sketch.push_back(tmp);
            }
        }
    }

    void draw()
    {
        sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));

        sf::CircleShape granules;
        granules.setFillColor(sf::Color(255, 182, 170));

        for (unsigned char y = 0; y < MAP_HEIGHT; ++y)
        {
            for (unsigned char x = 0; x < MAP_WIDTH; ++x)
            {
                cell_shape.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                switch (m_map[y][x])
                {
                    case CELL::GRANULES:
                        granules.setRadius(CELL_SIZE / 8);
                        granules.setPosition(CELL_SIZE * x + (CELL_SIZE / 2 - granules.getRadius()), CELL_SIZE * y + (CELL_SIZE / 2 - granules.getRadius()));
                        m_window.draw(granules);
                        break;
                    case CELL::WALL:
                        cell_shape.setFillColor(sf::Color(36, 36, 255));
                        m_window.draw(cell_shape);
                        break;
                    case CELL::DOOR:
                        cell_shape.setFillColor(sf::Color(100, 100, 255));
                        m_window.draw(cell_shape);
                        break;
                }
            }
        }
    }

    std::vector<std::vector<CELL>>& getMap()
    {
        return m_map;
    }
};
