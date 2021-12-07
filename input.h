//
// Created by jc on 06.12.2021.
//

#ifndef SNAKE_INPUT_H
#define SNAKE_INPUT_H

enum Direction {
    Error = -1,
    West = 0, North = 1, East = 2, South = 3
};

void InputThread();
enum Direction GetInput();
#endif //SNAKE_INPUT_H
