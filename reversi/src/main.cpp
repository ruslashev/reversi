#include "board.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

void Game(Cell Board[8][8]);
void GetInput(int *x, int *y);

int main()
{
	puts("Welcome to Reversi!");
	puts("Coordinates are accepted in the format a:1, d4, 5f or 7:g etc.");
	puts("Enter \"q\" to quit");
	puts("");

	Cell Board[8][8] = { { CELL_EMPTY } };

	Board[3][3] = CELL_WHITE;
	Board[3][4] = CELL_BLACK;
	Board[4][3] = CELL_BLACK;
	Board[4][4] = CELL_WHITE;

	Game(Board);

	return 0;
}

void Game(Cell nBoard[8][8])
{
	Cell Board[8][8];
	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 8; x++)
			Board[y][x] = nBoard[y][x];

	int blackScore = 0, whiteScore = 0;
	Player CurrentPlayer = PLAYER_BLACK;
	while (1) {
		int legalMoves = 0;
		DrawBoard(Board, CurrentPlayer, &legalMoves);

		if (legalMoves == 0) {
			puts("");
			puts("GAME END");
			printf("%d:%d\n", blackScore, whiteScore);
			if (blackScore > whiteScore)
				puts("Player Black won!");
			else if (whiteScore > blackScore)
				puts("Player White won!");
			else
				puts("Tie!");

			break;
		}

		printf("Score: %d:%d\n", blackScore, whiteScore);
		printf("%s's move\n", CurrentPlayer == PLAYER_BLACK ? "Black" : "White");

		int x, y;
		GetInput(&x, &y);
		while (!LegalToPlace(x, y, Board, CurrentPlayer)) {
			puts("Illegal move");
			GetInput(&x, &y);
		}
		int score = Flip(x, y, &Board, CurrentPlayer);
		if (CurrentPlayer == PLAYER_BLACK) {
			blackScore += score;
			CurrentPlayer = PLAYER_WHITE;
		} else {
			whiteScore += score;
			CurrentPlayer = PLAYER_BLACK;
		}
		printf("\n");
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
		} else if (c == 'q') {
			exit(0);
		} else {
			puts("Invalid coordinates");
			continue;
		}

		if (input.size() > (unsigned int)i) {
			puts("Invalid coordinates");
			continue;
		}

		break;
	}
}

