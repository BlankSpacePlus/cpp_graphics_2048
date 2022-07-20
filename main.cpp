#include <graphics.h>
#include <conio.h>
#include <map>

using namespace std;

// 每一行格子的数量
#define MAX_SIZE 4
// 格子宽度
#define GRID_WIDTH 100
// 相邻格子间的间隔
# define INTERVAL 15
// 窗口宽度
#define WINDOW_SIZE MAX_SIZE*GRID_WIDTH+5*INTERVAL

// 颜色枚举
enum Color {
    SPACE = RGB(205, 193, 180),
    POW_1 = RGB(238, 228, 218),
    POW_2 = RGB(237, 224, 200),
    POW_3 = RGB(242, 177, 121),
    POW_4 = RGB(245, 149, 99),
    POW_5 = RGB(246, 124, 95),
    POW_6 = RGB(246, 94, 59),
    POW_7 = RGB(242, 177, 121),
    POW_8 = RGB(237, 204, 97),
    POW_9 = RGB(255, 0, 128),
    POW_10 = RGB(145, 0, 72),
    POW_11 = RGB(242, 17, 158),
    BACKGROUND = RGB(187, 173, 160),
    NUMBER = RGB(119, 110, 101),
};

// 每个方格的实际数据
int game_data[MAX_SIZE][MAX_SIZE];
// 每个方格的POINT实例
POINT position[MAX_SIZE][MAX_SIZE];
// int数值到Color枚举的map
map<int, Color> num2color;
// 方格的数值字符串(临时变量)
char number[5] = "";
// 读取到的键盘输入字符(临时变量)
char userKey;

/**
 * 随机生成每回合生成的数值
 * @return 2或者4
 */
int random_2_or_4();

/**
 * 随机在空白格子上生成新的2或者4
 */
void random();

/**
 * 游戏数据初始化
 */
void init();

/**
 * 游戏UI绘制
 */
void draw();

/**
 * 上移操作
 */
void moveUp();

/**
 * 下移操作
 */
void moveDown();

/**
 * 左移操作
 */
void moveLeft();

/**
 * 右移操作
 */
void moveRight();

/**
 * 键盘输入识别响应
 */
void keyPressControl();

int main() {
    // 创建一个窗口
    initgraph(WINDOW_SIZE, WINDOW_SIZE, SHOWCONSOLE);
    init();
    while (1) {
        draw();
        keyPressControl();
    }
    return 0;
}

int random_2_or_4() {
    return (rand() % 10 == 0) ? 4 : 2;
}

void random() {
    while (true) {
        int x = rand() % MAX_SIZE;
        int y = rand() % MAX_SIZE;
        if (game_data[x][y] == 0) {
            game_data[x][y] = random_2_or_4();
            break;
        }
    }
}

void init() {
    // 设置随机数种子
    srand(GetTickCount());
    //数据初始化
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            game_data[i][j] = 0;
        }
    }
    // map初始化
    num2color[0] = SPACE;
    num2color[2] = POW_1;
    num2color[4] = POW_2;
    num2color[8] = POW_3;
    num2color[16] = POW_4;
    num2color[32] = POW_5;
    num2color[64] = POW_6;
    num2color[128] = POW_7;
    num2color[256] = POW_8;
    num2color[512] = POW_9;
    num2color[1024] = POW_10;
    num2color[2048] = POW_11;
    // 初始化每个格子的左上角坐标
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            position[i][j].x = j * GRID_WIDTH + (j + 1) * INTERVAL;
            position[i][j].y = i * GRID_WIDTH + (i + 1) * INTERVAL;
        }
    }
    // 产生两个随机数据
    random();
    random();
}

