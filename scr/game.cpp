#include "../include/snake/game.h"


void BufferToggle::Off() {
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void BufferToggle::On() {
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

bool IsEnd(Snake &snake) {
    std::pair<int, int> snake_head = snake.snake_head;
    return snake_head.first < 0 || snake_head.first >= MAP_WIDTH ||
           snake_head.second < 0 || snake_head.second >= MAP_HEIGHT ||
           snake.is_dead;
}

void StartLoop(BufferToggle &bf, Snake &snake, SnakeMap &snake_map) {
    bf.Off();
    while (true) {
        snake.UpdateMovement();
        if (IsEnd(snake)) {
            system("clear");
            std::cout << FRED("GAME  OVER") << std::endl;
            break;
        } else {
            snake_map.Draw();
            usleep(DELAY_TERMINAL);
            snake.ValidateDirection();
        }
    }
}

void StartGame(){
    Snake snake;
    SnakeMap snake_map(&snake);
    BufferToggle bf{};
    StartLoop(bf, snake, snake_map);
}

