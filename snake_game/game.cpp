#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

// Constants
const int columns = 40;       // Grid columns
const int rows = 20;          // Grid rows
const int MAX_SCORES = 100;   // Max high scores
const string SCORE_FILE = "game_scores.txt"; // High score file

// Game variables
bool gameover;
int score = 0;
int choice;
int x, y, fruit_x, fruit_y;
int tail_x[100], tail_y[100], n_tail = 0;
string playerName;

// High score arrays
string highScoreNames[MAX_SCORES];
int highScores[MAX_SCORES];
int highScoreCount = 0;

// Enum for direction
enum Direction { STOP = 0, UP, DOWN, LEFT, RIGHT };
Direction dir = STOP;

// Function declarations
void setup();
void grid();
void mainMenu();
void workingMenu();
void input();
void logic();
void handleMenuChoice();
void enterPlayerName();
void viewTopScores();
void renderGame();
void handleInput();
void updateGame();
void initGame();
void runGame();
void setCursorPos(int x, int y);
void saveScores();
void loadScores();

// Main function
int main() {
    loadScores();      // Load high scores at the start
    handleMenuChoice(); // Start menu navigation
    return 0;
}

// Function definitions

void setup() {
    gameover = false;
    dir = STOP;
    x = rows / 2;
    y = columns / 2;
    fruit_x = rand() % (rows - 2) + 1; // Generate fruit randomly
    fruit_y = rand() % (columns - 2) + 1;
    score = 0;
    n_tail = 0; // Reset snake tail length
    fill(begin(tail_x), end(tail_x), 0);
    fill(begin(tail_y), end(tail_y), 0);
}

void setCursorPos(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { (SHORT)y, (SHORT)x };
    SetConsoleCursorPosition(hOut, coord);
}

void grid() {
    setCursorPos(0, 0); // Reset cursor to the top-left of the console

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
                cout << "#"; // Border
            }
            else if (i == x && j == y) {
                cout << "O"; // Snake's head
            }
            else if (i == fruit_x && j == fruit_y) {
                cout << "$"; // Fruit
            }
            else {
                bool print = false;
                for (int k = 0; k < n_tail; k++) {
                    if (i == tail_x[k] && j == tail_y[k]) {
                        cout << "o"; // Snake's body
                        print = true;
                        break;
                    }
                }
                if (!print) cout << " ";
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void mainMenu() {
    cout << setw(10) << "" << "  <== SNAKE GAME ==> " << endl;
    cout << setw(10) << "" << "1. Enter your name." << endl;
    cout << setw(10) << "" << "2. View high scores." << endl;
    cout << setw(10) << "" << "3. Play Game." << endl;
    cout << setw(10) << "" << "0. Exit game." << endl;
    cout << setw(6) << "" << "Please choose an option (0-3): ";
    cin >> choice;
    system("cls");
}

void workingMenu() {
    while (true) {
        mainMenu();
        switch (choice) {
        case 1:
            enterPlayerName();
            break;
        case 2:
            viewTopScores();
            break;
        case 3:
            system("cls");
            initGame();
            runGame();
            break;
        case 0:
            saveScores();  // Save scores before exiting
            cout << "Exited the game..." << endl;
            exit(0);
            break;
        default:
            cout << "Invalid option. Try again." << endl;
            break;
        }
    }
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w': dir = UP; break;
        case 'a': dir = LEFT; break;
        case 's': dir = DOWN; break;
        case 'd': dir = RIGHT; break;
        }
    }
}

void logic() {
    int prev_x = tail_x[0];
    int prev_y = tail_y[0];
    tail_x[0] = x;
    tail_y[0] = y;
    int prev_2x, prev_2y;

    for (int i = 1; i < n_tail; i++) {
        prev_2x = tail_x[i];
        prev_2y = tail_y[i];
        tail_x[i] = prev_x;
        tail_y[i] = prev_y;
        prev_x = prev_2x;
        prev_y = prev_2y;
    }

    switch (dir) {
    case UP: x--; break;
    case DOWN: x++; break;
    case LEFT: y--; break;
    case RIGHT: y++; break;
    default: break;
    }

    if (x <= 0 || x >= rows - 1 || y <= 0 || y >= columns - 1) {
        gameover = true;
    }

    for (int i = 0; i < n_tail; i++) {
        if (x == tail_x[i] && y == tail_y[i]) {
            gameover = true;
        }
    }

    if (x == fruit_x && y == fruit_y) {
        score += 10;
        fruit_x = rand() % (rows - 2) + 1;
        fruit_y = rand() % (columns - 2) + 1;
        n_tail++;
    }
}

void initGame() {
    setup();
}

void renderGame() {
    grid();
}

void runGame() {
    while (!gameover) {
        input();
        logic();
        renderGame();
        this_thread::sleep_for(chrono::milliseconds(150));
    }

    cout << "Game Over! Final Score: " << score << endl;

    if (highScoreCount < MAX_SCORES) {
        highScoreNames[highScoreCount] = playerName;
        highScores[highScoreCount] = score;
        highScoreCount++;
    }

    sort(highScores, highScores + highScoreCount, greater<int>());

    cout << "Press 'r' to retry or 'm' to return to the main menu: ";
    char retryChoice = _getch();
    if (retryChoice == 'r') {
        setup(); // Reset the game
        runGame();
    }
    else {
        system("cls");
        handleMenuChoice();
    }
}

void saveScores() {
    ofstream file(SCORE_FILE);
    for (int i = 0; i < highScoreCount; i++) {
        file << highScoreNames[i] << " " << highScores[i] << endl;
    }
}

void loadScores() {
    ifstream file(SCORE_FILE);
    while (file >> highScoreNames[highScoreCount] >> highScores[highScoreCount]) {
        highScoreCount++;
    }
}

void enterPlayerName() {
    cout << "Enter your name: ";
    cin >> playerName;
    system("cls");
    cout << "WELCOME, PLAYER " << playerName << "!" << endl;
    cout << endl;
    handleMenuChoice();
}

void viewTopScores() {
    system("cls");
    cout << "Top Scores:" << endl;

    for (int i = 0; i < min(3, highScoreCount); i++) {
        cout << highScoreNames[i] << ": " << highScores[i] << endl;
    }

    cout << "Press any key to return to the main menu.";
    _getch();
    system("cls");
    handleMenuChoice();
}

void handleMenuChoice() {
    workingMenu();
}

