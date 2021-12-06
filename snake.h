//
// Created by jc on 06.12.2021.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include "input.h"
#include <thread>
#include <semaphore.h>
#include <vector>
#include <utility>
#include "head.h"

using namespace std;

class Snake {
public:
    Snake();
    void UpdateDirection(enum Direction direction);
    void UpdateNextDirection(enum Direction direction);
    enum Direction GetDirection();
    void ValidateDirection();
    std::vector<std::pair<int, int>> snake_parts;
    std::pair<int, int> snake_head;
    void UpdateMovement();
    void SetSnakeFood(pair<int, int> snake_food);
    bool food_eaten;
    bool is_dead;
    int length;

private:
    pthread_t _input_thread;
    sem_t _snake_sema;
    enum Direction _direction;
    enum Direction _next_direction;
    std::pair<int, int> _snake_food;
    int _snake_world_array[MAP_HEIGHT][MAP_WIDTH];
    void ClearSnakeWorld();
    void InitializeSnake();
};
#endif //SNAKE_SNAKE_H
