//
// Created by c on 5/24/23.
//

#include "SnakeSFMLView.h"
#include <iostream>

SnakeSFMLView::SnakeSFMLView(Snake &s1, SnakeBoard &b1) : snake(s1), board(b1)
{
    cellWidth = WINDOW_WIDTH/MAP_SIZE;
    cellHeight = WINDOW_HEIGHT/MAP_SIZE;

    menuButtonPlay = sf::RectangleShape(sf::Vector2f(300, 100));
    menuButtonEasy = sf::RectangleShape(sf::Vector2f(100, 100));
    menuButtonNormal = sf::RectangleShape(sf::Vector2f(100, 100));
    menuButtonHard = sf::RectangleShape(sf::Vector2f(100, 100));
    menuButtonPlay.setOrigin(300.0f/2, 100.0f/2);
    menuButtonEasy.setOrigin(100.0f/2,100.0f/2);
    menuButtonNormal.setOrigin(100.0f/2,100.0f/2);
    menuButtonHard.setOrigin(100.0f/2,100.0f/2);

    menuButtonPlay.setPosition(800.0f/2, 600.0f/2);
    menuButtonEasy.setPosition(0+50, 0+50);
    menuButtonNormal.setPosition(200, 50);
    menuButtonHard.setPosition(350, 50);

    load_all_txsp();
}

void SnakeSFMLView::draw(sf::RenderWindow &win)
{
    int x_pos = 0;
    int y_pos = 0;

    if(board.get_status() == MENU)
    {
        display_menu_screen(win);
        return;
    }

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

    if(!snakeBody.tx.loadFromFile("../textures/karpBody.png", sf::IntRect(0, 0, 80, 60)))
        exit(1);
    snakeBody.sp.setTexture(snakeBody.tx);
}

void SnakeSFMLView::display_end_screen(sf::RenderWindow &win)
{
    TxSp* displayed_end_screen;
    displayed_end_screen=&end_screen_loss;
    displayed_end_screen->sp.setPosition(WINDOW_WIDTH/2-50, WINDOW_HEIGHT/2-50);
    win.draw(displayed_end_screen->sp);
}