void draw() {
    setbkcolor(Color::BACKGROUND);
    cleardevice();
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            setfillcolor(num2color[game_data[i][j]]);
            solidrectangle(position[i][j].x, position[i][j].y, position[i][j].x + GRID_WIDTH,
                           position[i][j].y + GRID_WIDTH);
            if (game_data[i][j] != 0) {
                sprintf(number, "%d", game_data[i][j]);
                setbkmode(TRANSPARENT);
                settextcolor(Color::NUMBER);
                settextstyle(50, 0, "黑体");
                outtextxy(position[i][j].x + (GRID_WIDTH - textwidth(number)) / 2, position[i][j].y + 25, number);
            }
        }
    }
}

void moveUp() {
    for (int i = 0; i < MAX_SIZE; i++) {
        int temp = 0;
        for (int j = 1; j < MAX_SIZE; j++) {
            if (game_data[j][i] != 0) {
                if (game_data[temp][i] == 0) {
                    game_data[temp][i] = game_data[j][i];
                    game_data[j][i] = 0;
                } else if (game_data[temp][i] == game_data[j][i]) {
                    game_data[temp][i] *= 2;
                    game_data[j][i] = 0;
                    temp++;
                } else {
                    game_data[temp + 1][i] = game_data[j][i];
                    if (temp + 1 != j) {
                        game_data[j][i] = 0;
                    }
                    temp++;
                }
            }
        }
    }
}

void moveDown() {
    for (int i = 0; i < MAX_SIZE; i++) {
        int temp = MAX_SIZE - 1;
        for (int j = MAX_SIZE - 2; j >= 0; j--) {
            if (game_data[j][i] != 0) {
                if (game_data[temp][i] == 0) {
                    game_data[temp][i] = game_data[j][i];
                    game_data[j][i] = 0;
                } else if (game_data[temp][i] == game_data[j][i]) {
                    game_data[temp][i] *= 2;
                    game_data[j][i] = 0;
                    temp--;
                } else {
                    game_data[temp - 1][i] = game_data[j][i];
                    if (temp - 1 != j) {
                        game_data[j][i] = 0;
                    }
                    temp--;
                }
            }
        }
    }
}

void moveLeft() {
    for (int i = 0; i < MAX_SIZE; i++) {
        int temp = 0;
        for (int j = 1; j < MAX_SIZE; j++) {
            if (game_data[i][j] != 0) {
                if (game_data[i][temp] == 0) {
                    game_data[i][temp] = game_data[i][j];
                    game_data[i][j] = 0;
                } else if (game_data[i][temp] == game_data[i][j]) {
                    game_data[i][temp] *= 2;
                    game_data[i][j] = 0;
                    temp++;
                } else {
                    game_data[i][temp + 1] = game_data[i][j];
                    if (temp + 1 != j) {
                        game_data[i][j] = 0;
                    }
                    temp++;
                }
            }
        }
    }
}

void moveRight() {
    for (int i = 0; i < MAX_SIZE; i++) {
        int temp = MAX_SIZE - 1;
        for (int j = MAX_SIZE - 2; j >= 0; j--) {
            if (game_data[i][j] != 0) {
                if (game_data[i][temp] == 0) {
                    game_data[i][temp] = game_data[i][j];
                    game_data[i][j] = 0;
                } else if (game_data[i][temp] == game_data[i][j]) {
                    game_data[i][temp] *= 2;
                    game_data[i][j] = 0;
                    temp--;
                } else {
                    game_data[i][temp - 1] = game_data[i][j];
                    if (temp - 1 != j) {
                        game_data[i][j] = 0;
                    }
                    temp--;
                }
            }
        }
    }
}

void keyPressControl() {
    _getch();
    userKey = _getch();
    switch (userKey) {
        case 'w':
        case 'W':
        case 72:
            moveUp();
            random();
            break;
        case 80:
        case 's':
        case 'S':
            moveDown();
            random();
            break;
        case 75:
        case 'a':
        case 'A':
            moveLeft();
            random();
            break;
        case 77:
        case 'd':
        case 'D':
            moveRight();
            random();
            break;
        default:
            break;
    }
}
