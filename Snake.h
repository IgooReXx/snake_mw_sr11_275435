//
// Created by c on 5/17/23.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H
#include <vector>

enum Facing {UP, LEFT, DOWN, RIGHT};
enum Status {ALIVE, DEAD};

class Snake {
    std::vector<int> SnakeBody;
    Facing facing;
    Status status;
    bool apple_eaten;

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

};


#endif //SNAKE_SNAKE_H
