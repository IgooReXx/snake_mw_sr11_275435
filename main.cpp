#include "Snake.h"
#include "SnakeBoard.h"
#include <iostream>

int main() {

    Snake snake;
    SnakeBoard board(snake);

    board.debug_display();
    std::cout << std::endl;
    board.update();
    std::cout << std::endl;
    board.debug_display();

}
