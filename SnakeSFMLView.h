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


class SnakeSFMLView {

    Snake &snake;
    SnakeBoard &board;

    sf::RectangleShape emptyCell;
    sf::RectangleShape wallCell;
    sf::RectangleShape appleCell;
    sf::RectangleShape snakeCell;

    int cellWidth;
    int cellHeight;

public:

    SnakeSFMLView(Snake &s1, SnakeBoard &b1);
    void draw(sf::RenderWindow &win);

};


#endif //SNAKE_SNAKESFMLVIEW_H
