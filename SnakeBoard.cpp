//
// Created by c on 5/17/23.
//

#include "SnakeBoard.h"
#include <iostream>

SnakeBoard::SnakeBoard(Snake &s1) : snake(s1)
{
    place_apple(0, 4);
    walls.push_back(3*MAP_SIZE+5);
}

void SnakeBoard::debug_display()
{
    for(int row=0; row<MAP_SIZE; row++)
    {
        for(int col=0; col<MAP_SIZE; col++)
        {
            if (snake.check_for_snake(row, col))
            {
                std::cout << "#";
            }
            else if (check_for_apple(row, col))
            {
                std::cout << "a";
            }
            else if (check_for_wall(row, col))
            {
                std::cout << "W";
            }
            else
            {
                std::cout << "_";
            }
        }
        std::cout << std::endl;
    }
}

void SnakeBoard::update()
{
    snake.update_snake();
}


void SnakeBoard::place_apple(int row, int col)
{
    apple.position = row * MAP_SIZE + col;
    apple.is_spawned = true;
}

bool SnakeBoard::check_for_apple(int row, int col)
{
    if(!apple.is_spawned)
        return false;

    if(apple.position == row*MAP_SIZE+col)
        return true;

    return false;
}

void SnakeBoard::remove_apple()
{
    apple.position = -1;
    apple.is_spawned = false;
}

bool SnakeBoard::check_for_wall(int row, int col)
{
    for(int i=0; i < walls.size(); i++)
    {
        if( row * MAP_SIZE + col == walls[i])
            return true;
    }

    return false;
}