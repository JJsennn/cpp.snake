#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <utility>
#include <conio.h>
#include <windows.h>
using namespace std;
constexpr int WIDTH = 20;
constexpr int HEIGHT = 20;
vector<string> board(HEIGHT + 2, string(WIDTH + 2, ' '));
struct point {
    int curx;
    int cury;
    point() : curx(0), cury(0) {}
    point(int x_, int y_) : curx(x_), cury(y_) {}
    bool operator==(const point& other) const {
        return curx == other.curx && cury == other.cury;
    }
};
point food(15, 10);
const pair<int, int> movemod[4] = {
    {1, 0},
    {0, 1},
    {-1, 0},
    {0, -1}
};
int direction = 0;
int score = 0;
void initializeBoard() {
    for (int i = 0; i < WIDTH + 2; ++i) {
        board[0][i] = '#';
        board[HEIGHT + 1][i] = '#';
    }
    for (int i = 0; i < HEIGHT + 2; ++i) {
        board[i][0] = '#';
        board[i][WIDTH + 1] = '#';
    }
}
void readKey(const deque<point>& s) {
    if (!_kbhit()) {
        return;
    }
    char choose = static_cast<char>(_getch());
    int newDirection = direction;
    switch (choose) {
        case 'd':
            newDirection = 0;
            break;
        case 's':
            newDirection = 1;
            break;
        case 'a':
            newDirection = 2;
            break;
        case 'w':
            newDirection = 3;
            break;
        default:
            return;
    }
    if (s.size() >= 2 && newDirection == (direction + 2) % 4) {
        return;
    }
    direction = newDirection;
}
bool createFood(const deque<point>& s) {
    if (s.size() >= WIDTH * HEIGHT) {
        return false;
    }
    while (true) {
        point candidate(
            rand() % WIDTH + 1,
            rand() % HEIGHT + 1
        );
        bool onSnake = false;
        for (const auto& body : s) {
            if (body == candidate) {
                onSnake = true;
                break;
            }
        }
        if (!onSnake) {
            food = candidate;
            return true;
        }
    }
}
bool moveSnake(deque<point>& s) {
    point next = s.front();
    next.curx += movemod[direction].first;
    next.cury += movemod[direction].second;
    s.push_front(next);
    if (s.front() == food) {
        score += 10;
        return createFood(s);
    }
    s.pop_back();
    return true;
}
bool isAlive(const deque<point>& s) {
    int x = s.front().curx;
    int y = s.front().cury;
    if (x < 0 || x >= WIDTH + 2 ||
        y < 0 || y >= HEIGHT + 2) {
        return false;
    }
    if (board[y][x] == '#') {
        return false;
    }
    for (size_t i = 1; i < s.size(); ++i) {
        if (s.front() == s[i]) {
            return false;
        }
    }
    return true;
}
void restoreset(){
    HANDLE hconsole=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position={0,0};
    SetConsoleCursorPosition(hconsole,position);
}
void render(const deque<point>& s) {
    restoreset();
    vector<string> tmp = board;
    tmp[food.cury][food.curx] = '*';
    int headX = s.front().curx;
    int headY = s.front().cury;
    if (headX >= 0 && headX < WIDTH + 2 &&
        headY >= 0 && headY < HEIGHT + 2) {
        tmp[headY][headX] = '@';
    }
    for (size_t i = 1; i < s.size(); ++i) {
        int x = s[i].curx;
        int y = s[i].cury;
        tmp[y][x] = 'O';
    }
    for (const auto& row : tmp) {
        cout << row << '\n';
    }
    cout << '\n';
    cout << "Score: " << score << '\n';
    cout << "Control: W/A/S/D\n";
}
int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    initializeBoard();
    deque<point> snake;
    snake.push_back({10, 10}); 
    snake.push_back({9, 10});
    snake.push_back({8, 10}); 
    cout<<"=======start=======\n";
    cout<<"按下任意键开始！！！"<<'\n';
    _getch();
    system("cls");
    render(snake);
    while (true) {
        readKey(snake);
        bool hasEmptyCell = moveSnake(snake);
        if (!isAlive(snake)) {
            render(snake);
            cout << "Game Over!\n";
            cout << "Final Score: " << score << '\n';
            break;
        }
        if (!hasEmptyCell) {
            render(snake);
            cout << "You Win!\n";
            cout << "Final Score: " << score << '\n';
            break;
        }
        render(snake);
        Sleep(120);
    }
    cout<<"按下空格结束";
    while(true){
        if(_kbhit()){
            char ch=static_cast<char>(_getch());
            if(ch==' ')
            break;
        }
    }
    return 0;
}