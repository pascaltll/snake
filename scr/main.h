//
// Created by jc on 18.12.2021.
//
#ifndef SNAKE_MAIN_H
#define SNAKE_MAIN_H

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

#endif //SNAKE_MAIN_H
