#include "Snake.h"
#include "SnakeBoard.h"
#include <chrono>
#include <thread>
#include "SnakeSFMLView.h"
#include "SnakeSFMLController.h"
#include <iostream>

int main() {

    Snake snake;
    SnakeBoard board(snake);
    std::chrono::milliseconds timespan(1);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(30);

    SnakeSFMLView view(snake, board);
    SnakeSFMLController ctrl(snake, board, view, window);

    board.debug_display();


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed and !ctrl.get_keyRegistered())
            {
                ctrl.play(event);
            }
        }
        board.update();
        if(board.get_wasUpdated())
        {
            ctrl.reset_keyRegistered();
            board.reset_wasUpdated();
        }

        window.clear();
        view.draw(window);
        window.display();
        if(snake.get_snake_status() == DEAD)
        {
            window.close();
        }
    }

    return 0;

}
