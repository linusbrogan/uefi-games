#include <stdbool.h>
#include "lblib.c"

char activePlayer = 'X';
int blankSpaces = 3 * 3;
char board[3][3] = {
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '}
};

void printBoard() {
	LB_print(TEXT("\n+-+-+-+\n"));
	for (int i = 0; i < 3; i++) {
		LB_print(TEXT("|"));
		for (int j = 0; j < 3; j++)
			LB_print(TEXT("%c|"), board[i][j]);
		LB_print(TEXT("\n+-+-+-+\n"));
	}
}

bool checkWin() {
	for (int i = 0; i < 3; i++) {
		if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
			LB_print(TEXT("%c wins!\n"), board[i][0]);
			return true;
		}
		if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
			LB_print(TEXT("%c wins!\n"), board[0][i]);
			return true;
		}
	}

	bool downDiagonalMatches = board[1][1] == board[0][0] && board[1][1] == board[2][2];
	bool upDiagonalMatches = board[1][1] == board[0][2] && board[1][1] == board[2][0];
	if (board[1][1] != ' ' && (downDiagonalMatches || upDiagonalMatches)) {
		LB_print(TEXT("%c wins!\n"), board[1][1]);
		return true;
	}

	if (blankSpaces == 0) {
		LB_print(TEXT("Tie.\n"));
		return true;
	}

	return false;
}

void takeTurn() {
	LB_print(TEXT("Where would you (%c) like to go (1-9): "), activePlayer);
	int playerAction = LB_readDigit();
	LB_print(TEXT("\n"));
	playerAction--;
	int row = playerAction / 3;
	int column = playerAction % 3;
	if (playerAction >= 0 && playerAction < 9 && board[row][column] == ' ') {
		board[row][column] = activePlayer;
		blankSpaces--;
		if (activePlayer == 'X') activePlayer = 'O';
		else activePlayer = 'X';
	} else LB_print(TEXT("Invalid location."));
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
