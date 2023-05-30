#include "Snake.h"
#include "SnakeBoard.h"
#include <chrono>
#include <thread>
#include <iostream>

int main() {

    Snake snake;
    SnakeBoard board(snake);
    std::chrono::milliseconds timespan(1000);

    while(true)
    {
        board.debug_display();
        std::cout << std::endl;
        board.update();
        std::this_thread::sleep_for(timespan);
    }
}
