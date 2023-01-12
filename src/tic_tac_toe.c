#include <stdbool.h>
#include <stdio.h>

//COULD MAYBE ADD AI??
int main() {
	//init tacBoard
	char tacBoard[3][3] = { { ' ', ' ', ' ' }, { ' ', ' ', ' ' }, { ' ', ' ', ' ' } }, currSym = ' ';
	int usOpt, playTurn = 0;
	while (true) {
		int spcCnt = 9;
		//board
		printf("\n");
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				printf("%c ", tacBoard[i][j]);
			}
			printf("\n");
		}
		//Check win/tie
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (tacBoard[i][j] != ' '){
					spcCnt--;
				}
			}
		}
		if (spcCnt == 0) {
			printf("Tie\n");
			break;
		}
		if (tacBoard[0][0] == tacBoard[0][1] && tacBoard[0][0] == tacBoard[0][2] && tacBoard[0][0] != ' ') {
			printf("%c wins!!!\n", tacBoard[0][0]);
			break;
		}
		else if (tacBoard[1][0] == tacBoard[1][1] && tacBoard[1][0] == tacBoard[1][2] && tacBoard[1][0] != ' ') {
			printf("%c wins!!!\n", tacBoard[1][0]);
			break;
		}
		else if (tacBoard[2][0] == tacBoard[2][1] && tacBoard[2][0] == tacBoard[2][2] && tacBoard[2][0] != ' ') {
			printf("%c wins!!!\n", tacBoard[2][0]);
			break;
		}
		else if (tacBoard[0][0] == tacBoard[1][0] && tacBoard[0][0] == tacBoard[2][0] && tacBoard[0][0] != ' ') {
			printf("%c wins!!!\n", tacBoard[0][0]);
			break;
		}
		else if (tacBoard[0][1] == tacBoard[1][1] && tacBoard[0][1] == tacBoard[2][1] && tacBoard[0][1] != ' ') {
			printf("%c wins!!!\n", tacBoard[0][1]);
			break;
		}
		else if (tacBoard[0][2] == tacBoard[1][2] && tacBoard[0][2] == tacBoard[2][2] && tacBoard[0][2] != ' ') {
			printf("%c wins!!!\n", tacBoard[0][2]);
			break;
		}
		else if (tacBoard[0][0] == tacBoard[1][1] && tacBoard[0][0] == tacBoard[2][2] && tacBoard[0][0] != ' ') {
			printf("%c wins!!!\n", tacBoard[0][0]);
			break;
		}
		else if (tacBoard[0][2] == tacBoard[1][1] && tacBoard[0][2] == tacBoard[2][0] && tacBoard[0][2] != ' ') {
			printf("%c wins!!!\n", tacBoard[0][2]);
			break;
		}
		//decide turn
		if (playTurn % 2 == 0) {
			currSym = 'X';
		}
		else {
			currSym = 'O';
		}
		//prompt
		printf("Where would you (%c) like to go (1-9): ", currSym); 
		scanf("%d", &usOpt);
		switch (usOpt) {
		case 1:
			if (tacBoard[0][1] == ' ') {
				tacBoard[0][0] = currSym;
				playTurn++;
			}
			else {
				printf("Invalid location\n");
			}
			break;
		case 2:
			if (tacBoard[0][1] == ' ') {
				tacBoard[0][1] = currSym;
				playTurn++;
			}
			else {
				printf("Invalid location\n");
			}
			break;
		case 3:
			if (tacBoard[0][2] == ' ') {
				tacBoard[0][2] = currSym;
				playTurn++;
			}
			else {
				printf("Invalid location\n");
			}
			break;
		case 4:
			if (tacBoard[1][0] == ' ') {
				tacBoard[1][0] = currSym;
				playTurn++;
			}
			else {
				printf("Invalid location\n");
			}
			break;
		case 5:
			if (tacBoard[1][1] == ' ') {
				tacBoard[1][1] = currSym;
				playTurn++;
			}
			else {
				printf("Invalid location\n");
			}
			break;
		case 6:
			if (tacBoard[1][2] == ' ') {
				tacBoard[1][2] = currSym;
				playTurn++;
			}
			else {
				printf("Invalid location\n");
			}
			break;
		case 7:
			if (tacBoard[2][0] == ' ') {
				tacBoard[2][0] = currSym;
				playTurn++;
			}
			else {
				printf("Invalid location\n");
			}
			break;
		case 8:
			if (tacBoard[2][1] == ' ') {
				tacBoard[2][1] = currSym;
				playTurn++;
			}
			else {
				printf("Invalid location\n");
			}
			break;
		case 9:
			if (tacBoard[2][2] == ' ') {
				tacBoard[2][2] = currSym;
				playTurn++;
			}
			else {
				printf("Invalid location\n");
			}
			break;
		default:
			printf("Invalid location\n");
			continue;

		}

	}
	return 0;
}