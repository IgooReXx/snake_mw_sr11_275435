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

    sf::RectangleShape emptyCell;
    sf::RectangleShape wallCell;
    sf::RectangleShape appleCell;
    sf::RectangleShape snakeCell;

    TxSp end_screen_win;
    TxSp end_screen_loss;
    TxSp snakeHead;
    TxSp snakeBody;
    TxSp snakeTail;
    TxSp grass;
    TxSp wall;
    TxSp apple;


    int cellWidth;
    int cellHeight;

    void load_all_txsp();
    void display_end_screen(sf::RenderWindow &win);
    void set_shape_size();
    void set_shape_colour();
    void set_shape_position();
    void draw_object(int row, int col, int x_pos, int y_pos, sf::RenderWindow &win);

public:

    SnakeSFMLView(Snake &s1, SnakeBoard &b1);
    void draw(sf::RenderWindow &win);

};


#endif //SNAKE_SNAKESFMLVIEW_H
