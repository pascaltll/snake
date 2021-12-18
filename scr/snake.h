//
// Created by jc on 18.12.2021.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"


#define FRED(x) KRED x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST

#define INITIAL_SNAKE_LENGTH 4
#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#include <vector>
#include <thread>
#include <iostream>

enum Direction {
    Error = -1,
    West = 0, North = 1, East = 2, South = 3
};
enum Direction GetInput();

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
    void SetSnakeFood(std::pair<int, int> snake_food);
    bool food_eaten;
    bool is_dead;
    int length;
    bool IsEnd();
private:
    pthread_t _input_thread;//
    std::thread _snake_thread;
    enum Direction _direction;
    enum Direction _next_direction;
    std::pair<int, int> _snake_food;
    int _snake_world_array[MAP_HEIGHT][MAP_WIDTH];
    void ClearSnakeWorld();
    void InitializeSnake();
};

#endif //SNAKE_SNAKE_H
