#ifndef SNAKE_SNAKE_MAP_H
#define SNAKE_SNAKE_MAP_H

#include "snake.h"
#define MAP_CHAR ' '
#define SNAKE_CHAR '/'
#define SNAKE_HEAD_WEST '<'
#define SNAKE_HEAD_NORTH '^'
#define SNAKE_HEAD_EAST '>'
#define SNAKE_HEAD_SOUTH 'v'
#define SNAKE_FOOD_CHAR 'O'
#define SNAKE_TAIL '~'

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

#endif //SNAKE_SNAKE_MAP_H
