#include <efi.h>
#include <efilib.h>
#include <stdbool.h>
#include "efistub.h"
#include "io.h"
#include "rand.h"
#include "time.h"

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
	Print(L"You have a %d and a %d. Your total is %d.\n", card1, card2, playerHand);

	dealerHiddenCard = drawCard();
	dealerHand = drawCard();
	Print(L"Dealer has a %d and a hidden card.\n", dealerHand);
}

void initialize() {
	srand(time(0));
	srand(rand() * time(0));

	dealHands();
}

bool checkGameOver() {
	int dealerTotal = dealerHand + dealerHiddenCard;
	if (dealerTotal > 21) {
		Print(L"Dealer's hidden card was %d. Dealer has %d. Dealer busts. You win!\n", dealerHiddenCard, dealerTotal);
		return true;
	}
	if (playerHand > 21) {
		Print(L"Your total is %d. You bust. You lose!\n", playerHand);
		return true;
	}
	if (playerHand == 21) {
		Print(L"You have 21. You win!\n");
		return true;
	}
	if (dealerTotal == 21) {
		Print(L"Dealer's hidden card was %d. Dealer has 21. Dealer wins. You lose!\n", dealerHiddenCard);
		return true;
	}
	return false;
}

void takePlayerTurn() {
	Print(L"Choose an action:\n1) Draw\n2) Pass\nChoice: ");
	int playerAction = scanDigit();
	if (playerAction == 1) {
		int card = drawCard();
		playerHand += card;
		Print(L"You drew a %d. Your new total is %d.\n", card, playerHand);
	} else {
		Print(L"You pass.\n");
	}
}

void takeDealerTurn() {
	if (dealerHand + dealerHiddenCard < 17 || rand() % 2) {
		int card = drawCard();
		dealerHand += card;
		Print(L"Dealer draws %d. Dealer's new total is %d plus hidden card.\n", card, dealerHand);
	} else {
		Print(L"Dealer passes. Your turn.\n");
	}
}

void playGame() {
	while (!checkGameOver()) {
		Print(L"\n");
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
