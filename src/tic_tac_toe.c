#include <stdbool.h>
#include <stdio.h>

char activePlayer = 'X';
int blankSpaces = 3 * 3;
char board[3][3] = {
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '}
};

void printBoard() {
	printf("\n+-+-+-+\n");
	for (int i = 0; i < 3; i++) {
		printf("|");
		for (int j = 0; j < 3; j++)
			printf("%c|", board[i][j]);
		printf("\n+-+-+-+\n");
	}
}

bool checkWin() {
	for (int i = 0; i < 3; i++) {
		if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
			printf("%c wins!\n", board[i][0]);
			return true;
		}
		if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
			printf("%c wins!\n", board[0][i]);
			return true;
		}
	}

	if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
		printf("%c wins!\n", board[0][0]);
		return true;
	}

	if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
		printf("%c wins!\n", board[0][2]);
		return true;
	}

	if (blankSpaces == 0) {
		printf("Tie.\n");
		return true;
	}

	return false;
}

void takeTurn() {
	printf("Where would you (%c) like to go (1-9): ", activePlayer);
	int playerAction = 0;
	scanf("%d", &playerAction);
	playerAction--;
	int row = playerAction / 3;
	int column = playerAction % 3;
	if (playerAction >= 0 && playerAction < 9 && board[row][column] == ' ') {
		board[row][column] = activePlayer;
		blankSpaces--;
		if (activePlayer == 'X') activePlayer = 'O';
		else activePlayer = 'X';
	} else printf("Invalid location.");
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
