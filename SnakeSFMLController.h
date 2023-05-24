//
// Created by c on 5/24/23.
//

#ifndef SNAKE_SNAKESFMLCONTROLLER_H
#define SNAKE_SNAKESFMLCONTROLLER_H

#include "SnakeBoard.h"
#include "Snake.h"
#include "SnakeSFMLView.h"

class SnakeSFMLController {

    Snake &snake;
    SnakeBoard &board;
    SnakeSFMLView &view;
    sf::RenderWindow &window;

public:

    SnakeSFMLController(Snake &s1, SnakeBoard &b1, SnakeSFMLView &v1, sf::RenderWindow &win);
    void play(sf::Event &event);


};


#endif //SNAKE_SNAKESFMLCONTROLLER_H
