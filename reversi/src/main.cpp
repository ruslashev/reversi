#include "board.hpp"
#include <fstream>
#include <iostream>
#include <string>

void Game(Cell Board[8][8]);
void GetInput(int *x, int *y);

int main()
{
	puts("Welcome to Reversi!");
	puts("Coordinates are accepted in the format a:1, d4, 5f or 7:g etc.");
	puts("");
	Cell Board[8][8] = { { CELL_EMPTY } };

	Board[3][3] = CELL_WHITE;
	Board[3][4] = CELL_BLACK;
	Board[4][3] = CELL_BLACK;
	Board[4][4] = CELL_WHITE;

	Game(Board);

	return 0;
}

void Game(Cell Board[8][8])
{
	while (1) {
		Player CurrentPlayer = PLAYER_BLACK;
		DrawBoard(Board, CurrentPlayer);

		int x, y;
		GetInput(&x, &y);
		printf("x = %d, y = %d\n", x, y);

		break;
	}
}

void GetInput(int *x, int *y)
{
	while (1) {
		printf("Enter coordinates: ");
		std::string input;
		std::getline(std::cin, input);

		int i = 0;
		char c = input[i++];
		if (c >= 'a' && c <= 'h') {
			*x = c-'a';

			c = input[i++];

			if (c == ':')
				c = input[i++];

			if (c < '1' || c > '8') {
				puts("Invalid coordinates");
				continue;
			}

			*y = c-'1';
		} else if (c >= '1' && c <= '9') {
			*y = c-'1';

			c = input[i++];

			if (c == ':')
				c = input[i++];

			if (c < 'a' || c > 'h') {
				puts("Invalid coordinates");
				continue;
			}

			*x = c-'a';
		} else {
			puts("Invalid coordinates");
			continue;
		}

		if (input.size() > i) {
			puts("Invalid coordinates");
			continue;
		}

		break;
	}
}

