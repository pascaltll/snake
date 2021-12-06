//
// Created by jc on 06.12.2021.
//
#include "input.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>


struct termios t;

void InputOff(){
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

enum Direction GetInput() {
    enum Direction result = East;
    char user_input = getchar();
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


