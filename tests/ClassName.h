//
// Created by jc on 09.12.2021.
//

#ifndef SNAKE_CLASSNAME_H
#define SNAKE_CLASSNAME_H


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
Snake::Snake(void) {
    _direction = East;
    _next_direction = _direction;
    food_eaten = false;
    is_dead = false;
    length = INITIAL_SNAKE_LENGTH;
    ClearSnakeWorld();
    InitializeSnake();
    //pthread_create(&_input_thread, NULL, InputThreadWork, this);//old option not compatible with cmake
    _snake_thread = std::thread([this](){//compatible form
        auto *snake = (struct Snake *)this;
        while (true) {
            enum Direction direction = GetInput();
            if(direction == 4){//just a solution for loop
                break;
            }
            snake->UpdateNextDirection(direction);
        }
        return this;

    });
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
    result = this->_direction;
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
bool Snake::IsEnd() {
    bool result = false;
    //if is in the range
    return snake_head.first < 0 || snake_head.first >= MAP_WIDTH ||
           snake_head.second < 0 || snake_head.second >= MAP_HEIGHT ||
           is_dead;
}



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

Snake snake;
SnakeMap snake_map(&snake);
BufferToggle bf{};

bool IsEnd() {
    std::pair<int, int> snake_head = snake.snake_head;//if is in the range
    return snake_head.first < 0 || snake_head.first >= MAP_WIDTH ||
           snake_head.second < 0 || snake_head.second >= MAP_HEIGHT ||
           snake.is_dead;
}

void GameOver() {
    system("clear");
    std::cout << FRED("GAME  OVER") << std::endl;
    //cout << "\033[1;31mGAME  OVER\033[0m\n";
}

void StartLoop() {
    bf.Off();
    while (true) {
        snake.UpdateMovement();
        if (IsEnd()) {
            GameOver();
            break;
        }
        snake_map.Draw();
        usleep(DELAY_TERMINAL);//microsecund
        snake.ValidateDirection();
    }
    //bf.On();
}
//new main
void StartGame(){
    StartLoop();
}

#endif //SNAKE_CLASSNAME_H
