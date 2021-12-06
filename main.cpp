#include <iostream>
#include <unistd.h>
#include "input.h"
#include "snake.h"
#include "snake_map.h"
#include <utility>
#include "head.h"
#include "color.h"

Snake snake;
SnakeMap snake_map(&snake);

void Initialize() {
    InputOff();
}

bool IsEnd() {
    bool result = false;
    std::pair<int, int> snake_head = snake.snake_head;
    return snake_head.first < 0 || snake_head.first >= MAP_WIDTH ||
        snake_head.second < 0 || snake_head.second >= MAP_HEIGHT ||
        snake.is_dead;
}

void GameOver() {

    std::cout << FRED("GAME  OVER") << std::endl;
    //cout << "\033[1;31mGAME  OVER\033[0m\n";

}

void StartGame() {
    while (true) {
        snake.UpdateMovement();
        if (IsEnd()) {
            GameOver();
            break;
        }
        snake_map.Draw();

        usleep(PAUSE_LENGTH);

        snake.ValidateDirection();
    }
}

int main() {
    Initialize();
    StartGame();
    return 0;
}
