//
// Created by c on 5/24/23.
//

#include "SnakeSFMLView.h"
#include <iostream>

SnakeSFMLView::SnakeSFMLView(Snake &s1, SnakeBoard &b1) : snake(s1), board(b1)
{
    cellWidth = WINDOW_WIDTH/MAP_SIZE;
    cellHeight = WINDOW_HEIGHT/MAP_SIZE;

    emptyCell.setSize(sf::Vector2f(cellWidth, cellHeight));
    wallCell.setSize(sf::Vector2f(cellWidth, cellHeight));
    appleCell.setSize(sf::Vector2f(cellWidth, cellHeight));
    snakeCell.setSize(sf::Vector2f(cellWidth, cellHeight));

    emptyCell.setFillColor(sf::Color(19, 130, 7));
    wallCell.setFillColor(sf::Color::Blue);
    appleCell.setFillColor(sf::Color::Red);
    snakeCell.setFillColor(sf::Color::Cyan);


    emptyCell.setPosition(0, 0);
    wallCell.setPosition(0, 0);
    appleCell.setPosition(0, 0);
    snakeCell.setPosition(0, 0);
}

void SnakeSFMLView::draw(sf::RenderWindow &win)
{
    int x_pos = 0;
    int y_pos = 0;

    for(int row=0; row<MAP_SIZE; ++row)
    {
        for(int col=0; col<MAP_SIZE; ++col)
        {
            if(snake.check_for_snake(row, col))
            {
                snakeCell.setPosition(x_pos, y_pos);
                win.draw(snakeCell);
            }
            else if(board.check_for_wall(row, col))
            {
                wallCell.setPosition(x_pos, y_pos);
                win.draw(wallCell);
            }
            else if(board.check_for_apple(row, col))
            {
                appleCell.setPosition(x_pos, y_pos);
                win.draw(appleCell);
            }
            else
            {
                emptyCell.setPosition(x_pos, y_pos);
                win.draw(emptyCell);
            }

            x_pos += cellWidth;
        }
        x_pos=0;
        y_pos += cellHeight;
    }
}