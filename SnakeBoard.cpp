//
// Created by c on 5/17/23.
//

#include "SnakeBoard.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>


SnakeBoard::SnakeBoard(Snake &s) : snake(s)
{
    set_GameDifficulty(EASY);
    place_walls();
    wasUpdated = false;
    points = 600;
    status = MENU;
    apple.push_back(-1);
    replace_apple();
    set_update_speed();
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
    set_update_speed();
    if(clock.getElapsedTime() >= sf::milliseconds(time))
    {
        collision_logic();
        snake.update();
        clock.restart();
        wasUpdated = true;
        if(points > 0)
            points -=1;
    }
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

void SnakeBoard::replace_apple()
{
    std::vector<int> availableCells;

    for(int cell=0; cell<MAP_SIZE*MAP_SIZE; ++cell)
    {
        availableCells.push_back(cell);
    }

    remove_occupied_cells(availableCells);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (availableCells.begin(), availableCells.end(), std::default_random_engine(seed)); // Inicjacja 3. argumentu https://cplusplus.com/reference/algorithm/shuffle/
    apple.front() = availableCells.front();
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

    if(snake.check_for_snake(nextCell.row, nextCell.col) and nextCell.row*MAP_SIZE+nextCell.col != snake.get_snake_tail())
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
        if(nextCell.row < 0 or nextCell.col < 0)
            return true;

        if(nextCell.row > MAP_SIZE-1)
            return true;
        if(currentCell.col == 0 and nextCell.col == MAP_SIZE-1)
            return true;
        if(currentCell.col == MAP_SIZE-1 and nextCell.col == 0)
            return true;
    }
    return false;
}


void SnakeBoard::collision_logic()
{
    if(snake_collision())
        snake.kill_snake();
    if(map_boundary_collision())
    {/*snake.kill_snake();*/}
    if(wall_collision())
    {/*snake.kill_snake();*/}
    if(apple_collision())
    {
        snake.set_apple_eaten();
        points +=100;
        replace_apple();
    }
}

bool SnakeBoard::get_wasUpdated()
{
    return wasUpdated;
}

void SnakeBoard::reset_wasUpdated()
{
    wasUpdated = false;
}

int SnakeBoard::get_points()
{
    return points;
}

void SnakeBoard::remove_occupied_cells(std::vector<int> &availableCells)
{
    remove_snake_cells(availableCells);
    remove_apple_cells(availableCells);
    remove_wall_cells(availableCells);
}
void SnakeBoard::remove_snake_cells(std::vector<int> &availableCells)
{
    for(int cell : snake.get_snakeBody())
    {
        std::vector<int>::iterator end = availableCells.end();
        std::vector<int>::iterator newEnd = std::remove(availableCells.begin(), availableCells.end(), cell);
        if(end != newEnd)
            availableCells.pop_back();
    }
}
void SnakeBoard::remove_wall_cells(std::vector<int> &availableCells)
{
    for(int cell : walls)
    {
        std::vector<int>::iterator end = availableCells.end();
        std::vector<int>::iterator newEnd = std::remove(availableCells.begin(), availableCells.end(), cell);
        if(end != newEnd)
            availableCells.pop_back();
    }
}
void SnakeBoard::remove_apple_cells(std::vector<int> &availableCells)
{
    for(int cell : apple)
    {
        std::vector<int>::iterator end = availableCells.end();
        std::vector<int>::iterator newEnd = std::remove(availableCells.begin(), availableCells.end(), cell);
        if(end!=newEnd)
            availableCells.pop_back();
    }
}

void SnakeBoard::place_walls()
{
    walls.push_back(11);
    walls.push_back(12);
    walls.push_back(21);
    walls.push_back(28);
    walls.push_back(71);
    walls.push_back(78);
    walls.push_back(87);
    walls.push_back(88);
}

GameStatus SnakeBoard::get_status()
{
    return status;
}

void SnakeBoard::set_status_running()
{
    status = RUNNING;
}

void SnakeBoard::set_GameDifficulty(GameDifficulty Difficulty)
{
    difficulty = Difficulty;
}

GameDifficulty SnakeBoard::get_GameDifficulty() {
    return difficulty;
}

void SnakeBoard::set_update_speed()
{
    if(get_GameDifficulty() == EASY)
        time = 300;
    else if(get_GameDifficulty() == NORMAL)
        time = 200;
    else if(get_GameDifficulty() == HARD)
        time = 100;
}
