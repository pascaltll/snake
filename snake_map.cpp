//
// Created by jc on 08.12.2021.
//
#include "head.h"

SnakeMap::SnakeMap(Snake* snake){
    this->_snake = snake;
    ClearMap(this->_map_array);//rewrite matrix
    srand(time(nullptr));
    UpdateSnakeFood(true);
}

void SnakeMap::Draw(void) {
    ClearMap(this->_map_array);
    system("clear");//refesh terminal
    UpdateScore();

    std::vector<std::pair<int, int>> snake_parts = _snake->snake_parts;

    _map_array[snake_parts[0].first][snake_parts[0].second] = SNAKE_TAIL;//draw snake
    for (int i = 1; i < snake_parts.size(); i++) {
        _map_array[snake_parts[i].first][snake_parts[i].second] = SNAKE_CHAR;
    }

    UpdateSnakeHead(_map_array, _snake);
    UpdateSnakeFood(false);
    _map_array[snake_food.first][snake_food.second] = SNAKE_FOOD_CHAR;
    for (int i = 0; i < MAP_WIDTH + 1; ++i) {
        std::cout <<"+ ";
    }
    std::cout << std::endl;
    for (auto & i : _map_array) {//print matrixx
        std::cout <<"+";
        for (auto j : i) {
            if ( j == SNAKE_FOOD_CHAR) {
                std::cout << KGRN << j << FCYN(".");
            } else {
                std::cout << KYEL << j << FCYN(".");
            }

        }
        std::cout << "+" << std::endl;
    }
    for (int i = 0; i < MAP_WIDTH + 1; ++i) {
        std::cout <<"+ ";
    }
    std::cout << std::endl;
}

void SnakeMap::UpdateSnakeFood(bool force_update) {
    if (_snake->food_eaten || force_update) {
        while (true) {
            int random_i = rand() % MAP_WIDTH;
            int random_j = rand() % MAP_HEIGHT;
            if (_map_array[random_i][random_j] == MAP_CHAR) {
                snake_food = std::make_pair(random_i, random_j);
                _snake->SetSnakeFood(snake_food);
                _snake->food_eaten = false;
                break;
            }
        }
    }
}

void SnakeMap::UpdateScore(void){
    std::cout << FMAG("Score:") << _snake->length - INITIAL_SNAKE_LENGTH << std::endl;
}

void ClearMap(char map_array[MAP_HEIGHT][MAP_WIDTH]) {//re drawing matrix
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            /*if (i == MAP_HEIGHT - 1 || i == 0 || j == MAP_WIDTH - 1 || j == 0) {
                map_array[i][j] = MAP_BARRIER;
            } else {*/
            map_array[i][j] = MAP_CHAR;

        }
    }
}

void UpdateSnakeHead(char map_array[MAP_HEIGHT][MAP_WIDTH], Snake *snake) {
    char snake_head_char = SNAKE_CHAR;
    enum Direction direction = snake->GetDirection();
    switch (direction) {
        case West:
            snake_head_char = SNAKE_HEAD_WEST;
            break;
        case North:
            snake_head_char = SNAKE_HEAD_NORTH;
            break;
        case East:
            snake_head_char = SNAKE_HEAD_EAST;
            break;
        case South:
            snake_head_char = SNAKE_HEAD_SOUTH;
            break;
    }
    map_array[snake->snake_head.first][snake->snake_head.second] = snake_head_char;
}


