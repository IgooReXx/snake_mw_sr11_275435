//
// Created by c on 5/17/23.
//

#include "Snake.h"
#define MAP_SIZE 10

Snake::Snake()
{
    SnakeBody.push_back(4 * MAP_SIZE + 4);
    facing = RIGHT;
}

int Snake::get_snake_head()
{
    return SnakeBody.front();
}

Facing Snake::get_snake_facing()
{
    return facing;
}

bool Snake::check_for_snake(int row, int col)
{
    for(int cell : SnakeBody)
    {
        if (row * MAP_SIZE + col == cell)
            return true;
    }
    return false;
}

int Snake::get_snake_next_pos()
{
    if(facing == RIGHT)
        return get_snake_head() + 1;
    if(facing == LEFT)
        return get_snake_head() - 1;
    if(facing == UP)
        return get_snake_head() + MAP_SIZE;

    return get_snake_head() - MAP_SIZE;
}

void Snake::update_snake()
{

    SnakeBody.emplace(SnakeBody.begin(), get_snake_next_pos());
    SnakeBody.pop_back();

}