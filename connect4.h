#pragma once
#define BOARD_ROWS 6
#define BOARD_COLS 7
void gotoxy(int x, int y);
void setTextColor(int textColor, int backColor = 0);
void printBoard();
int check(int A[][BOARD_COLS], int x, int y);
int computerMove(int game[][BOARD_COLS]);
void readFile(int game[][BOARD_COLS]);
void writeFile(int game[][BOARD_COLS]);
void printSavedGame(int game[][BOARD_COLS], int &type);
void clearScreen();