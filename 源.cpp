#include"snake.h"
using namespace std;
bool isGameRunning = true;
bool isGameRunning1 = true;
bool Maps[160][120] = { false };
class Wall {
protected:
    int left;
    int top;
    int right;
    int bottom;
public:
    Wall(int zuo,int ding,int you,int di):left(zuo*CELL_WIDTH),top(ding*CELL_WIDTH),right(you*CELL_WIDTH),bottom(di*CELL_WIDTH) {
        for (int i=0; i < 60; i++)Maps[30][30 + i] = true;
    }
    void DrawWall() {
        setfillcolor(BLACK);
        solidrectangle(left, top, right, bottom);
        setfillcolor(WHITE);
    }
};
Wall wall(30, 30,31,90);
class Food {
private:
    int sum = 0;
protected:
    int _x;
    int _y;
public:
    static int count;//用来随机生成特殊事物
    Food()
    {
        NewFood();
    }

    void Drawfood() {
        int left, top, right, bottom;
        left = _x * CELL_WIDTH;
        top = _y * CELL_WIDTH;
        right = (_x + 1) * CELL_WIDTH;
        bottom = (_y + 1) * CELL_WIDTH;
        setfillcolor(YELLOW);
        solidrectangle(left, top, right, bottom);
        //setfillcolor(WHITE);
    }
    void NewFood() {
        _x = rand() % (1600 / CELL_WIDTH);//保证画的是在方格上
        _y = rand() % (1200 / CELL_WIDTH);
        //if (Maps[_x][_y] == true)NewFood();

    }
    int GetX() { return _x; }
    int GetY() { return _y; }
    void friend_change_sum();
    int back_sum() { return sum; }
};
void Food::friend_change_sum() {
    sum = rand() % 20;
}
int Food::count = 0;
class Puple_Food :public Food {
public:
    Puple_Food() {
        _x = rand() % (1600 / CELL_WIDTH);//保证画的是在方格上
        _y = rand() % (1000 / CELL_WIDTH);
    }
    void Drawfood() {
        int left, top, right, bottom;
        left = _x * CELL_WIDTH;
        top = _y * CELL_WIDTH;
        right = (_x + 1) * CELL_WIDTH;
        bottom = (_y + 1) * CELL_WIDTH;
        setfillcolor(MAGENTA);
        solidrectangle(left, top, right, bottom);
        setfillcolor(WHITE);
    }
    void NewFood() {
        _x = rand() % (1600 / CELL_WIDTH);//保证画的是在方格上
        _y = rand() % (1000 / CELL_WIDTH);
    }
    void clear() {
        _x = -1;
        _y = 1;
    }
private:
};

Food food;

Puple_Food food2;

class Snake {
protected:
    list<POINT>_bodyList;
    Direction _dir;
    int Case1;
    int speed;
    int score;
public:
    Snake() {
        speed = 250;
        Case1 = 0;
        score = 0;
    }//构造函数

};

class Snake_P2;
class Snake_P1 :public Snake {
public:
    Snake_P1() :Snake() {
        POINT head = { 150,5 };//初始化蛇的坐标
        POINT p1 = { 149,5 };
        POINT p2 = { 148,5 };
        _dir = Right;
        _bodyList.push_back(head);
        _bodyList.push_back(p1);
        _bodyList.push_back(p2);
        key = false;
    }
    void Update();
    void DrawSnake();
    void ChangeDirection(Direction dir);
    void Eat(Food& food, Puple_Food& food2);
    bool isGameover(Snake_P2& p2);
    void Speed_up();
    POINT* back_List();
    void Reset();
    bool Gameover() {
        key = true;
        return key;
    }
    bool getkey() { return key; }
protected:
    bool key;
};

void Snake_P1::DrawSnake() {
    for (list<POINT>::iterator it = _bodyList.begin(); it != _bodyList.end(); ++it) {
        setfillcolor(RED);
        solidrectangle((it->x) * CELL_WIDTH, (it->y) * CELL_WIDTH, (it->x + 1) * CELL_WIDTH, (it->y + 1) * CELL_WIDTH);
    }
}

void Snake_P1::Update() {
    int xOffset[4] = { 0, 0, -1, 1 };         // 与Direction对应的x轴位移
    int yOffset[4] = { -1, 1, 0, 0 };         // 与Direction对应的x轴位移​

    static int lastMoveTick = 0;              //使用静态变量
    int curTick = GetTickCount();             //获取当前时间
    if (curTick - lastMoveTick < speed)return;
    lastMoveTick = curTick;

    list<POINT>::iterator it = _bodyList.begin();
    int prevX = it->x; // 记录头部坐标
    int prevY = it->y;
    it->x += xOffset[_dir]; // 修改头部坐标
    it->y += yOffset[_dir];
    it++;
    for (; it != _bodyList.end(); ++it) {
        //后续结点全部往前移动
        int curX = it->x;
        int curY = it->y;
        it->x = prevX;
        it->y = prevY;
        prevX = curX;
        prevY = curY;
    }
}

