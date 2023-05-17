//
// Created by c on 5/17/23.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H
#include <vector>

enum Facing {UP, LEFT, DOWN, RIGHT};

class Snake {

    std::vector<int> SnakeBody;
    Facing facing;

public:

    Snake();
    int get_snake_head();
    Facing get_snake_facing();
    bool check_for_snake(int row, int col);
    int get_snake_next_pos();
    void update_snake();

};


#endif //SNAKE_SNAKE_H
