#include "../include/main.h"
#include "../include/snake.h"
#include "../include/snake_map.h"
#include "../include/snake/buffer_toggle.h"



bool IsEnd(Snake &snake) {
    std::pair<int, int> snake_head = snake.snake_head;
    return snake_head.first < 0 || snake_head.first >= MAP_WIDTH ||
           snake_head.second < 0 || snake_head.second >= MAP_HEIGHT ||
           snake.is_dead;
}

void GameOver() {
    system("clear");
    std::cout << FRED("GAME  OVER") << std::endl;
}

void StartLoop(BufferToggle &bf, Snake &snake, SnakeMap &snake_map) {
    bf.Off();
    while (true) {
        snake.UpdateMovement();
        if (IsEnd(snake)) {
            GameOver();
            break;
        }
        snake_map.Draw();
        usleep(DELAY_TERMINAL);
        snake.ValidateDirection();
    }
}

int main(int argc, char* argv[]) {
    Snake snake;
    SnakeMap snake_map(&snake);
    BufferToggle bf{};
    StartLoop(bf, snake, snake_map);
    return 0;
}