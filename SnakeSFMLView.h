//
// Created by c on 5/24/23.
//

#ifndef SNAKE_SNAKESFMLVIEW_H
#define SNAKE_SNAKESFMLVIEW_H
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "SnakeBoard.h"

struct TxSp
{
    sf::Texture tx;
    sf::Sprite sp;
};


class SnakeSFMLView {

    Snake &snake;
    SnakeBoard &board;

    sf::RectangleShape menuBackground;
    sf::RectangleShape menuButtonPlay;
    sf::RectangleShape menuButtonEasy;
    sf::RectangleShape menuButtonNormal;
    sf::RectangleShape menuButtonHard;
    TxSp buttonPlay;
    TxSp buttonEasy;
    TxSp buttonNormal;
    TxSp buttonHard;

    TxSp end_screen_win;
    TxSp end_screen_loss;

    TxSp snakeHead;
    TxSp snakeTail;
    TxSp snakeBody;

    TxSp grass;
    TxSp wall_1;
    TxSp wall_2;
    TxSp apple;

    int cellWidth;
    int cellHeight;

    void load_all_txsp();

    void display_menu_screen(sf::RenderWindow &win);
    void display_end_screen(sf::RenderWindow &win);

    void draw_object(int x_pos, int y_pos, sf::RenderWindow &win, sf::Sprite objectSprite, float rotationInDegrees, float factorX, float factorY);

    void draw_logic(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win);

    void draw_wall(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win);
    void draw_apple(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win);
    void draw_grass(int x_pos, int y_pos, sf::RenderWindow &win);

    void draw_snake(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win);
    void set_snake_origin();
    void draw_snakeHead(int x_pos, int y_pos, sf::RenderWindow &win);
    void snakeHead_facing(float &rotationInDegrees, float &factorX, float &factorY);
    void draw_snakeBody(int x_pos, int y_pos, sf::RenderWindow &win);
    void snakeTail_facing(float &rotationInDegrees, float &factorX, float &factorY);
    void draw_snakeTail(int x_pos, int y_pos, sf::RenderWindow &win);

    void set_menuButtons_origin();
    void set_menuButtons_position();
    void set_menuButtons_color();
    void draw_menuButtons(sf::RenderWindow &win);

public:

    SnakeSFMLView(Snake &s1, SnakeBoard &b1);
    void draw(sf::RenderWindow &win);

    sf::FloatRect get_menuButtonPlay();
    sf::FloatRect get_menuButtonEasy();
    sf::FloatRect get_menuButtonNormal();
    sf::FloatRect get_menuButtonHard();
};


#endif //SNAKE_SNAKESFMLVIEW_H
