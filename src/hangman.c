#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef char *string;

/*/
using std::cout;
using std::cin;
using std::endl;//*/
//functions
void gameStart();
void toScores(string oldTimes, string newTime);
string fromScores();
int main() {
	srand(time(0));
	srand(rand() * time(0));
	string scores;

	printf(" _\n| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __\n| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\\n| | | | (_| | | | | (_| | | | | | | (_| | | | |\n|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n                   |___/\n");
	printf(" _             ____  ____  ____   ____\n| |__  _   _  |  _ \\|  _ \\|  _ \\ / ___| _     _\n| '_ \\| | | | | | | | |_) | |_) | |   _| |_ _| |_\n| |_) | |_| | | |_| |  __/|  _ <| |__|_   _|_   _|\n|_.__/ \\__, | |____/|_|   |_| \\_\\\\____||_|   |_|\n       |___/\n");
	//Main game loop
	while (true) {
		//define vars
		int usrInt;
		//Main menu
		printf("\n\n1) New Game\n2) See Best Times\n3) Quit\nChoice: ");
		int status = scanf("%d", &usrInt);
		while (status != 1) {
			status = scanf("%d", &usrInt);
		}
		switch (usrInt) {
		case 1:
			//begin game
			gameStart();
			break;
		case 2:
			//MAGIC
			printf("%s", fromScores());
			break;
		case 3:
			return 0;
		case 0:
			toScores("Name\t\tTime\t\tMissed Letters\n----\t\t----\t\t--------------", "");
		default:
			continue;
		}
	}

	return 0;
}
//function code
void gameStart() {
	char usrChar, posFinder; //for inpute
	string wordList[27] = { "random", "a", "no", "win", "foot", "bacon", "speedy", "unicorn", "blizzard", "computers", "embezzling", "quizzically", "hippopotamus", "quadrilateral", "absentmindedly", "extrajudicially", "nonbiodegradable", "industrialization", "characteristically", "multidimensionality", "counterrevolutionary", "unconstitutionalities", "nonrepresentationalism", "hydrochlorofluorocarbon", "antidisestablishmentarianism", "supercalifragilisticexpialidocious", "pneumonoultramicroscopicsilicovolcanoconiosis" }; //list of wordds
	//                        0        1     2     3       4      5         6         7         8                8         10          11               12               13               14                 15                     16             17                     18                     19                   20                         21                      22                       23                             24                                    25                                            26
	wordList[0] = wordList[rand() % 26 + 1];//random word
	//string person = "  0\n /|\\\n  |\n_/ \\_", hanger = "   _______\n   |     |\n   |\n   |\n   |\n   |\n___|______", dead = "   _______\n   |     |\n   |     0\n   |    /|\\\n   |     |\n   |   _/ \\_\n___|_______";//art
	bool win = false, lose = false;
	string bodyChars[10] = { " ", "0", "/", "|", "\\", "|", "_", " / ", "\\", "_" };//art
	char guessed[] = "                          ";
	int diff, fails = 0;
	printf("Choose difficulty (1-26, 0 for random): ");
	int status = 0;
	do {
		status = scanf("%d", &diff);
	} while (status != 1);
	if (diff > 26 || diff < 0) {
		diff = 0;
	} 

	char word[strlen(wordList[diff]) + 1];
	strcpy(word, wordList[diff]);
	char bakWord[strlen(wordList[diff]) + 1];
	strcpy(bakWord, wordList[diff]);
	int wordLength = strlen(word);
	char dispWord[wordLength + 1];
	char winWord[wordLength + 1];
	for (int i = 0; i < wordLength; i++) {
		dispWord[i] = '_';
		winWord[i] = ' ';
	}
	dispWord[wordLength] = '\0';
	winWord[wordLength] = '\0';
	int start = time(0), finish = 0;
	//int lettPos = 0;
	//Game loop
	while (true) {
		int lettPos = 0;
		//print hanger
		printf("\n    _____\n   |     |\n   |     ");
		switch (fails) {
		case 0:
			printf("\n   |\n   |\n   |\n___|________\n");
			break;
		case 1:
			printf("0\n   |  \n   |\n   |\n___|________\n");
			break;
		case 2:
			printf("0\n   |     |\n   |\n   |\n___|________\n");
			break;
		case 3:
			printf("0\n   |    /|\n   |\n   |\n___|________\n");
			break;
		case 4:
			printf("0\n   |    /|\\\n   |\n   |\n___|________\n");
			break;
		case 5:
			printf("0\n   |    /|\\\n   |     |\n   |\n___|________\n");
			break;
		case 6:
			printf("0\n   |    /|\\\n   |     |\n   |    /\n___|________\n");
			break;
		case 7:
			printf("0\n   |    /|\\\n   |     |\n   |    / \\\n___|________\n");
			break;
		case 8:
			printf("0\n   |    /|\\\n   |     |\n   |   _/ \\\n___|________\n");
			break;
		case 9:
			printf("0\n   |    /|\\\n   |     |\n   |   _/ \\_\n___|________\n");
			break;
		default:
			while (true) {
				printf("\n");
			}
		}
		//check wins
		if (strcmp(word, winWord) == 0) {
			printf("You win\nThe word was %s\n", bakWord);
			finish = time(0);
			printf("Time: %d\n", finish - start);
			char timeData[200];
			printf("Enter your name to save your score: ");
			scanf(" %100s", timeData);
			int length = strlen(timeData);
			sprintf(timeData + length, "\t\t%d\t\t%d", finish - start, fails);
			toScores(fromScores(), timeData);
			break;
		}
		else if (fails >= 9) {
			printf("You lose :(\nThe word was %s\n", bakWord);
			finish = time(0);
			printf("Time: %d\n", finish - start);
			char timeData[200];
			printf("Enter your name to save your score: ");
			scanf(" %100s", timeData);
			int length = strlen(timeData);
			sprintf(timeData + length, "\t\t%d X\t\t%d", finish - start, fails);
			toScores(fromScores(), timeData);

			break;
		}
		//print word
		printf("\n%s\n%ld letter word\n", dispWord, strlen(word));
		//guessed letters:
		printf("Guessed letters:\n");
		for (int i = 0; i < 26; i++) {
			printf("%c ", guessed[i]);
			if (i == 5 || i == 11 || i == 17 || i == 23 || i == 25) {
				printf("\n");
			}
		}
		//get new lettter
		printf("New letter guess: ");
		int status = scanf(" %c", &usrChar);
		while (status != 1) {}
		while (usrChar < 'a' || usrChar > 'z') {
			do {
				status = scanf(" %c", &usrChar);
			} while (status != 1);
		}
		posFinder = usrChar;
		//check letter
		while (posFinder != 'a') {
				posFinder--;
				lettPos++;
		}
		if (guessed[lettPos] == usrChar) {
			printf("You already guessed that letter!\n");
			continue;
		}
		else {
			guessed[lettPos] = usrChar;
		}
		if (strchr(word, usrChar) == NULL) {
			printf("Letter not found :(\n");
			fails++;
		}
		else {
			printf("Good guess!\n");
			while (strchr(word, usrChar) != NULL) {
				dispWord[strchr(word, usrChar) - word] = usrChar;
				//word[strchr(word, usrChar) - word] = ' ';
				char *wordChar = strchr(word, usrChar);
				if (wordChar != NULL) *wordChar = ' ';
			}
		}
	}
}

void toScores(string oldTimes, string newTime) {
	FILE *outData = fopen("bestTimes.dat", "w+");
	if (outData != NULL) {
		fprintf(outData, "%s\n%s\n", oldTimes, newTime);
		fclose(outData);
	}


}
string fromScores() {
	string tmp = NULL;
	string inFo = NULL;
	FILE *inData = fopen("bestTimes.dat", "r+");
	if (inData != NULL) {
		fseek(inData, 0, SEEK_END);
		long length = ftell(inData);
		fseek(inData, 0, SEEK_SET);
		inFo = malloc(length * sizeof(char));
		if (inFo == NULL) return NULL;
		fread(inFo, sizeof(char), length, inData);
		fclose(inData);
	}
	return inFo;

}

