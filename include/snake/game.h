
#ifndef SNAKE_BUFFER_TOGGLE_H
#define SNAKE_BUFFER_TOGGLE_H
#define DELAY_TERMINAL 150000
#include "termios.h"
#include <unistd.h>

class BufferToggle {
private:
    struct termios t;
public:
    void Off();
    void On();
};
bool IsEnd(Snake &snake);
void GameOver();
void StartLoop(BufferToggle &bf, Snake &snake, SnakeMap &snake_map);
void StartGame();
#endif //SNAKE_BUFFER_TOGGLE_H
