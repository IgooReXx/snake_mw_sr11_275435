//
// Created by c on 5/17/23.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H
#include <vector>

enum Facing {UP, LEFT, DOWN, RIGHT}; // Snake's head facing - movement will proceed in this direction
enum Status {ALIVE, DEAD};

class Snake {
    std::vector<int> snakeBody; // contains all snake cells (including head and tail)
    Facing facing;
    Status status;
    bool apple_eaten; // Used in updating snake's length (if true - last cell in snakeBody is not

public:

    Snake();
    int get_snake_head();
    Facing get_snake_facing();
    bool check_for_snake(int row, int col);
    int get_snake_next_pos();
    void update();
    Status get_status();
    void kill_snake();
    void set_apple_eaten();
    void turn(Facing f);
    int get_snake_tail();
    const std::vector<int>& get_snakeBody();

};


#endif //SNAKE_SNAKE_H
