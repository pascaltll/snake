#include "../scr/main.h"
#include "../scr/snake.h"
#include "../scr/snake_map.h"

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

Snake snake;
SnakeMap snake_map(&snake);
BufferToggle bf{};

bool IsEnd() {
    std::pair<int, int> snake_head = snake.snake_head;
    return snake_head.first < 0 || snake_head.first >= MAP_WIDTH ||
           snake_head.second < 0 || snake_head.second >= MAP_HEIGHT ||
           snake.is_dead;
}

void GameOver() {
    system("clear");
    std::cout << FRED("GAME  OVER") << std::endl;
}

void StartLoop() {
    bf.Off();
    while (true) {
        snake.UpdateMovement();
        if (IsEnd()) {
            GameOver();
            break;
        }
        snake_map.Draw();
        usleep(DELAY_TERMINAL);
        snake.ValidateDirection();
    }
}

int main(int argc, char* argv[]) {
    StartLoop();
    return 0;
}