#ifndef SNAKE_BUFFER_TOGGLE_H
#define SNAKE_BUFFER_TOGGLE_H

#include "snake.h"
#include "snake_map.h"
#include "termios.h"
#include <unistd.h>
#define DELAY_TERMINAL 150000



class BufferToggle {
private:
    struct termios t;
public:
    void Off();
    void On();
};
bool IsEnd(Snake &snake);
void StartLoop(BufferToggle &bf, Snake &snake, SnakeMap &snake_map);
void StartGame();

#endif //SNAKE_BUFFER_TOGGLE_H
