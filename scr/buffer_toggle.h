//
// Created by jc on 18.12.2021.
//

#ifndef SNAKE_BUFFER_TOGGLE_H
#define SNAKE_BUFFER_TOGGLE_H
#include "termios.h"
#include <unistd.h>
class BufferToggle {
private:
    struct termios t;
public:
    void Off();
    void On();
};
#endif //SNAKE_BUFFER_TOGGLE_H