void Snake_P1::ChangeDirection(Direction dir) {
    if (_dir == Direction::Up && dir == Direction::Down
        || _dir == Direction::Down && dir == Direction::Up
        || _dir == Direction::Right && dir == Direction::Left
        || _dir == Direction::Left && dir == Direction::Right)
    {
        return;        // 需要判断蛇不能向反方向运动
    }
    _dir = dir;
}

void Snake_P1::Eat(Food& food, Puple_Food& food2) {
    POINT headPos = *_bodyList.begin();
    if (headPos.x == food.GetX() && headPos.y == food.GetY()) {
        food.NewFood();
        POINT end = _bodyList.back();
        _bodyList.push_back(end);//直接将尾巴复制过来，所以不会立即长一节。
        score += 10;
        if (food.back_sum() != 0)(Food::count++);
        if (Food::count == food.back_sum() && Food::count != 0) {
            food2.NewFood();
            Food::count = 0;
        }
    }
    if (headPos.x == food2.GetX() && headPos.y == food2.GetY()) {
        food2.clear();
        food.friend_change_sum();
    }
    return;
}


Snake_P1 snake1;

POINT* Snake_P1::back_List() {
    return  &_bodyList.front();
}

class Snake_P2 :public Snake {
public:
    Snake_P2() :Snake() {
        POINT head = { 55,55 };
        POINT p1 = { 56,55 };
        POINT  p2 = { 57,55 };
        _dir = Left;
        _bodyList.push_back(head);
        _bodyList.push_back(p1);
        _bodyList.push_back(p2);
        key = false;
    }
    void Update();
    void DrawSnake();
    void ChangeDirection(Direction dir);
    void Eat(Food& food, Puple_Food& food2);
    bool isGameover(Snake_P1& p1);
    void Speed_up();//加速
    POINT* back_List();//获取首地址
    bool Gameover() {
        key = true;
        return key;
    }//挂了
    bool getkey() {
        return key;
    }
    void Reset();
protected:
    bool key;
};

bool Snake_P1::isGameover(Snake_P2& p2) {
    POINT headPos1 = *_bodyList.begin();
    list<POINT>::iterator it1 = _bodyList.begin();
    it1++;
    cout << headPos1.x;
    if (headPos1.x < 0 || headPos1.x>1600 / CELL_WIDTH)return true;
    if (headPos1.y < 0 || headPos1.y>1000 / CELL_WIDTH)return true;
    POINT headPos2 = *p2.back_List();
    for (; it1 != _bodyList.end(); ++it1) {
        if (headPos2.x == it1->x && headPos2.y == it1->y)p2.Gameover();
        if (it1->x == headPos1.x && it1->y == headPos1.y)return true;
    }
    //if (headPos1.x >= 30 && headPos1.x <31 && headPos1.y >= 30 && headPos1.y <= 90)return true;
    if (Maps[headPos1.x][headPos1.y])return true;
    return false;
}

void Snake_P1::Speed_up() {
    if (Case1 == 0) {
        speed = 125;
        Case1 = 1;
    }
    else {
        speed = 250;
        Case1 = 0;
    }
}

void Snake_P1::Reset() {
    Sleep(600);
    _bodyList.clear();
    POINT head = { 2,5 };//初始化蛇的坐标
    POINT p1 = { 1,5 };
    POINT p2 = { 0,5 };
    _dir = Right;
    _bodyList.push_back(head);
    _bodyList.push_back(p1);
    _bodyList.push_back(p2);
    key = false;
}

void Snake_P2::DrawSnake() {
    for (list<POINT>::iterator it = _bodyList.begin(); it != _bodyList.end(); ++it) {
        setfillcolor(BLUE);
        solidrectangle((it->x) * CELL_WIDTH, (it->y) * CELL_WIDTH, (it->x + 1) * CELL_WIDTH, (it->y + 1) * CELL_WIDTH);
    }
}

void Snake_P2::Update() {
    int xOffset[4] = { 0, 0, -1, 1 };         // 与Direction对应的x轴位移
    int yOffset[4] = { -1, 1, 0, 0 };         // 与Direction对应的x轴位移​

    static int lastMoveTick = 0;              //使用静态变量
    int curTick = GetTickCount();             //获取当前时间
    if (curTick - lastMoveTick < speed)return;
    lastMoveTick = curTick;

    list<POINT>::iterator it = _bodyList.begin();
    int prevX = it->x; // 记录头部坐标
    int prevY = it->y;
    it->x += xOffset[_dir]; // 修改头部坐标
    it->y += yOffset[_dir];
    it++;
    for (; it != _bodyList.end(); ++it) {
        //后续结点全部往前移动
        int curX = it->x;
        int curY = it->y;
        it->x = prevX;
        it->y = prevY;
        prevX = curX;
        prevY = curY;
    }
}

void Snake_P2::ChangeDirection(Direction dir) {
    if (_dir == Direction::Up && dir == Direction::Down
        || _dir == Direction::Down && dir == Direction::Up
        || _dir == Direction::Right && dir == Direction::Left
        || _dir == Direction::Left && dir == Direction::Right)
    {
        return;        // 需要判断蛇不能向反方向运动
    }
    _dir = dir;
}

