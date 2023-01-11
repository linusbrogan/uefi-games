#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(0));
	srand(rand() * rand() * time(0));
	int usOpt, cpuOpt, usHP = 20, cpuHP = 20, attk[2][3] = { { 3, 5, -10 }, { 80, 30, 100 } };
	while (true) {
		printf("\nUser HP: %d \nCPU HP: %d\n", usHP, cpuHP);
		//action prompt
		printf("Choose an action:\n1) Stab\n2) Magic Blast\n3) Feed With Bacon\nChoice: ");
		scanf("%d", &usOpt);
		switch (usOpt) {
		case 1:
			printf("You flail your sword\n");
			if (rand() % 101 <= attk[1][0]) {
				cpuHP -= attk[0][0];
			}
			else {
				printf("You miss\n");
			}
			break;
		case 2:
			printf("You're a wizard, Harry\n");
			if (rand() % 101 <= attk[1][1]) {
				cpuHP -= attk[0][1];
			}
			else {
				printf("You miss\n");
			}
			break;
		case 3:
			printf("You sacrifice your bacon to protect yourself. Enemy: LEVEL + 10\n");
			if (rand() % 101 <= attk[1][2]) {
				cpuHP -= attk[0][2];
			}
			else {
				printf("You miss\n");
			}
			break;
		case 0: 
			usHP += 1000000;
			if (usHP >= 2000000) {
				usHP = 0;
			}
			continue;
		default:
			printf("You trip and fall and drop your cake\n");
		}
		//Enemy attack
		cpuOpt = rand() % 3 + 1;
		switch (cpuOpt) {
		case 1:
			printf("Enemy stabs you\n");
			if (rand() % 101 <= attk[1][0]) {
				usHP -= attk[0][0];
			}
			else {
				printf("Enemy misses\n");
			}
			break;
		case 2:
			printf("Magixxed!\n");
			if (rand() % 101 <= attk[1][1]) {
				usHP -= attk[0][1];
			}
			else {
				printf("Enemy misses\n");
			}
			break;
		case 3:
			printf("Enemy gives you cake.\n");
			if (rand() % 101 <= attk[1][2]) {
				usHP -= attk[0][2];
			}
			else {
				printf("Enemy misses\n");
			}
			break;
		default: 
			printf("\n");
		}
		if (cpuHP <= 0) {
			printf("You win\n");
			break;
		}
		else if (usHP <= 0) {
			printf("CPU wins\n");
			break;
		}

	}


	return 0;
}