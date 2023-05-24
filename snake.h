#include <graphics.h>
#include <iostream>
#include<iomanip>
#include<Windows.h>
#include<list>
#include<map>
#include<thread>
#define CELL_WIDTH 10
enum Direction {
    Up,
    Down,
    Left,
    Right,
};
bool IsKeyDown(int key);
void KeyboardControl();
void HandleLogic();
void Draw();