void Snake_P2::Eat(Food& food, Puple_Food& food2) {
    POINT headPos = *_bodyList.begin();
    if (headPos.x == food.GetX() && headPos.y == food.GetY()) {
        food.NewFood();
        POINT end = _bodyList.back();
        _bodyList.push_back(end);//直接将尾巴复制过来，所以不会立即长一节。
        score += 10;
        if (food.back_sum() != 0)(Food::count++);
        if (Food::count == food.back_sum() && Food::count != 0) {
            food2.NewFood();
            Food::count = 0;
        }
    }
    if (headPos.x == food2.GetX() && headPos.y == food2.GetY()) {
        food2.clear();
        food.friend_change_sum();
    }
}

bool Snake_P2::isGameover(Snake_P1& p1) {
    POINT headPos = *_bodyList.begin();
    list<POINT>::iterator it = _bodyList.begin();
    it++;
    if (headPos.x < 0 || headPos.x>1600 / CELL_WIDTH)return true;
    if (headPos.y < 0 || headPos.y>1000 / CELL_WIDTH)return true;
    POINT headPos1 = *p1.back_List();
    for (; it != _bodyList.end(); ++it) {
        if (headPos1.x == it->x && headPos1.y == it->y)p1.Gameover();
        if (it->x == headPos.x && it->y == headPos.y)return true;
    }

    return false;
}

void Snake_P2::Speed_up() {
    if (Case1 == 0) {
        speed = 125;
        Case1 = 1;
    }
    else {
        speed = 250;
        Case1 = 0;
    }
}

POINT* Snake_P2::back_List() {
    return  &_bodyList.front();
}

void Snake_P2::Reset() {
    _bodyList.clear();
    Sleep(600);
    POINT head = { 55,55 };
    POINT p1 = { 56,55 };
    POINT  p2 = { 57,55 };
    _dir = Left;
    _bodyList.push_back(head);
    _bodyList.push_back(p1);
    _bodyList.push_back(p2);
    key = false;
}

Snake_P2 snake2;

bool IsKeyDown(int key)
{
    return (GetAsyncKeyState(key) & 0x8000 ? 1 : 0);
}

void KeyboardControl()
{
    static bool isLShiftDown = false; // 标志左 Shift 键是否被按下过
    static bool isRShiftDown = false; // 标志右 Shift 键是否被按下过
    if (IsKeyDown(VK_ESCAPE)) // esc键按下则退出循环结束游戏
    {
        isGameRunning = false;
        return;
    }
    if (IsKeyDown(VK_LEFT))
    {
        // 按左键向左移动
        snake1.ChangeDirection(Direction::Left);
    }
    if (IsKeyDown(VK_RIGHT))
    {
        snake1.ChangeDirection(Direction::Right);
    }
    if (IsKeyDown(VK_UP))
    {
        snake1.ChangeDirection(Direction::Up);
    }
    if (IsKeyDown(VK_DOWN))
    {
        snake1.ChangeDirection(Direction::Down);
    }
    if (IsKeyDown(VK_RSHIFT))
    {
        if (!isRShiftDown) {
            snake1.Speed_up();
        }
        isRShiftDown = true;
    }
    else {
        isRShiftDown = false;
    }
    if (IsKeyDown('A')) {
        snake2.ChangeDirection(Direction::Left);
    }
    if (IsKeyDown('D')) {
        snake2.ChangeDirection(Direction::Right);
    }
    if (IsKeyDown('S')) {
        snake2.ChangeDirection(Direction::Down);
    }
    if (IsKeyDown('W')) {
        snake2.ChangeDirection(Direction::Up);
    }
    if (IsKeyDown(VK_LSHIFT))
    {
        if (!isLShiftDown) {
            snake2.Speed_up();
        }
        isLShiftDown = true;
    }
    else {
        isLShiftDown = false;
    }
}

void HandleLogic() {
    snake1.Update();
    snake1.Eat(food, food2);
    if (snake1.isGameover(snake2) || snake1.getkey()) {
        snake1.Reset();
    }
    snake2.Update();
    snake2.Eat(food, food2);
    if (snake2.isGameover(snake1) || snake2.getkey()) {
        snake2.Reset();
    }
}

void DrawFirm() {
    for (int x = 0; x <= 1600; x += CELL_WIDTH) {
        line(x, 0, x, 1000);
    }
    for (int y = 0; y <= 1000; y += CELL_WIDTH) {
        line(0, y, 1600, y);
    }
}

void Draw() {
    cleardevice();
    DrawFirm();
    food.Drawfood();
    food2.Drawfood();
    snake1.DrawSnake();
    snake2.DrawSnake();
    //wall.DrawWall();
}

int main()
{
    initgraph(1600, 1000);
    //  设置背景色
    setbkcolor(RGB(164, 225, 202));
    //  使用背景色清空窗体
    cleardevice();
    while (isGameRunning)
    {
        while (isGameRunning1) {
            KeyboardControl();           // 处理键盘操作
            HandleLogic();              // 处理游戏逻辑
            Draw();                    // 处理所有绘制
            Sleep(30);                // 等待30毫秒，控制帧率
        }
    }
    closegraph();
    return 0;
}