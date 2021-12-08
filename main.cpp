
#include "head.h"

//
void BufferToggle::Off() {
    tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
    t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}

void BufferToggle::On() {
    tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
    t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}
enum Direction GetInput() {
    enum Direction result = East;
    char user_input = getchar();
    std::cout <<user_input <<std::endl;
    switch (user_input) {

        case 'a':
            result = West;
            break;
        case 'w':
            result = North;
            break;
        case 'd':
            result = East;
            break;
        case 's':
            result = South;
            break;
        default:
            result = Error;
            break;
    }
    return result;
}

Snake snake;
SnakeMap snake_map(&snake);
BufferToggle bf{};

bool IsEnd() {
    std::pair<int, int> snake_head = snake.snake_head;//if is in the range
    return snake_head.first < 0 || snake_head.first >= MAP_WIDTH ||
           snake_head.second < 0 || snake_head.second >= MAP_HEIGHT ||
           snake.is_dead;
}

void GameOver() {
    system("clear");
    std::cout << FRED("GAME  OVER") << std::endl;
    //cout << "\033[1;31mGAME  OVER\033[0m\n";
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
        usleep(DELAY_TERMINAL);//microsecund
        snake.ValidateDirection();
    }
    //bf.On();
}

int main() {
    StartLoop();
    return 0;
}