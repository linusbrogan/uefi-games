#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *scoreFileName = "bestTimes.dat";
const char *hangman[] = {
	"\n   |\n   |\n   |\n___|________",
	"0\n   |  \n   |\n   |\n___|________",
	"0\n   |     |\n   |\n   |\n___|________",
	"0\n   |    /|\n   |\n   |\n___|________",
	"0\n   |    /|\\\n   |\n   |\n___|________",
	"0\n   |    /|\\\n   |     |\n   |\n___|________",
	"0\n   |    /|\\\n   |     |\n   |    /\n___|________",
	"0\n   |    /|\\\n   |     |\n   |    / \\\n___|________",
	"0\n   |    /|\\\n   |     |\n   |   _/ \\\n___|________",
	"0\n   |    /|\\\n   |     |\n   |   _/ \\_\n___|________"
};
const char *wordList[] = {
	"a",
	"no",
	"win",
	"foot",
	"bacon",
	"speedy",
	"unicorn",
	"blizzard",
	"computers",
	"embezzling",
	"quizzically",
	"hippopotamus",
	"quadrilateral",
	"absentmindedly",
	"extrajudicially",
	"nonbiodegradable",
	"industrialization",
	"characteristically",
	"multidimensionality",
	"counterrevolutionary",
	"unconstitutionalities",
	"nonrepresentationalism",
	"hydrochlorofluorocarbon",
	"antidisestablishmentarianism",
	"supercalifragilisticexpialidocious",
	"pneumonoultramicroscopicsilicovolcanoconiosis"
};

// Game state
const char *word = NULL;
int wordLength = 0;
char displayWord[100];
int missedLetters = 0;
time_t startTime = 0;
char guessedLetters[26];

void printBanner() {
	printf(" _\n| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __\n| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\\n| | | | (_| | | | | (_| | | | | | | (_| | | | |\n|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n                   |___/\n");
	printf(" _             ____  ____  ____   ____\n| |__  _   _  |  _ \\|  _ \\|  _ \\ / ___| _     _\n| '_ \\| | | | | | | | |_) | |_) | |   _| |_ _| |_\n| |_) | |_| | | |_| |  __/|  _ <| |__|_   _|_   _|\n|_.__/ \\__, | |____/|_|   |_| \\_\\\\____||_|   |_|\n       |___/\n");
}

void initialize() {
	srand(time(0));
	srand(rand() * time(0));
	printBanner();
}

void resetScores() {
	FILE *scoreFile = fopen(scoreFileName, "w+");
	if (scoreFile == NULL) return;
	fprintf(scoreFile, "Name\t\tTime\t\tMissed Letters\n----\t\t----\t\t--------------\n");
	fclose(scoreFile);
}

int promptLevel() {
	printf("Choose a level (1-26, 0 for random): ");
	int level = 0;
	int status = 0;
	while (status != 1) {
		status = scanf(" %d", &level);
	}
	if (level <= 0 || level > 26) {
		return rand() % 26;
	} 
	return level - 1;
}

void setupGame() {
	word = wordList[promptLevel()];
	wordLength = strlen(word);
	for (int i = 0; i < wordLength; i++)
		displayWord[i] = '_';
	displayWord[wordLength] = '\0';
	for (int i = 0; i < 26; i++)
		guessedLetters[i] = ' ';
	missedLetters = 0;
	startTime = time(0);
}

void saveScore(const char *newTime) {
	FILE *scoreFile = fopen(scoreFileName, "a");
	if (scoreFile == NULL) return;
	fprintf(scoreFile, "%s\n", newTime);
	fclose(scoreFile);
}

bool checkGameOver() {
	bool isGameOver = false;
	bool lost = false;
	if (strcmp(displayWord, word) == 0) {
		printf("You win!\n");
		isGameOver = true;
	} else if (missedLetters >= 9) {
		printf("You lose!\n");
		isGameOver = true;
		lost = true;
	}

	if (isGameOver) {
		printf("The word was %s.\n", word);
		long playTime = time(0) - startTime;
		printf("Time: %ld\n", playTime);
		char timeData[200];
		printf("Enter your name to save your score: ");
		scanf(" %100s", timeData);
		int length = strlen(timeData);
		sprintf(timeData + length, "\t\t%ld%s\t\t%d", playTime, lost ? " X" : "", missedLetters);
		saveScore(timeData);
	}

	return isGameOver;
}

void printGameState() {
	printf("\n    _____\n   |     |\n   |     %s\n", hangman[missedLetters]);
	printf("\n%s (%d letter word)\n", displayWord, wordLength);
	printf("Guessed letters:\n");
	for (int i = 0; i < 26; i++) {
		printf("%c ", guessedLetters[i]);
		if (i % 6 == 5 || i == 25) {
			printf("\n");
		}
	}
}

char promptLetter() {
	printf("Guess a letter: ");
	char letter = '\0';
	int status = 0;
	while (status != 1 || letter < 'a' || letter > 'z') {
		status = scanf(" %c", &letter);
		if (letter >= 'A' && letter <= 'Z') letter -= 'a' - 'A';
	}

	if (guessedLetters[letter - 'a'] == letter) {
		printf("You already guessed that letter!\n");
		return '\0';
	}
	guessedLetters[letter - 'a'] = letter;
	return letter;
}

void checkLetter(char letter) {
	char *letterPosition = strchr(word, letter);
	if (letterPosition == NULL) {
		printf("The word does not contain %c.\n", letter);
		missedLetters++;
	} else {
		printf("Good guess!\n");
		while (letterPosition != NULL) {
			displayWord[letterPosition - word] = letter;
			letterPosition = strchr(letterPosition + 1, letter);
		}
	}
}

void playGame() {
	setupGame();
	while (!checkGameOver()) {
		printGameState();
		char letter = promptLetter();
		if (letter != '\0') checkLetter(letter);
	}
}

void printScores() {
	FILE *scoreFile = fopen(scoreFileName, "r");
	if (scoreFile == NULL) return;
	while (true) {
		char *buffer = NULL;
		size_t size = 0;
		int status = getline(&buffer, &size, scoreFile);
		if (status == -1) {
			free(buffer);
			break;
		}
		printf("%s", buffer);
		free(buffer);
	}
	fclose(scoreFile);
}

void quit() {
	exit(0);
}

const int menuLength = 4;
void (*menu[])() = {
	resetScores,
	playGame,
	printScores,
	quit
};

void promptMenu() {
	printf("\nChoose an action:\n1) New game\n2) See best times\n3) Quit\nChoice: ");
	int action = 0;
	int status = 0;
	while (status != 1 || action < 0 || action >= menuLength) {
		status = scanf(" %d", &action);
	}
	menu[action]();
}

int main() {
	initialize();
	while (true) {
		promptMenu();
	}
	return 0;
}
