#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dealerHand = 0;
int dealerHiddenCard = 0;
int playerHand = 0;

int drawCard() {
	int card = (rand() % 13) + 1;
	if (card > 10) card = 10;
	return card;
}

void dealHands() {
	int card1 = drawCard();
	int card2 = drawCard();
	playerHand = card1 + card2;
	printf("You have a %d and a %d. Your total is %d.\n", card1, card2, playerHand);

	dealerHiddenCard = drawCard();
	dealerHand = drawCard();
	printf("Dealer has a %d and a hidden card.\n", dealerHand);
}

void initialize() {
	srand(time(0));
	srand(rand() * time(0));

	dealHands();
}

bool checkGameOver() {
	int dealerTotal = dealerHand + dealerHiddenCard;
	if (dealerTotal > 21) {
		printf("Dealer's hidden card was %d. Dealer has %d. Dealer busts. You win!\n", dealerHiddenCard, dealerTotal);
		return true;
	}
	if (playerHand > 21) {
		printf("Your total is %d. You bust. You lose!\n", playerHand);
		return true;
	}
	if (playerHand == 21) {
		printf("You have 21. You win!\n");
		return true;
	}
	if (dealerTotal == 21) {
		printf("Dealer's hidden card was %d. Dealer has 21. Dealer wins. You lose!\n", dealerHiddenCard);
		return true;
	}
	return false;
}

void takePlayerTurn() {
	printf("Choose an action:\n1) Draw\n2) Pass\nChoice: ");
	int playerAction = 0;
	scanf(" %d", &playerAction);
	if (playerAction == 1) {
		int card = drawCard();
		playerHand += card;
		printf("You drew a %d. Your new total is %d.\n", card, playerHand);
	} else {
		printf("You pass.\n");
	}
}

void takeDealerTurn() {
	if (dealerHand + dealerHiddenCard < 17 || rand() % 2) {
		int card = drawCard();
		dealerHand += card;
		printf("Dealer draws %d. Dealer's new total is %d plus hidden card.\n", card, dealerHand);
	} else {
		printf("Dealer passes. Your turn.\n");
	}
}

void playGame() {
	while (!checkGameOver()) {
		printf("\n");
		takePlayerTurn();
		if (checkGameOver()) break;
		takeDealerTurn();
	}
}

int main() {
	initialize();
	playGame();
	return 0;
}
