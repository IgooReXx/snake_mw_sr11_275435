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
            draw_logic(row, col, x_pos, y_pos, win);
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

    if(!snakeHead.tx.loadFromFile("../textures/karpHead.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    snakeHead.sp.setTexture(snakeHead.tx);

    if(!snakeBodyHorizontal.tx.loadFromFile("../textures/karpBody.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    snakeBodyHorizontal.sp.setTexture(snakeBodyHorizontal.tx);

    snakeBodyVertical = snakeBodyHorizontal;
    snakeBodyVertical.sp.setRotation(-90);

    if(!snakeTail.tx.loadFromFile("../textures/karpTail.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    snakeTail.sp.setTexture(snakeTail.tx);

    if(!grass.tx.loadFromFile("../textures/grass.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    grass.sp.setTexture(grass.tx);

    if(!wall_1.tx.loadFromFile("../textures/wall_1.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    wall_1.sp.setTexture(wall_1.tx);

    if(!wall_2.tx.loadFromFile("../textures/wall_2.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    wall_2.sp.setTexture(wall_2.tx);

    if(!apple.tx.loadFromFile("../textures/apple.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    apple.sp.setTexture(apple.tx);

    if(!snakeConnector.tx.loadFromFile("../textures/connector.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    snakeConnector.sp.setTexture(snakeConnector.tx);

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

void SnakeSFMLView::draw_logic(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
{
    draw_grass(x_pos, y_pos, win);
    draw_apple(row, col, x_pos, y_pos, win);
    draw_wall(row, col, x_pos, y_pos, win);
    draw_snake(row, col, x_pos, y_pos, win);
}

void SnakeSFMLView::draw_object(int x_pos, int y_pos, sf::RenderWindow &win, sf::Sprite objectSprite)
{
    objectSprite.setPosition(x_pos, y_pos);
    win.draw(objectSprite);

}

void SnakeSFMLView::draw_snake(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
{
    snakeHead.sp.setOrigin(80/2, 60/2);
    snakeTail.sp.setOrigin(80/2, 60/2);
    snakeBodyHorizontal.sp.setOrigin(80/2, 60/2);
    snakeBodyVertical.sp.setOrigin(80/2, 60/2);
    snakeConnector.sp.setOrigin(80/2, 60/2);
    x_pos+=80/2;
    y_pos+=60/2;
    switch (snake.get_snake_facing()) {
        case UP: {
            snakeHead.sp.setRotation(90);
            snakeHead.sp.setScale(-1.0f, -1.0f);
            break;
        }
        case DOWN: {
            snakeHead.sp.setRotation(90);
            snakeHead.sp.setScale(1.0f, -1.0f);
            break;
        }
        case RIGHT: {
            snakeHead.sp.setRotation(0);
            snakeHead.sp.setScale(1.0f, 1.0f);
            break;
        }
        case LEFT:{
            snakeHead.sp.setRotation(0);
            snakeHead.sp.setScale(-1.0f, 1.0f);
            break;
        }
    }
    for(int cell : snake.get_snakeBody())
    {
        if(cell == snake.get_snake_head() && cell == row*MAP_SIZE+col)
            draw_object(x_pos, y_pos, win,snakeHead.sp);
        else if(cell == snake.get_snake_tail() && cell == row*MAP_SIZE+col)
            draw_object(x_pos, y_pos, win,snakeTail.sp);
        else if (cell == row*MAP_SIZE+col)
            draw_snakeBody(cell, x_pos, y_pos, win);
    }
}
void SnakeSFMLView::draw_wall(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
{
    if(board.check_for_wall(row, col))
    {
        if((row*MAP_SIZE+col) % 2 == 0)
            draw_object(x_pos, y_pos, win,wall_1.sp);
        else
            draw_object(x_pos, y_pos, win,wall_2.sp);
    }
}
void SnakeSFMLView::draw_apple(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
{
    if(board.check_for_apple(row, col))
    {
        draw_object(x_pos, y_pos, win,apple.sp);
    }
}
void SnakeSFMLView::draw_grass(int x_pos, int y_pos, sf::RenderWindow &win)
{
    draw_object(x_pos, y_pos, win,grass.sp);
}

void SnakeSFMLView::draw_snakeBody(int currentCell, int x_pos, int y_pos, sf::RenderWindow &win)
{
    if(currentCell == snake.get_snake_head() or currentCell == snake.get_snake_tail())
        return;
    std::vector<int> snakeCells = snake.get_snakeBody();
    int previousCell=-1;
    int nextCell=-1;
    for(int index=0; index<snakeCells.size(); index++)
    {
        if(snakeCells[index] == currentCell)
        {
            previousCell = snakeCells[index-1];
            nextCell = snakeCells[index+1];
        }
    }
    if(currentCell % MAP_SIZE == previousCell % MAP_SIZE and currentCell % MAP_SIZE == nextCell % MAP_SIZE)
    {
        draw_object(x_pos, y_pos, win, snakeBodyVertical.sp);
    }
    else if(currentCell / MAP_SIZE == previousCell / MAP_SIZE and currentCell / MAP_SIZE == nextCell / MAP_SIZE)
    {
        draw_object(x_pos, y_pos, win, snakeBodyHorizontal.sp);
    }
    else
    {
        draw_connector(x_pos, y_pos, win, currentCell, previousCell, nextCell);
    }
}

void SnakeSFMLView::draw_connector(int x_pos, int y_pos, sf::RenderWindow &win, int currentCell, int previousCell, int nextCell)
{
    if(nextCell == currentCell+1 and previousCell % MAP_SIZE == currentCell % MAP_SIZE)
    {
        snakeConnector.sp.setRotation(0);
        snakeConnector.sp.setScale(1, 1);
    }
    if(nextCell == currentCell-1 and previousCell % MAP_SIZE == currentCell % MAP_SIZE)
    {
        snakeConnector.sp.setRotation(180);
        snakeConnector.sp.setScale(1, 1);
    }
    if(nextCell % MAP_SIZE == currentCell % MAP_SIZE and previousCell == currentCell - 1)
    {
        snakeConnector.sp.setScale(-1, -1);
        snakeConnector.sp.setRotation(0);
    }
    if(nextCell % MAP_SIZE == currentCell % MAP_SIZE and previousCell == currentCell + 1)
    {
        snakeConnector.sp.setRotation(-90);
    }
    draw_object(x_pos, y_pos, win, snakeConnector.sp);
}
