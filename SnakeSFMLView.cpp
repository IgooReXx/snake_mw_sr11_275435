//
// Created by c on 5/24/23.
//

#include "SnakeSFMLView.h"
#include <iostream>

SnakeSFMLView::SnakeSFMLView(Snake &s1, SnakeBoard &b1) : snake(s1), board(b1)
{
    cellWidth = WINDOW_WIDTH/MAP_SIZE;
    cellHeight = WINDOW_HEIGHT/MAP_SIZE;

    set_shape_size();
    set_shape_colour();
    set_shape_position();

    load_all_txsp();
}

void SnakeSFMLView::draw(sf::RenderWindow &win)
{
    int x_pos = 0;
    int y_pos = 0;

    for(int row=0; row<MAP_SIZE; ++row)
    {
        for(int col=0; col<MAP_SIZE; ++col)
        {
            draw_object(row, col, x_pos, y_pos, win);
            x_pos += cellWidth;
        }
        x_pos=0;
        y_pos += cellHeight;
    }

    if(snake.get_status()==DEAD)
    {
        display_end_screen(win);
    }
}

void SnakeSFMLView::load_all_txsp()
{
    if(!end_screen_loss.tx.loadFromFile("../textures/lost.png", sf::IntRect(0, 0, 100, 100)))
        exit(1);
    end_screen_loss.sp.setTexture(end_screen_loss.tx);

    if(!end_screen_win.tx.loadFromFile("../textures/won.png", sf::IntRect(0, 0, 100, 100)))
        exit(1);
    end_screen_win.sp.setTexture(end_screen_win.tx);
}

void SnakeSFMLView::display_end_screen(sf::RenderWindow &win)
{
    TxSp* displayed_end_screen;
    displayed_end_screen=&end_screen_loss;
    displayed_end_screen->sp.setPosition(WINDOW_WIDTH/2-50, WINDOW_HEIGHT/2-50);
    win.draw(displayed_end_screen->sp);
}

void SnakeSFMLView::set_shape_size()
{
    emptyCell.setSize(sf::Vector2f(cellWidth, cellHeight));
    wallCell.setSize(sf::Vector2f(cellWidth, cellHeight));
    appleCell.setSize(sf::Vector2f(cellWidth, cellHeight));
    snakeCell.setSize(sf::Vector2f(cellWidth, cellHeight));
}

void SnakeSFMLView::set_shape_colour()
{
    emptyCell.setFillColor(sf::Color(19, 130, 7));
    wallCell.setFillColor(sf::Color::Blue);
    appleCell.setFillColor(sf::Color::Red);
    snakeCell.setFillColor(sf::Color::Cyan);
}

void SnakeSFMLView::set_shape_position()
{
    emptyCell.setPosition(0, 0);
    wallCell.setPosition(0, 0);
    appleCell.setPosition(0, 0);
    snakeCell.setPosition(0, 0);
}

void SnakeSFMLView::draw_object(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
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
}