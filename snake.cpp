#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

// Game variables
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int dir; // 1: Left, 2: Right, 3: Up, 4: Down

void Setup() {
    gameOver = false;
    dir = 0; // Stop at start
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

void Draw() {
    // Clear the screen by resetting cursor to top-left
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    // Top wall
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Game grid
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#"; // Left wall

            if (i == y && j == x) {
                cout << "O"; // Snake head
            } else if (i == fruitY && j == fruitX) {
                cout << "F"; // Fruit
            } else {
                bool printed = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Snake tail
                        printed = true;
                    }
                }
                if (!printed) cout << " ";
            }

            if (j == width - 1) cout << "#"; // Right wall
        }
        cout << endl;
    }

    // Bottom wall
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    cout << "Score: " << score << " | Use W A S D to move, X to exit" << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
            case 'A':
                if (dir != 2) dir = 1; // Left
                break;
            case 'd':
            case 'D':
                if (dir != 1) dir = 2; // Right
                break;
            case 'w':
            case 'W':
                if (dir != 4) dir = 3; // Up
                break;
            case 's':
            case 'S':
                if (dir != 3) dir = 4; // Down
                break;
            case 'x':
            case 'X':
                gameOver = true;
                break;
        }
    }
}

void Logic() {
    // Move tail segments
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move head based on direction
    if (dir == 1) x--;
    if (dir == 2) x++;
    if (dir == 3) y--;
    if (dir == 4) y++;

    // Wrap around walls
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // Check if snake hits itself
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // Check if snake eats fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(120); // Controls game speed
    }

    cout << "\nGame Over! Final Score: " << score << endl;
    return 0;
}