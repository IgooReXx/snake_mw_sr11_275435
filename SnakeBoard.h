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

enum GameStatus {RUNNING, MENU};

class SnakeBoard {

    Snake &snake;
    std::vector<int> walls;
    std::vector<int> apple;
    sf::Clock clock;
    bool wasUpdated;
    int points;
    GameStatus status;

    void place_apple(int row, int col);
    void replace_apple();
    bool wall_collision();
    bool apple_collision();
    bool snake_collision();
    bool map_boundary_collision();
    Cell convert_cell(int cell);
    void collision_logic();
    int get_apple_pos();
    void place_walls();
    void remove_occupied_cells(std::vector<int> &availableCells);
    void remove_snake_cells(std::vector<int> &availableCells);
    void remove_wall_cells(std::vector<int> &availableCells);
    void remove_apple_cells(std::vector<int> &availableCells);


public:

    SnakeBoard(Snake &s);
    void debug_display();
    void update();
    bool check_for_wall(int row, int col);
    bool check_for_apple(int row, int col);
    bool get_wasUpdated();
    void reset_wasUpdated();
    int get_points();
};


#endif //SNAKE_SNAKEBOARD_H
