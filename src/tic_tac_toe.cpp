#include <iostream>
using namespace std;
//COULD MAYBE ADD AI??
int main() {
	//init tacBoard
	char tacBoard[3][3] = { { ' ', ' ', ' ' }, { ' ', ' ', ' ' }, { ' ', ' ', ' ' } }, currSym = ' ';
	int usOpt, playTurn = 0;
	while (true) {
		int spcCnt = 9;
		//board
		cout << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cout << tacBoard[i][j] << ' ';
			}
			cout << endl;
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
			cout << "Tie" << endl;
			break;
		}
		if (tacBoard[0][0] == tacBoard[0][1] && tacBoard[0][0] == tacBoard[0][2] && tacBoard[0][0] != ' ') {
			cout << tacBoard[0][0] << " wins!!!" << endl;
			break;
		}
		else if (tacBoard[1][0] == tacBoard[1][1] && tacBoard[1][0] == tacBoard[1][2] && tacBoard[1][0] != ' ') {
			cout << tacBoard[1][0] << " wins!!!" << endl;
			break;
		}
		else if (tacBoard[2][0] == tacBoard[2][1] && tacBoard[2][0] == tacBoard[2][2] && tacBoard[2][0] != ' ') {
			cout << tacBoard[2][0] << " wins!!!" << endl;
			break;
		}
		else if (tacBoard[0][0] == tacBoard[1][0] && tacBoard[0][0] == tacBoard[2][0] && tacBoard[0][0] != ' ') {
			cout << tacBoard[0][0] << " wins!!!" << endl;
			break;
		}
		else if (tacBoard[0][1] == tacBoard[1][1] && tacBoard[0][1] == tacBoard[2][1] && tacBoard[0][1] != ' ') {
			cout << tacBoard[0][1] << " wins!!!" << endl;
			break;
		}
		else if (tacBoard[0][2] == tacBoard[1][2] && tacBoard[0][2] == tacBoard[2][2] && tacBoard[0][2] != ' ') {
			cout << tacBoard[0][2] << " wins!!!" << endl;
			break;
		}
		else if (tacBoard[0][0] == tacBoard[1][1] && tacBoard[0][0] == tacBoard[2][2] && tacBoard[0][0] != ' ') {
			cout << tacBoard[0][0] << " wins!!!" << endl;
			break;
		}
		else if (tacBoard[0][2] == tacBoard[1][1] && tacBoard[0][2] == tacBoard[2][0] && tacBoard[0][2] != ' ') {
			cout << tacBoard[0][2] << " wins!!!" << endl;
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
		cout << "Where would you (" << currSym << ") like to go (1-9): "; 
		cin >> usOpt;
		switch (usOpt) {
		case 1:
			if (tacBoard[0][1] == ' ') {
				tacBoard[0][0] = currSym;
				playTurn++;
			}
			else {
				cout << "Invalid location" << endl;
			}
			break;
		case 2:
			if (tacBoard[0][1] == ' ') {
				tacBoard[0][1] = currSym;
				playTurn++;
			}
			else {
				cout << "Invalid location" << endl;
			}
			break;
		case 3:
			if (tacBoard[0][2] == ' ') {
				tacBoard[0][2] = currSym;
				playTurn++;
			}
			else {
				cout << "Invalid location" << endl;
			}
			break;
		case 4:
			if (tacBoard[1][0] == ' ') {
				tacBoard[1][0] = currSym;
				playTurn++;
			}
			else {
				cout << "Invalid location" << endl;
			}
			break;
		case 5:
			if (tacBoard[1][1] == ' ') {
				tacBoard[1][1] = currSym;
				playTurn++;
			}
			else {
				cout << "Invalid location" << endl;
			}
			break;
		case 6:
			if (tacBoard[1][2] == ' ') {
				tacBoard[1][2] = currSym;
				playTurn++;
			}
			else {
				cout << "Invalid location" << endl;
			}
			break;
		case 7:
			if (tacBoard[2][0] == ' ') {
				tacBoard[2][0] = currSym;
				playTurn++;
			}
			else {
				cout << "Invalid location" << endl;
			}
			break;
		case 8:
			if (tacBoard[2][1] == ' ') {
				tacBoard[2][1] = currSym;
				playTurn++;
			}
			else {
				cout << "Invalid location" << endl;
			}
			break;
		case 9:
			if (tacBoard[2][2] == ' ') {
				tacBoard[2][2] = currSym;
				playTurn++;
			}
			else {
				cout << "Invalid location" << endl;
			}
			break;
		default:
			cout << "Invalid location" << endl;
			continue;

		}

	}
	return 0;
}