#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

const int width = 110; // 스테이지 너비
const int height = 20; // 스테이지 높이
const int gameSpeed = 110; // 게임 속도 (밀리초 단위)

bool isGameOver = false; // 게임 오버 여부
bool isGameStarted = false; // 게임 시작 여부

enum Direction { UP, DOWN, LEFT, RIGHT };
Direction dir;

struct Point
{
    int x;
    int y;
};

struct Wall
{
    int x;
    int y;
    Direction direction;
    int length;
};

Point food; // 먹이의 위치
vector<Point> snake; // 지렁이의 몸통
vector<Wall> walls; // 벽

int highScore = 0; // 최고 점수

void Setup();
void Draw();
void Input();
void Logic();
void MoveWalls();
void LoadHighScore();
void SaveHighScore();

void Setup()
{
    isGameOver = false;
    isGameStarted = false;
    dir = RIGHT;

    snake.clear();
    snake.push_back({ width / 2, height / 2 }); // 지렁이 초기 위치

    food.x = rand() % width;
    food.y = rand() % height;

    walls.clear();
    walls.push_back({ width - 1, height / 2, LEFT, rand() % 13 + 3 }); // 첫 번째 벽 생성

    highScore = 0;
    LoadHighScore();
}

void Draw()
{
    system("cls"); // 화면 지우기

    if (!isGameStarted)
    {
        cout << "========== Snake Game ==========" << endl;
        cout << "Press Spacebar to Start" << endl;
        cout << "===============================" << endl;
        return;
    }

    // 상단 벽
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // 스테이지 그리기
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (x == 0)
                cout << "#"; // 좌측 벽
            if (x == food.x && y == food.y)
                cout << "*"; // 먹이
            else
            {
                bool isBodyPart = false;
                for (auto body : snake)
                {
                    if (body.x == x && body.y == y)
                    {
                        cout << "O"; // 지렁이의 몸통
                        isBodyPart = true;
                        break;
                    }
                }
                if (!isBodyPart)
                {
                    bool isWallPart = false;
                    for (auto wall : walls)
                    {
                        if (wall.x == x && wall.y == y)
                        {
                            cout << "I"; // 벽
                            isWallPart = true;
                            break;
                        }
                    }
                    if (!isWallPart)
                        cout << " ";
                }
            }
            if (x == width - 1)
                cout << "#"; // 우측 벽
        }
        cout << endl;
    }

    // 하단 벽
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << (snake.size() - 1) << endl;
    cout << "Best Score: " << highScore << endl;

    // 게임 플레이 시간 표시
    if (isGameStarted && !isGameOver)
    {
        static auto startTime = std::chrono::steady_clock::now();
        auto currentTime = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        cout << "Time: " << deltaTime << "s" << endl;
    }
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case ' ':
            if (!isGameStarted)
                isGameStarted = true;
            break;
        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'a':
            if (dir != RIGHT)
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 'x':
            isGameOver = true;
            break;
        case 'r':
            if (isGameOver)
            {
                isGameOver = false;
                Setup();
            }
            break;
        }
    }
}

void Logic()
{
    if (!isGameStarted)
        return;

    Point prevHead = snake[0];
    Point newHead = prevHead;

    switch (dir)
    {
    case UP:
        newHead.y--;
        break;
    case DOWN:
        newHead.y++;
        break;
    case LEFT:
        newHead.x--;
        break;
    case RIGHT:
        newHead.x++;
        break;
    }

    // 지렁이 이동
    for (int i = snake.size() - 1; i > 0; i--)
        snake[i] = snake[i - 1];
    snake[0] = newHead;

    // 먹이 먹었는지 확인
    if (newHead.x == food.x && newHead.y == food.y)
    {
        // 먹이를 먹으면 길이가 1 증가
        snake.push_back(prevHead);

        // 새로운 먹이 생성
        food.x = rand() % width;
        food.y = rand() % height;

        // 점수 갱신
        int score = snake.size() - 1;
        if (score > highScore)
        {
            highScore = score;
            SaveHighScore();
        }

        // 벽 생성
        walls.push_back({ width - 1, rand() % height, LEFT, rand() % 13 + 3 });
    }

    // 자기 자신과의 충돌 확인
    for (int i = 1; i < snake.size(); i++)
    {
        if (snake[i].x == newHead.x && snake[i].y == newHead.y)
        {
            isGameOver = true;
            break;
        }
    }

    // 벽과의 충돌 확인
    for (auto wall : walls)
    {
        if (wall.x == newHead.x && wall.y == newHead.y)
        {
            isGameOver = true;
            break;
        }
    }

    // 벽 이동
    MoveWalls();

    // 벽과의 충돌 확인 (이동 후)
    for (auto wall : walls)
    {
        if (wall.x == newHead.x && wall.y == newHead.y)
        {
            isGameOver = true;
            break;
        }
    }

    // 벽을 지나친 벽 제거
    for (auto it = walls.begin(); it != walls.end();)
    {
        if (it->x < 0)
            it = walls.erase(it);
        else
            ++it;
    }

    // 스테이지 경계와의 충돌 확인
    if (newHead.x < 0 || newHead.x >= width || newHead.y < 0 || newHead.y >= height)
        isGameOver = true;
}

void MoveWalls()
{
    for (auto& wall : walls)
    {
        switch (wall.direction)
        {
        case LEFT:
            wall.x--;
            break;
        case RIGHT:
            wall.x++;
            break;
        }

        // 벽 길이에 따라 방향 전환
        if (wall.length > 0)
        {
            if (wall.direction == LEFT && wall.x < 0)
            {
                wall.direction = RIGHT;
                wall.x = 0;
                wall.length--;
            }
            else if (wall.direction == RIGHT && wall.x >= width)
            {
                wall.direction = LEFT;
                wall.x = width - 1;
                wall.length--;
            }
        }
    }
}

void LoadHighScore()
{
    ifstream file("highscore.txt");
    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
}

void SaveHighScore()
{
    ofstream file("highscore.txt");
    if (file.is_open())
    {
        file << highScore;
        file.close();
    }
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    Setup();

    while (!isGameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(gameSpeed);
    }

    cout << "Game Over!" << endl;
    cout << "Press 'R' to Restart or 'X' to Exit" << endl;

    while (true)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'r':
                isGameOver = false;
                Setup();
                while (!isGameOver)
                {
                    Draw();
                    Input();
                    Logic();
                    Sleep(gameSpeed);
                }
                break;
            case 'x':
                return 0;
            }
        }
    }

    return 0;
}