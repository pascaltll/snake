//
// Created by jc on 08.12.2021.
//

#include <thread>
#include "head.h"

Snake::Snake(void) {
    _direction = East;
    _next_direction = _direction;
    food_eaten = false;
    is_dead = false;
    length = INITIAL_SNAKE_LENGTH;
    ClearSnakeWorld();
    InitializeSnake();
    pthread_create(&_input_thread, NULL, InputThreadWork, this);//
    //std::thread t1(InputThreadWork(),this);

}

void Snake::UpdateDirection(enum Direction direction) {
    switch (direction) {
        case West:
            if (this->_direction != East) {
                this->_direction = direction;
            }
            break;
        case North:
            if (this->_direction != South) {
                this->_direction = direction;
            }
            break;
        case East:
            if (this->_direction != West) {
                this->_direction = direction;
            }
            break;
        case South:
            if (this->_direction != North) {
                this->_direction = direction;
            }
            break;
    }
}

void Snake::UpdateNextDirection(enum Direction direction) {
    this->_next_direction = direction;
}

enum Direction Snake::GetDirection(void) {
    enum Direction result = this->_direction;
    //sem_wait(&this->_snake_sema);

    result = this->_direction;

    //sem_post(&this->_snake_sema);
    return result;
}

void Snake::ValidateDirection(void) {
    if (_next_direction != Error) {
        UpdateDirection(_next_direction);
    }
}

void Snake::UpdateMovement(void) {
    std::pair<int, int> movement_part;
    enum Direction direction = GetDirection();
    switch (direction) {
        case West:
            movement_part = std::make_pair(snake_head.first, snake_head.second - 1);
            break;
        case North:
            movement_part = std::make_pair(snake_head.first - 1, snake_head.second);
            break;
        case East:
            movement_part = std::make_pair(snake_head.first, snake_head.second + 1);
            break;
        case South:
            movement_part = std::make_pair(snake_head.first + 1, snake_head.second);
            break;
    }
    snake_head = movement_part;
    snake_parts.push_back(movement_part);
    food_eaten = snake_head.first == _snake_food.first && snake_head.second == _snake_food.second;
    if (food_eaten) {//HEAD == FOOD
        length++;
    } else {
        std::pair<int, int> tail = snake_parts.front();
        _snake_world_array[tail.first][tail.second]--;
        snake_parts.erase(snake_parts.begin());
    }
    int head_value = ++_snake_world_array[snake_head.first][snake_head.second];
    if (head_value > 1) {
        is_dead = true;
    }
}

void Snake::SetSnakeFood(std::pair<int, int> snake_food) {
    this->_snake_food = snake_food;
}

void Snake::ClearSnakeWorld(void) {
    for (auto & i : _snake_world_array)
    {
        for (auto j : i) {
            j = 0;
        }
    }
}

void Snake::InitializeSnake(void) {
    for (int i = 0; i < INITIAL_SNAKE_LENGTH; i++) {
        std::pair<int, int> snake_part = std::make_pair(MAP_HEIGHT / 2,
                                                   MAP_WIDTH / 2 - (INITIAL_SNAKE_LENGTH / 2) + i);
        snake_parts.push_back(snake_part);
        _snake_world_array[snake_part.first][snake_part.second] = 1;
    }
    snake_head = snake_parts[snake_parts.size() - 1];
}