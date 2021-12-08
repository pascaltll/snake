//
// Created by jc on 08.12.2021.
//

#include "head.h"

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

void* InputThreadWork(void* current) {
    auto *snake = (struct Snake *)current;
    while (true) {
        enum Direction direction = GetInput();
        snake->UpdateNextDirection(direction);
    }
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
