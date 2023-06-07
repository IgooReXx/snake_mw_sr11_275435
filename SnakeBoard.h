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
enum GameDifficulty {EASY, NORMAL, HARD};

class SnakeBoard {

    Snake &snake;
    std::vector<int> walls;
    std::vector<int> apple;
    sf::Clock clock;
    bool wasUpdated;
    int points;
    GameStatus status;
    GameDifficulty difficulty;
    int time;


    void replace_apple();
    bool wall_collision();
    bool apple_collision();
    bool snake_collision();
    bool map_boundary_collision();
    Cell convert_cell(int cell);
    void collision_logic();
    void place_walls();
    void remove_occupied_cells(std::vector<int> &availableCells);
    void remove_snake_cells(std::vector<int> &availableCells);
    void remove_wall_cells(std::vector<int> &availableCells);
    void remove_apple_cells(std::vector<int> &availableCells);
    void set_update_speed();


public:

    SnakeBoard(Snake &s);
    void debug_display();
    void update();
    bool check_for_wall(int row, int col);
    bool check_for_apple(int row, int col);
    bool get_wasUpdated();
    void reset_wasUpdated();
    int get_points();
    GameStatus get_status();
    void set_status_running();

    void set_GameDifficulty(GameDifficulty Difficulty);
    GameDifficulty get_GameDifficulty();
};


#endif //SNAKE_SNAKEBOARD_H
