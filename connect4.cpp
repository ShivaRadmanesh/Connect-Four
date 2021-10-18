#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <stdlib.h>
#define BOARD_ROWS 6
#define BOARD_COLS 7

void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorCoord;
	cursorCoord.X = x;
	cursorCoord.Y = y;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}
void clearScreen()
{
	system("cls");
}
void setTextColor(int textColor, int backColor = 0) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}
void printBoard() {
	setTextColor(10);
	printf("\n         Connect Four\n\n");
	setTextColor(8, 0);
	int row, col;
	for (row = 0; row < BOARD_ROWS; row++) {
		for (col = 0; col < BOARD_COLS; col++) {
			printf("|   ");
		}
		printf("|\n");
		for (int i = 0; i < BOARD_COLS; i++)
			printf(" %c%c%c", 205, 205, 205);
		printf("\n");
	}
	int k;
	for (k = 1; k <= BOARD_COLS; k++) {
		printf(" %2d ", k);
	}
	setTextColor(8, 0);
	gotoxy(32, 1);
	printf("                                   press (esc) to exit");
}
int check(int A[][BOARD_COLS], int x, int y) {
	int vertical = 1, horizontal = 1, diagonal1 = 1, diagonal2 = 1, i, j, m, n;
	int cur = A[x][y];
	for (i = x + 1; cur == A[i][y] && i < BOARD_ROWS && vertical < 4; i++, vertical++);
	if (vertical == 4) return(1);
	for (m = y; cur == A[x][m] && m < BOARD_COLS; m--);
	for (i = m + 2; cur == A[x][i] && i < BOARD_COLS && horizontal < 4; i++, horizontal++);
	if (horizontal == 4) return(1);
	for (m = x - 1, n = y + 1; cur == A[m][n] && m >= 0 && n < BOARD_COLS; m--, n++);
	for (i = m + 2, j = n - 2; cur == A[i][j] && i < BOARD_ROWS && j >= 0 && diagonal1 < 4; diagonal1++, i++, j--);
	if (diagonal1 == 4) return(1);
	for (m = x - 1, n = y - 1; cur == A[m][n] && m >= 0 && n >= 0; m--, n--);
	for (i = m + 2, j = n + 2; cur == A[i][j] && i < BOARD_ROWS && j < BOARD_COLS && diagonal2 < 4; diagonal2++, i++, j++);
	if (diagonal2 == 4)return(1);
	return(0);
}
int computerMove(int game[][BOARD_COLS]) {
	int col, row;
	for (col = 0; col < BOARD_COLS; col++) {
		for (row = BOARD_ROWS - 1; game[row][col] != 0 && row >= 0; row--);
		if (row >= 0) {
			game[row][col] = 1;
			if (check(game, row, col)) {
				game[row][col] = 0;
				return(col);
			}
			game[row][col] = 0;
		}
	}
	for (col = 0; col < BOARD_COLS; col++) {
		for (row = BOARD_ROWS - 1; game[row][col] != 0 && row >= 0; row--);
		if (row >= 0) {
			game[row][col] = 2;
			if (check(game, row, col)) {
				game[row][col] = 0;
				return(col);
			}
			game[row][col] = 0;
		}
	}
	do {
		col = rand() % BOARD_COLS;
		for (row = BOARD_ROWS - 1; game[row][col] != 0 && row >= 0; row--);
	} while (row<0);
	return(col);
}
void readFile(int game[][BOARD_COLS]) {
	FILE *inFile;
	inFile = fopen("game.dat", "rb");
	if (!inFile) {
		printf("There is no saved game!");
	}
	else {
		fread(game, sizeof(int), BOARD_COLS*BOARD_ROWS, inFile);
		setTextColor(8, 0);
		fclose(inFile);
	}
}
void writeFile(int game[][BOARD_COLS]) {
	FILE *outFile;
	outFile = fopen("game.dat", "wb");
	if (!outFile)
		printf("can't open the file!");
	fwrite(game, sizeof(int), BOARD_COLS*BOARD_ROWS, outFile);
	setTextColor(8, 0);
	printf("game succesfully saved!\n");
	fclose(outFile);
}
void printSavedGame(int game[][BOARD_COLS], int &type) {
	int i, j;
	type = -1;
	for (i = 0; i < BOARD_ROWS; i++) {
		for (j = 0; j < BOARD_COLS; j++) {
			if (game[i][j] == 1) {
				gotoxy(j * 4 + 2, i * 2 + 3);
				setTextColor(14, 0);
				printf("%c", 254);
				type++;
			}
			if (game[i][j] == 2) {
				gotoxy(j * 4 + 2, i * 2 + 3);
				setTextColor(12, 0);
				printf("%c", 254);
				type++;
			}
		}
	}
}