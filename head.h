//
// Created by jc on 08.12.2021.
//
#ifndef SNAKE_HEAD_H
#define SNAKE_HEAD_H
#include <iostream>
#include <vector>
#include "termios.h"
#include <unistd.h>//ICANOT
#include <thread>

//colors
#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x)	"\x1B[1m" x RST
#define UNDL(x)	"\x1B[4m" x RST
//
#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define MAP_CHAR ' '
#define SNAKE_CHAR '/'
#define SNAKE_HEAD_WEST '<'
#define SNAKE_HEAD_NORTH '^'
#define SNAKE_HEAD_EAST '>'
#define SNAKE_HEAD_SOUTH 'v'
#define SNAKE_FOOD_CHAR 'O'
#define SNAKE_TAIL '~'
#define INITIAL_SNAKE_LENGTH 4

//-lpthread old vertion
//-pthread new vertion

#define DELAY_TERMINAL 250000 // 0.15 us
//
enum Direction {
    Error = -1,
    West = 0, North = 1, East = 2, South = 3
};
class BufferToggle {
private:
    struct termios t;
public:
    void Off();//Disables buffered input
    void On();//Enables buffered input
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

class SnakeMap {
public:
    SnakeMap(Snake *snake);
    void Draw();
    std::pair<int, int> snake_food;
    void UpdateSnakeFood(bool force_update);
    void UpdateScore();

private:
    char _map_array[MAP_HEIGHT][MAP_WIDTH];
    Snake* _snake;
};

void ClearMap(char map_array[MAP_HEIGHT][MAP_WIDTH]);
void UpdateSnakeHead(char map_array[MAP_HEIGHT][MAP_WIDTH], Snake *snake);
#endif //SNAKE_HEAD_H