void SnakeSFMLView::draw_logic(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
{
    draw_grass(x_pos, y_pos, win);
    draw_apple(row, col, x_pos, y_pos, win);
    draw_wall(row, col, x_pos, y_pos, win);
    draw_snake(row, col, x_pos, y_pos, win);
}

void SnakeSFMLView::draw_object(int x_pos, int y_pos, sf::RenderWindow &win, sf::Sprite objectSprite, float rotationInDegrees, float factorX, float factorY)
{
    objectSprite.setRotation(rotationInDegrees);
    objectSprite.setScale(factorX, factorY);
    objectSprite.setPosition(x_pos, y_pos);
    win.draw(objectSprite);
}

void SnakeSFMLView::snakeHead_facing(float &rotationInDegrees, float &factorX, float &factorY)
{
    switch (snake.get_snake_facing())
    {
        case UP: {
            rotationInDegrees = 90;
            factorX=-1.0f;
            factorY=80.0f/60.0f*1.0f;
            break;
        }
        case DOWN: {
            rotationInDegrees = 90;
            factorX=1.0f;
            factorY=80.0f/60.0f*-1.0f;
            break;
        }
        case RIGHT: {
            rotationInDegrees = 0;
            factorX=1.0f;
            factorY=1.0f;
            break;
        }
        case LEFT: {
            rotationInDegrees = 0;
            factorX=-1.0f;
            factorY=1.0f;
            break;
        }
    }
}

void SnakeSFMLView::draw_snake(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
{
    snakeHead.sp.setOrigin(80/2, 60/2);
    snakeTail.sp.setOrigin(80/2, 60/2);
    snakeBody.sp.setOrigin(80/2, 60/2);
    x_pos+=80/2;
    y_pos+=60/2;
    float headRotation;
    float headFactorX, headFactorY;
    snakeHead_facing(headRotation, headFactorX, headFactorY);
    for(int cell : snake.get_snakeBody())
    {
        if(cell == snake.get_snake_head() && cell == row*MAP_SIZE+col)
            draw_object(x_pos, y_pos, win,snakeHead.sp, headRotation, headFactorX, headFactorY);
        else if(cell == snake.get_snake_tail() && cell == row*MAP_SIZE+col)
            draw_snakeTail(x_pos, y_pos, win);
        else if (cell == row*MAP_SIZE+col)
            draw_snakeBody(x_pos, y_pos, win);

    }

}
void SnakeSFMLView::draw_wall(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
{
    if(board.check_for_wall(row, col))
    {
        if((row*MAP_SIZE+col) % 2 == 0)
            draw_object(x_pos, y_pos, win,wall_1.sp, 0, 1, 1);
        else
            draw_object(x_pos, y_pos, win,wall_2.sp, 0, 1 ,1);
    }
}
void SnakeSFMLView::draw_apple(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win)
{
    if(board.check_for_apple(row, col))
    {
        draw_object(x_pos, y_pos, win,apple.sp, 0, 1, 1);
    }
}
void SnakeSFMLView::draw_grass(int x_pos, int y_pos, sf::RenderWindow &win)
{
    draw_object(x_pos, y_pos, win,grass.sp, 0, 1, 1);
}

void SnakeSFMLView::draw_snakeBody(int x_pos, int y_pos, sf::RenderWindow &win)
{
    draw_object(x_pos, y_pos, win, snakeBody.sp, 0,1, 1);
}

void SnakeSFMLView::snakeTail_facing(float &rotationInDegrees, float &factorX, float &factorY)
{
    int index = static_cast<int>(snake.get_snakeBody().size())-2;
    bool bodyOnRight = snake.get_snakeBody()[index] == snake.get_snake_tail() + 1;
    bool bodyOnLeft = snake.get_snakeBody()[index] == snake.get_snake_tail() - 1;
    bool bodyAbove = snake.get_snakeBody()[index] / MAP_SIZE - 1 == snake.get_snake_tail() / MAP_SIZE;
    bool bodyBelow = snake.get_snakeBody()[index] / MAP_SIZE + 1 == snake.get_snake_tail() / MAP_SIZE;
    bool bodyInSameColumn = snake.get_snakeBody()[index] % MAP_SIZE == snake.get_snake_tail() % MAP_SIZE;

    if(bodyOnRight)
    {
        rotationInDegrees = 0;
        factorX = 1;
        factorY = 1;
    }
    if(bodyOnLeft)
    {
        rotationInDegrees = 180;
        factorX = 1;
        factorY = 1;
    }

    if(bodyAbove and bodyInSameColumn)
    {
        rotationInDegrees = 90;
        factorX = 1;
        factorY = 80.0f/60.0f*-1.0f;
    }
    if(bodyBelow and bodyInSameColumn)
    {
        rotationInDegrees = 270;
        factorX = 1;
        factorY = 80.0f/60.0f*-1.0f;
    }
}

void SnakeSFMLView::draw_snakeTail(int x_pos, int y_pos, sf::RenderWindow &win)
{
    float rotationInDegrees, factorX, factorY;
    snakeTail_facing(rotationInDegrees, factorX, factorY);
    draw_object(x_pos,y_pos,win, snakeTail.sp, rotationInDegrees, factorX, factorY);
}

void SnakeSFMLView::display_menu_screen(sf::RenderWindow &win)
{
    switch(board.get_GameDifficulty())
    {
        case EASY:
        {
            menuButtonEasy.setFillColor(sf::Color::Red);
            menuButtonNormal.setFillColor(sf::Color::White);
            menuButtonHard.setFillColor(sf::Color::White);
            break;
        }
        case NORMAL:
        {
            menuButtonEasy.setFillColor(sf::Color::White);
            menuButtonNormal.setFillColor(sf::Color::Red);
            menuButtonHard.setFillColor(sf::Color::White);
            break;
        }
        case HARD:
        {
            menuButtonEasy.setFillColor(sf::Color::White);
            menuButtonNormal.setFillColor(sf::Color::White);
            menuButtonHard.setFillColor(sf::Color::Red);
            break;
        }
    }
    win.draw(menuButtonPlay);
    win.draw(menuButtonEasy);
    win.draw(menuButtonNormal);
    win.draw(menuButtonHard);
}

sf::FloatRect SnakeSFMLView::get_menuButtonPlay()
{
    return menuButtonPlay.getGlobalBounds();
}

sf::FloatRect SnakeSFMLView::get_menuButtonEasy()
{
    return menuButtonEasy.getGlobalBounds();
}

sf::FloatRect SnakeSFMLView::get_menuButtonNormal()
{
    return menuButtonNormal.getGlobalBounds();
}

sf::FloatRect SnakeSFMLView::get_menuButtonHard()
{
    return menuButtonHard.getGlobalBounds();
}
