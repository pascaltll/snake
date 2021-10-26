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
    std::vector<std::vector<size_t>> back_ground_;
public:
    BackGround();
    void PrintFrame();
};
class Snake: public BackGround {
private:
    size_t px;
    size_t py;
protected:
    std::vector<std::vector<size_t>> snake_;
public:
    Snake();
    void UpdatePosition();
    void DrawSnake(size_t flag);
    void OverLapping();
};
void Snake::OverLapping() {
    px = snake_[0][0];
    py = snake_[0][1];

}
void Snake::DrawSnake(size_t flag) {
    for (int i = 0; i < 2 ; ++i) {
        size_t x = snake_[i][0];
        size_t y = snake_[i][1];
        if(x != 0 && y != 0) {
            back_ground_[x][y];
        }
    }
}
void Snake::UpdatePosition() {

}
Snake::Snake() {
    snake_.resize(50, std::vector<size_t>(2));

    snake_[0][0] = 3;
    snake_[0][1] = 3;

    snake_[1][0] = 3 + 1;
    snake_[1][1] = 3;
}
BackGround::BackGround() {
    back_ground_.resize(50, std::vector<size_t>(50));
    for (size_t i = 0; i < 50; ++i) {
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

void MainLoop(BackGround & object_back_ground) {
    std::system("clear");//clear background
    object_back_ground.PrintFrame();
}

void Loop(BackGround & object_back_ground){
    size_t x = 0;
    while (x < 100) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        MainLoop(object_back_ground);
        x++;
    }
}
int main (){
    BackGround in_terminal;
    Snake snake;
    Loop(in_terminal);
    return 0;
}