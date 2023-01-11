#include <iostream>
#include <ctime>
//#include <time.h>
using namespace std;
//function to generate cards
int genCard() {
	int nuMR = (rand() % 100) + 1;
	while (nuMR > 13) {
		nuMR = (rand() % 100) + 1;
	}
	if (nuMR > 10) {
		nuMR = 10;
	}
	return nuMR;
}
int main() {
	//seed random and initialize vars
	srand(time(0));
	srand(rand() * time(0));
	int cpuPass = 0, usOpt = 0, usrNum = 0, cpuNum = 0, cpuHide = 0, currCard = 0;
	//generate hands
	currCard = genCard();
	usrNum += currCard;
	cout << "Card 1 is " << currCard << endl;
	currCard = genCard();
	usrNum += currCard;
	cout << "Card 2 is " << currCard << endl;
	cout << "Total is " << usrNum << endl;
	currCard = genCard();
	cpuHide += currCard;
	currCard = genCard();
	cpuNum += currCard;
	cout << "CPU has " << cpuNum << " and hidden card" << endl;

	while (true) {
		//check for wins
		if (cpuNum + cpuHide == 21) {
			cout << "CPU has " << cpuNum + cpuHide << " so CPU wins. You lose!!!!" << endl;
			break;
		}
		else if (usrNum == 21) {
			cout << "You WIN!!!!!!!!!" << endl;
			break;
		}
		else {
			cout << endl;
		}
		//action prompt
		cout << "Choose action:\n1) Draw\n2) Pass\nChoice: ";
		cin >> usOpt;
		if (usOpt == 1) {
			currCard = genCard();
			usrNum += currCard;
			cout << "You drew a " << currCard << " and your new total is " << usrNum << endl;
			if (usrNum > 21) {
				cout << endl << "You bust!!!!" << endl;
				break;
			}
		}
		else {
			cout << "You pass" << endl;
		}
		//cpu action
		if (cpuNum + cpuHide < 17) {
			currCard = genCard();
			cpuNum += currCard;
			cout << "CPU draws " << currCard << " and CPU new total is " << cpuNum << " plus hidden card" << endl;
			if (cpuNum + cpuHide > 21) {
				cout << "CPU busts. You WIN!!!!" << endl;
				break;
			}
		}
		else {
			cpuPass = rand() % 2;
			if (cpuPass == 1) {
				cout << "CPU passes. Your turn." << endl;
			}
			else {
				currCard = genCard();
				cpuNum += currCard;
				cout << "CPU draws " << currCard << " and CPU new total is " << cpuNum << " plus hidden card" << endl;
				if (cpuNum + cpuHide > 21) {
					cout << "CPU busts. You WIN!!!!" << endl;
					break;
				}
			}
		}
	}
	return 0;
}