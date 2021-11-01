//
// Created by jc on 26.10.2021.
//
#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
//comentario git
class BackGround {
protected:
    std::vector<std::vector<int>> back_ground_;
public:
    BackGround();
    void PrintFrame();
};
class Snake: public BackGround {
private:
    int px;
    int py;
    int move_x;
    int move_y;
    
protected:
    std::vector<std::vector<int>> snake_;
public:
    Snake();
    void UpdatePosition();
    void DrawSnake(int flag);
    void OverLapping();
    void keyboard(const int k);
};
void Snake::OverLapping() {
    px = snake_[0][0];
    py = snake_[0][1];

}
void Snake::DrawSnake(int flag) {
    for (int i = 0; i < 2 ; ++i) {
        int x = snake_[i][0];
        int y = snake_[i][1];
        if(x != 0 && y != 0) {
            back_ground_[x][y] = flag;
        }
    }
}
void Snake::UpdatePosition() {
    

}
void Snake::keyboard(const int k) {
    if (k == '6') {
        move_x = 1;
        move_y = 0;
    } else if (k == '4') {
        move_x = -1;
        move_y = 0;
    } else if (k == '8') {
        move_x = 0;
        move_y = -1;
    } else if (k == '2') {
        move_x = 0;
        move_y = 1;
    }
}
Snake::Snake() {
    snake_.resize(50, std::vector<int>(2));

    snake_[0][0] = 3;
    snake_[0][1] = 3;

    snake_[1][0] = 3 + 1;
    snake_[1][1] = 3;
}
BackGround::BackGround() {
    back_ground_.resize(50, std::vector<int>(50));
    for (int i = 0; i < 50; ++i) {
        back_ground_[0][i] = 1;
        back_ground_[i][0] = 1;
        back_ground_[49][i] = 1;
        back_ground_[i][49] = 1;
    }
}

void BackGround::PrintFrame() {
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            if (back_ground_[i][j] == 1) {
                std::cout << 'o';
            } else if (back_ground_[i][j] == 2) {
                std::cout << "+";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void MainLoop(BackGround& object_back_ground, Snake& snake) {
    std::system("clear");//clear background
    snake.DrawSnake(1);
    object_back_ground.PrintFrame();
    snake.DrawSnake(0);
}

void Loop(BackGround & object_back_ground, Snake& snake){
    int x = 0;
    int input_keyboard;
    while (x < 100) {
        std::this_thread::sleep_for(std::chrono::seconds(1)/1);
        MainLoop(object_back_ground, snake);
        std::cin >> input_keyboard;
        std::system("clear");//clear background
        x++;
    }
}
int main (){
    BackGround in_terminal;
    Snake snake;
    Loop(in_terminal, snake);
    return 0;
}