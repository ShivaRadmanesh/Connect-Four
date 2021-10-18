#include "connect4.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <stdlib.h>

int main() {
	int game[BOARD_ROWS][BOARD_COLS] = { 0 };
	int type = 0;
	int i, j;
	int sw = 1;
	char answer1, answer2;
	char m;
	do {
		printf("do you want to continue the previous game(y/n)?\n");
		answer1 = getch();
	} while (answer1 != 'n'&&answer1 != 'y');
	if (answer1 == 'y') {
		readFile(game);
	}
	do {
		gotoxy(0, 3);
		printf("do you want to play with computer(y/n)?");
		answer2 = getch();
	} while (answer2 != 'n'&&answer2 != 'y');
	gotoxy(0, 0);
	clearScreen();
	printBoard();
	if (answer1 = 'y')
		printSavedGame(game, type);
	int x = 2, y = BOARD_ROWS * 2 + 6;
	gotoxy(x, y);
	switch (answer2) {
	case 'n':
		type = 0;
		do {
			if (type % 2 == 0) {
				setTextColor(14, 0);
				gotoxy(32, 1);
				printf("player1's turn!");
				gotoxy(x, y);
			}
			else {
				setTextColor(12, 0);
				gotoxy(32, 1);
				printf("player2's turn!");
				gotoxy(x, y);
			}
			gotoxy(x, y);
			int a = getch();
			switch (a) {
			case 75:

				setTextColor(8, 0);
				gotoxy(x, y - 3);
				printf("%d", (x + 2) / 4);
				if (x >= 6) x -= 4;
				setTextColor(10, 0);
				gotoxy(x, y - 3);
				printf("%d", (x + 2) / 4);
				break;
			case 77:
				setTextColor(8, 0);
				gotoxy(x, y - 3);
				printf("%d", (x + 2) / 4);
				if (x < BOARD_COLS * 3 + 3) x += 4;
				setTextColor(10, 0);
				gotoxy(x, y - 3);
				printf("%d", (x + 2) / 4);
				break;
			case 13: break;
			case 27:
				char b;
				do {
					gotoxy(2, BOARD_ROWS * 2 + 6);
					setTextColor(8, 0);
					printf("Do you want to save the game(y/n)?\n");
					b = getch();
				} while (b != 'n'&& b != 'y');
				if (b == 'y') {
					writeFile(game);
				}
				exit(0);
			}
			gotoxy(x, y);
			if (a == 13) {
				for (; game[(y - 8) / 2][(x - 2) / 4] != 0; y -= 2);
				if (y >= 8) {
					y -= 5;
					gotoxy(x, y);
					printf("%c", 254);
					game[(y - 3) / 2][(x - 2) / 4] = ((type % 2) + 1);
					if (check(game, (y - 3) / 2, (x - 2) / 4)) sw = 0;
					type++;
				}
				y = BOARD_ROWS * 2 + 6;
			}
		} while (sw && type < (BOARD_COLS*BOARD_COLS));
		if (!sw) {
			gotoxy(2, BOARD_ROWS * 2 + 6);
			setTextColor(10, 0);
			type--;
			printf("player%d won!\n", ((type % 2) + 1));
			setTextColor(8, 0);
		}
		else if (type == BOARD_COLS*BOARD_COLS) {
			setTextColor(10, 0);
			printf("tie!");
			setTextColor(8, 0);
		}
		break;

	case 'y':
		type = 0;
		setTextColor(14, 0);
		if (type == 0) {
			game[BOARD_ROWS - 1][((BOARD_COLS - 1) / 2)] = 1;
			gotoxy((BOARD_COLS - 1) * 2 + 2, (BOARD_ROWS - 1) * 2 + 3);
			printf("%c", 254);
			type++;
		}
		do {
			if (type % 2 == 0) {
				int col;
				int row;
				do {
					col = computerMove(game);
					for (row = BOARD_ROWS - 1; game[row][col] != 0; row--);
				} while (row<0);

				game[row][col] = 1;
				gotoxy(col * 4 + 2, row * 2 + 3);
				setTextColor(14, 0);
				printf("%c", 254);
				if (check(game, row, col)) sw = 0;
				type++;
			}
			else {
				gotoxy(x, y);
				int a = getch();
				switch (a) {
				case 75:

					setTextColor(8, 0);
					gotoxy(x, y - 3);
					printf("%d", (x + 2) / 4);
					if (x >= 6) x -= 4;
					setTextColor(10, 0);
					gotoxy(x, y - 3);
					printf("%d", (x + 2) / 4);
					break;
				case 77:
					setTextColor(8, 0);
					gotoxy(x, y - 3);
					printf("%d", (x + 2) / 4);
					if (x < BOARD_COLS * 3 + 3) x += 4;
					setTextColor(10, 0);
					gotoxy(x, y - 3);
					printf("%d", (x + 2) / 4);
					break;
				case 13: break;
				case 27:
					char b;
					do {
						gotoxy(2, BOARD_ROWS * 2 + 6);
						setTextColor(8, 0);
						printf("Do you want to save the game(y/n)?\n");
						b = getch();
					} while (b != 'n'&& b != 'y');
					if (b == 'y') {
						writeFile(game);
					}
					exit(0);
				}
				gotoxy(x, y);
				if (a == 13) {
					for (; game[(y - 8) / 2][(x - 2) / 4] != 0; y -= 2);
					if (y >= 8) {
						y -= 5;
						gotoxy(x, y);
						setTextColor(12, 0);
						printf("%c", 254);
						game[(y - 3) / 2][(x - 2) / 4] = 2;
						if (check(game, (y - 3) / 2, (x - 2) / 4)) sw = 0;
						type++;
					}
					y = BOARD_ROWS * 2 + 6;
				}
			}
		} while (sw && type < BOARD_COLS*BOARD_ROWS);
		if (!sw) {
			type--;
			gotoxy(2, BOARD_ROWS * 2 + 6);
			setTextColor(10, 0);
			if (type % 2 == 0) {
				printf("You lost:(\n");
				setTextColor(8, 0);
			}
			else {
				printf("You won:)\n");
				setTextColor(8, 0);
			}
		}
		else if (type == BOARD_COLS*BOARD_COLS) {
			printf("tie!\n");
			setTextColor(8, 0);
		}
		break;
	}
}
