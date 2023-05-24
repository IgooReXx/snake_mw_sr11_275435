//
// Created by c on 5/24/23.
//

#include "SnakeSFMLController.h"
#include <iostream>

SnakeSFMLController::SnakeSFMLController(Snake &s1, SnakeBoard &b1, SnakeSFMLView &v1, sf::RenderWindow &win)
: snake(s1), board(b1), view(v1), window(win)
{}

void SnakeSFMLController::play(sf::Event &event)
{
    Facing f = snake.get_snake_facing();
    switch(event.key.code)
    {
        case sf::Keyboard::Up:
            f = UP;
            std::cerr << "UP";
            break;
        case sf::Keyboard::Down:
            f = DOWN;
            std::cerr << "DOWN";
            break;
        case sf::Keyboard::Left:
            f = LEFT;
            std::cerr << "LEFT";
            break;
        case sf::Keyboard::Right:
            f = RIGHT;
            std::cerr << "RIGHT";
            break;
        default:
            f = snake.get_snake_facing();
    }
}