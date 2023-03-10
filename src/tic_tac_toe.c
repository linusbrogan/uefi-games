#include <efi.h>
#include <efilib.h>
#include <stdbool.h>
#include "efistub.h"
#include "io.h"

char activePlayer = 'X';
int blankSpaces = 3 * 3;
char board[3][3] = {
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '}
};

void printBoard() {
	Print(L"\n+-+-+-+\n");
	for (int i = 0; i < 3; i++) {
		Print(L"|");
		for (int j = 0; j < 3; j++)
			Print(L"%c|", board[i][j]);
		Print(L"\n+-+-+-+\n");
	}
}

bool checkWin() {
	for (int i = 0; i < 3; i++) {
		if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
			Print(L"%c wins!\n", board[i][0]);
			return true;
		}
		if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
			Print(L"%c wins!\n", board[0][i]);
			return true;
		}
	}

	bool downDiagonalMatches = board[1][1] == board[0][0] && board[1][1] == board[2][2];
	bool upDiagonalMatches = board[1][1] == board[0][2] && board[1][1] == board[2][0];
	if (board[1][1] != ' ' && (downDiagonalMatches || upDiagonalMatches)) {
		Print(L"%c wins!\n", board[1][1]);
		return true;
	}

	if (blankSpaces == 0) {
		Print(L"Tie.\n");
		return true;
	}

	return false;
}

void takeTurn() {
	Print(L"Where would you (%c) like to go (1-9): ", activePlayer);
	int playerAction = scanDigit();
	Print(L"\n");
	playerAction--;
	int row = playerAction / 3;
	int column = playerAction % 3;
	if (playerAction >= 0 && playerAction < 9 && board[row][column] == ' ') {
		board[row][column] = activePlayer;
		blankSpaces--;
		if (activePlayer == 'X') activePlayer = 'O';
		else activePlayer = 'X';
	} else Print(L"Invalid location.");
}

void playGame() {
	printBoard();
	while (!checkWin()) {
		takeTurn();
		printBoard();
	}
}

int main() {
	playGame();
	return 0;
}
