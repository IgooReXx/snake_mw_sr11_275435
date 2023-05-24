#include "Snake.h"
#include "SnakeBoard.h"
#include "SnakeSFMLView.h"
#include "SnakeSFMLController.h"
#include <iostream>

int main() {

    Snake snake;
    SnakeBoard board(snake);

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
            else if(event.type == sf::Event::KeyPressed)
                ctrl.play(event);
        }

        window.clear();
        view.draw(window);
        window.display();
    }

    return 0;

}
