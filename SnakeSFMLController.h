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

    bool keyRegistered;

public:

    SnakeSFMLController(Snake &s1, SnakeBoard &b1, SnakeSFMLView &v1, sf::RenderWindow &win);
    void play(sf::Event &event);
    bool get_keyRegistered();
    void reset_keyRegistered();


};


#endif //SNAKE_SNAKESFMLCONTROLLER_H
