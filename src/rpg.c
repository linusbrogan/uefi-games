#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum attack {
	ATTACK_CHEAT,
	ATTACK_SWORD,
	ATTACK_MAGIC,
	ATTACK_BACON,
	ATTACK_COUNT
};

const int attackDamage[ATTACK_COUNT] = {0, 3, 5, -10};
const int attackProbability[ATTACK_COUNT] = {100, 80, 30, 100};
const int maxProbability = 101;
const char *enemyAttackMessage[ATTACK_COUNT] = {
	"Enemy cheats! How is that possible?",
	"Enemy stabs you.",
	"Magixxed!",
	"Enemy gives you cake."
};
const char *playerAttackMessage[ATTACK_COUNT] = {
	"You cheat! Don't do it again!",
	"You flail your sword.",
	"You're a wizard, Harry.",
	"You sacrifice your bacon to protect yourself."
};

int enemyHealth = 20;
int playerHealth = 20;

void initialize() {
	srand(time(0));
	srand(rand() * time(0));
}

bool checkGameOver() {
	if (enemyHealth <= 0) {
		printf("Enemy faints. You win!\n");
		return true;
	}

	if (playerHealth <= 0) {
		printf("You faint. Enemy wins.\n");
		return true;
	}
	return false;
}

void takePlayerTurn() {
	printf("Choose an action:\n1) Stab\n2) Magic blast\n3) Feed with bacon\nChoice: ");
	int playerAction = 0;
	scanf(" %d", &playerAction);
	if (playerAction == ATTACK_CHEAT) {
		playerHealth += 1000000;
		if (playerHealth >= 2000000) {
			playerHealth = 0;
		}
	}
	printf("\n");
	if (playerAction < ATTACK_COUNT) {
		printf("%s\n", playerAttackMessage[playerAction]);
		if (rand() % maxProbability <= attackProbability[playerAction]) enemyHealth -= attackDamage[playerAction];
		else printf("You miss.\n");
	} else printf("You trip and fall and drop your cake.\n");
}

void takeEnemyTurn() {
	enum attack enemyAction = rand() % (ATTACK_COUNT - 1) + 1;
	printf("%s\n", enemyAttackMessage[enemyAction]);
	if (rand() % maxProbability <= attackProbability[enemyAction]) playerHealth -= attackDamage[enemyAction];
	else printf("Enemy misses.\n");
}

void playGame() {
	while (!checkGameOver()) {
		printf("Player health: %d\nEnemy health: %d\n", playerHealth, enemyHealth);
		takePlayerTurn();
		takeEnemyTurn();
		printf("\n");
	}
}

int main() {
	initialize();
	playGame();
	return 0;
}
