#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
	srand(time(0));
	srand(rand() * rand() * time(0));
	int usOpt, cpuOpt, usHP = 20, cpuHP = 20, attk[2][3] = { { 3, 5, -10 }, { 80, 30, 100 } };
	while (true) {
		cout << "\nUser HP: " << usHP << " \nCPU HP: " << cpuHP << endl;
		//action prompt
		cout << "Choose an action:\n1) Stab\n2) Magic Blast\n3) Feed With Bacon\nChoice: ";
		cin >> usOpt;
		switch (usOpt) {
		case 1:
			cout << "You flail your sword" << endl;
			if (rand() % 101 <= attk[1][0]) {
				cpuHP -= attk[0][0];
			}
			else {
				cout << "You miss" << endl;
			}
			break;
		case 2:
			cout << "You're a wizard, Harry" << endl;
			if (rand() % 101 <= attk[1][1]) {
				cpuHP -= attk[0][1];
			}
			else {
				cout << "You miss" << endl;
			}
			break;
		case 3:
			cout << "You sacrifice your bacon to protect yourself. Enemy: LEVEL + 10" << endl;
			if (rand() % 101 <= attk[1][2]) {
				cpuHP -= attk[0][2];
			}
			else {
				cout << "You miss" << endl;
			}
			break;
		case 0: 
			usHP += 1000000;
			if (usHP >= 2000000) {
				usHP = 0;
			}
			continue;
		default:
			cout << "You trip and fall and drop your cake" << endl;
		}
		//Enemy attack
		cpuOpt = rand() % 3 + 1;
		switch (cpuOpt) {
		case 1:
			cout << "Enemy stabs you" << endl;
			if (rand() % 101 <= attk[1][0]) {
				usHP -= attk[0][0];
			}
			else {
				cout << "Enemy misses" << endl;
			}
			break;
		case 2:
			cout << "Magixxed!" << endl;
			if (rand() % 101 <= attk[1][1]) {
				usHP -= attk[0][1];
			}
			else {
				cout << "Enemy misses" << endl;
			}
			break;
		case 3:
			cout << "Enemy gives you cake." << endl;
			if (rand() % 101 <= attk[1][2]) {
				usHP -= attk[0][2];
			}
			else {
				cout << "Enemy misses" << endl;
			}
			break;
		default: 
			cout << endl;
		}
		if (cpuHP <= 0) {
			cout << "You win" << endl;
			break;
		}
		else if (usHP <= 0) {
			cout << "CPU wins" << endl;
			break;
		}

	}


	return 0;
}