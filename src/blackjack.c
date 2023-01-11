#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	printf("Card 1 is %d\n", currCard);
	currCard = genCard();
	usrNum += currCard;
	printf("Card 2 is %d\n", currCard);
	printf("Total is %d\n", usrNum);
	currCard = genCard();
	cpuHide += currCard;
	currCard = genCard();
	cpuNum += currCard;
	printf("CPU has %d and hidden card\n", cpuNum);

	while (true) {
		//check for wins
		if (cpuNum + cpuHide == 21) {
			printf("CPU has %d so CPU wins. You lose!!!!\n", cpuNum + cpuHide);
			break;
		}
		else if (usrNum == 21) {
			printf("You WIN!!!!!!!!!\n");
			break;
		}
		else {
			printf("\n");
		}
		//action prompt
		printf("Choose action:\n1) Draw\n2) Pass\nChoice: ");
		scanf("%d", &usOpt);
		if (usOpt == 1) {
			currCard = genCard();
			usrNum += currCard;
			printf("You drew a %d and your new total is %d\n", currCard, usrNum);
			if (usrNum > 21) {
				printf("\nYou bust!!!!\n");
				break;
			}
		}
		else {
			printf("You pass\n");
		}
		//cpu action
		if (cpuNum + cpuHide < 17) {
			currCard = genCard();
			cpuNum += currCard;
			printf("CPU draws %d and CPU new total is %d plus hidden card\n", currCard, cpuNum);
			if (cpuNum + cpuHide > 21) {
				printf("CPU busts. You WIN!!!!\n");
				break;
			}
		}
		else {
			cpuPass = rand() % 2;
			if (cpuPass == 1) {
				printf("CPU passes. Your turn.\n");
			}
			else {
				currCard = genCard();
				cpuNum += currCard;
				printf("CPU draws %d and CPU new total is %d plus hidden card\n", currCard, cpuNum);
				if (cpuNum + cpuHide > 21) {
					printf("CPU busts. You WIN!!!!\n");
					break;
				}
			}
		}
	}
	return 0;
}