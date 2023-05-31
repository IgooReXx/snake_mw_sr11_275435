//
// Created by c on 5/24/23.
//

#include "SnakeSFMLController.h"
#include <iostream>

SnakeSFMLController::SnakeSFMLController(Snake &s1, SnakeBoard &b1, SnakeSFMLView &v1, sf::RenderWindow &win)
: snake(s1), board(b1), view(v1), window(win)
{keyRegistered=false;}

void SnakeSFMLController::play(sf::Event &event)
{
    snake.turn(choose_facing(event));
    keyRegistered=true;
}

bool SnakeSFMLController::get_keyRegistered()
{
    return keyRegistered;
}

void SnakeSFMLController::reset_keyRegistered()
{
    keyRegistered=false;
}

Facing SnakeSFMLController::choose_facing(sf::Event &event)
{
    Facing f;
    switch(event.key.code)
    {
        case sf::Keyboard::Up:
            f = UP;
            break;
        case sf::Keyboard::Down:
            f = DOWN;
            break;
        case sf::Keyboard::Left:
            f = LEFT;
            break;
        case sf::Keyboard::Right:
            f = RIGHT;
            break;
        default:
            f = snake.get_snake_facing();
    }
    return f;
}