//
// Created by c on 5/17/23.
//

#include "SnakeBoard.h"
#define MAP_SIZE 10
#include <iostream>


SnakeBoard::SnakeBoard(Snake &s) : snake(s)
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
    if(clock.getElapsedTime() >= sf::milliseconds(2000))
    {
        collision_logic();
        snake.update_snake();
        clock.restart();
    }

}

int SnakeBoard::get_apple_pos()
{
    return apple.front();
}

void SnakeBoard::place_apple(int row, int col)
{
    apple.push_back(row * MAP_SIZE + col);
}

bool SnakeBoard::check_for_apple(int row, int col)
{
    if(apple.size() == 0)
    {
        return false;
    }

    if(apple.front() == row*MAP_SIZE+col)
        return true;

    return false;
}

void SnakeBoard::remove_apple()
{
    apple.pop_back();

}

bool SnakeBoard::check_for_wall(int row, int col)
{
    for(int cell : walls)
    {
        if( row * MAP_SIZE + col == cell)
            return true;
    }

    return false;
}

Cell SnakeBoard::convert_cell(int cell)
{
    Cell t;
    t.row = cell / MAP_SIZE;
    t.col = cell % MAP_SIZE;
    return t;
}

bool SnakeBoard::snake_collision()
{
    Cell nextCell = convert_cell(snake.get_snake_next_pos());

    if(snake.get_snake_next_pos() == snake.check_for_snake(nextCell.row, nextCell.col))
        return true;
    return false;
}

bool SnakeBoard::wall_collision()
{
    int nextCell = snake.get_snake_next_pos();
    for(int cell : walls)
    {
        if( cell == nextCell )
            return true;
    }
    return false;
}

bool SnakeBoard::apple_collision()
{
    if(apple.front() == snake.get_snake_next_pos())
        return true;
    return false;
}

bool SnakeBoard::map_boundary_collision()
{
    Cell currentCell = convert_cell(snake.get_snake_head());
    if(currentCell.col==0 or currentCell.col == MAP_SIZE-1 or currentCell.row == 0 or currentCell.row == MAP_SIZE-1)
    {
        Cell nextCell = convert_cell(snake.get_snake_next_pos());
        if(nextCell.row == currentCell.row+1 and nextCell.col == 0)
            return true;
        if(nextCell.row == currentCell.row-1 and nextCell.col == MAP_SIZE-1)
            return true;
        if(nextCell.row <= 0)
            return true;
        if(nextCell.row >= MAP_SIZE-1)
            return true;
    }
    return false;
}

void SnakeBoard::collision_logic()
{
    if(map_boundary_collision())
        snake.kill_snake();
    if(wall_collision())
        snake.kill_snake();
    if(apple_collision())
        snake.set_apple_eaten();
}
