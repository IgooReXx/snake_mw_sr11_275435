//
// Created by c on 5/17/23.
//

#include "Snake.h"
#define MAP_SIZE 10

Snake::Snake()
{
    snakeBody.push_back(4 * MAP_SIZE + 4);
    snakeBody.push_back(4 * MAP_SIZE + 3);
    facing = UP;
    status = ALIVE;
    apple_eaten = false;
}

int Snake::get_snake_head()
{
    return snakeBody.front();
}

Facing Snake::get_snake_facing()
{
    return facing;
}

bool Snake::check_for_snake(int row, int col)
{
    for(int body_part : snakeBody)
    {
        if( row * MAP_SIZE + col == body_part)
        {
            return true;
        }
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
        return get_snake_head() - MAP_SIZE;

    return get_snake_head() + MAP_SIZE;
}

void Snake::update()
{
    snakeBody.emplace(snakeBody.begin(), get_snake_next_pos());
    if(!apple_eaten)
        snakeBody.pop_back();
    apple_eaten = false;
}

void Snake::kill_snake()
{
    status = DEAD;
}

Status Snake::get_status()
{
    return status;
}

void Snake::set_apple_eaten()
{
    apple_eaten = true;
}

void Snake::turn(Facing f)
{
    switch(facing)
    {
        case UP:
        case DOWN:
            if(f == LEFT or f == RIGHT)
                facing = f;
            break;
        case RIGHT:
        case LEFT:
            if(f == UP or f == DOWN)
                facing = f;
            break;
    }
}

int Snake::get_snake_tail()
{
   return snakeBody.back();
}