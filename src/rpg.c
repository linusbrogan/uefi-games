#include <stdbool.h>
#include "efistub.h"
#include "io.h"
#include "rand.h"
#include "time.h"

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
const CHAR16 *enemyAttackMessage[ATTACK_COUNT] = {
	L"Enemy cheats! How is that possible?",
	L"Enemy stabs you.",
	L"Magixxed!",
	L"Enemy gives you cake."
};
const CHAR16 *playerAttackMessage[ATTACK_COUNT] = {
	L"You cheat! Don't do it again!",
	L"You flail your sword.",
	L"You're a wizard, Harry.",
	L"You sacrifice your bacon to protect yourself."
};

int enemyHealth = 20;
int playerHealth = 20;

void initialize() {
	srand(time(0));
	srand(rand() * time(0));
}

bool checkGameOver() {
	if (enemyHealth <= 0) {
		Print(L"Enemy faints. You win!\n");
		return true;
	}

	if (playerHealth <= 0) {
		Print(L"You faint. Enemy wins.\n");
		return true;
	}
	return false;
}

void takePlayerTurn() {
	Print(L"Choose an action:\n1) Stab\n2) Magic blast\n3) Feed with bacon\nChoice: ");
	int playerAction = readDigit();
	if (playerAction == ATTACK_CHEAT) {
		playerHealth += 1000000;
		if (playerHealth >= 2000000) {
			playerHealth = 0;
		}
	}
	Print(L"\n");
	if (playerAction < ATTACK_COUNT) {
		Print(L"%s\n", playerAttackMessage[playerAction]);
		if (rand() % maxProbability <= attackProbability[playerAction]) enemyHealth -= attackDamage[playerAction];
		else Print(L"You miss.\n");
	} else Print(L"You trip and fall and drop your cake.\n");
}

void takeEnemyTurn() {
	enum attack enemyAction = rand() % (ATTACK_COUNT - 1) + 1;
	Print(L"%s\n", enemyAttackMessage[enemyAction]);
	if (rand() % maxProbability <= attackProbability[enemyAction]) playerHealth -= attackDamage[enemyAction];
	else Print(L"Enemy misses.\n");
}

void playGame() {
	while (!checkGameOver()) {
		Print(L"Player health: %d\nEnemy health: %d\n", playerHealth, enemyHealth);
		takePlayerTurn();
		takeEnemyTurn();
		Print(L"\n");
	}
}

int main() {
	initialize();
	playGame();
	return 0;
}
