#include "Snake.h"
#include "SnakeBoard.h"
#include "SnakeSFMLView.h"
#include "SnakeSFMLController.h"
#include <iostream>

int main() {

    Snake snake;
    SnakeBoard board(snake);
    sf::RenderWindow window(sf::VideoMode(800, 600), L"Karp jest król wód, jak lew jest król dżungli");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);

    SnakeSFMLView view(snake, board);
    SnakeSFMLController ctrl(snake, board, view, window);

    //board.debug_display();


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(snake.get_status()==DEAD)
                continue;
            else if (event.type == sf::Event::MouseButtonPressed and board.get_status() == MENU)
            {
                ctrl.menu(event);
            }
            else if(event.type == sf::Event::KeyPressed and !ctrl.get_keyRegistered())
            {
                ctrl.play(event);
            }
        }
        if(board.get_status() == RUNNING and snake.get_status() == ALIVE)
            board.update();

        if(board.get_wasUpdated())
        {
            ctrl.reset_keyRegistered();
            board.reset_wasUpdated();
        }

        window.clear();
        view.draw(window);
        window.display();

    }


    return 0;

}
