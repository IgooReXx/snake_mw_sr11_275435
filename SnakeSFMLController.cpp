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

void SnakeSFMLController::menu(sf::Event &event) {
    if(event.mouseButton.button != sf::Mouse::Left)
        return;

    float mouseXPos = event.mouseButton.x;
    float mouseYPos = event.mouseButton.y;

    sf::FloatRect buttonPlay = view.get_menuButtonPlay();
    sf::FloatRect buttonEasy = view.get_menuButtonEasy();
    sf::FloatRect buttonNormal = view.get_menuButtonNormal();
    sf::FloatRect buttonHard = view.get_menuButtonHard();

    if(mouse_is_within_button(mouseXPos, mouseYPos, buttonPlay))
    {
        board.set_status_running();
    }
    if(mouse_is_within_button(mouseXPos, mouseYPos, buttonEasy))
    {
        board.set_GameDifficulty(EASY);
    }
    if(mouse_is_within_button(mouseXPos, mouseYPos, buttonNormal))
    {
        board.set_GameDifficulty(NORMAL);
    }
    if(mouse_is_within_button(mouseXPos, mouseYPos, buttonHard))
    {
        board.set_GameDifficulty(HARD);
    }
}

bool SnakeSFMLController::mouse_is_within_button(float mouseXPos, float mouseYPos, sf::FloatRect button)
{
    if(!(mouseXPos >= button.left))
        return false;
    if(!(mouseXPos <= button.left + button.width))
        return false;
    if(!(mouseYPos >= button.top))
        return false;
    if(!(mouseYPos <= button.top + button.height))
        return false;
    return true;
}
