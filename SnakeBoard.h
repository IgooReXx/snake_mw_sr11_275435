//
// Created by c on 5/17/23.
//

#ifndef SNAKE_SNAKEBOARD_H
#define SNAKE_SNAKEBOARD_H
#define MAP_SIZE 10

#include "Snake.h"
#include <SFML/System/Clock.hpp>

struct Cell {
    int row;
    int col;
};

class SnakeBoard {

    Snake &snake;
    std::vector<int> walls;
    std::vector<int> apple;
    sf::Clock clock;
    void place_apple(int row, int col);
    void replace_apple();
    bool wall_collision();
    bool apple_collision();
    bool snake_collision();
    bool map_boundary_collision();
    Cell convert_cell(int cell);
    void collision_logic();
    int get_apple_pos();
    bool wasUpdated;

public:

    SnakeBoard(Snake &s);
    void debug_display();
    void update();
    bool check_for_wall(int row, int col);
    bool check_for_apple(int row, int col);
    bool get_wasUpdated();
    void reset_wasUpdated();
};


#endif //SNAKE_SNAKEBOARD_H
