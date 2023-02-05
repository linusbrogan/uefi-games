#include <efi.h>
#include <efilib.h>
#include <stdbool.h>
#include "efistub.h"
#include "io.h"
#include "rand.h"
#include "time.h"
#include "wchar.h"

const CHAR16 scoreFileName[] = L"bestTimes.dat";
const CHAR16 hangman[][100] = {
	L"\n   |\n   |\n   |\n___|________",
	L"0\n   |  \n   |\n   |\n___|________",
	L"0\n   |     |\n   |\n   |\n___|________",
	L"0\n   |    /|\n   |\n   |\n___|________",
	L"0\n   |    /|\\\n   |\n   |\n___|________",
	L"0\n   |    /|\\\n   |     |\n   |\n___|________",
	L"0\n   |    /|\\\n   |     |\n   |    /\n___|________",
	L"0\n   |    /|\\\n   |     |\n   |    / \\\n___|________",
	L"0\n   |    /|\\\n   |     |\n   |   _/ \\\n___|________",
	L"0\n   |    /|\\\n   |     |\n   |   _/ \\_\n___|________"
};
const CHAR16 wordList[][100] = {
	L"a",
	L"no",
	L"win",
	L"foot",
	L"bacon",
	L"speedy",
	L"unicorn",
	L"blizzard",
	L"computers",
	L"embezzling",
	L"quizzically",
	L"hippopotamus",
	L"quadrilateral",
	L"absentmindedly",
	L"extrajudicially",
	L"nonbiodegradable",
	L"industrialization",
	L"characteristically",
	L"multidimensionality",
	L"counterrevolutionary",
	L"unconstitutionalities",
	L"nonrepresentationalism",
	L"hydrochlorofluorocarbon",
	L"antidisestablishmentarianism",
	L"supercalifragilisticexpialidocious",
	L"pneumonoultramicroscopicsilicovolcanoconiosis"
};

// Game state
const wchar_t *word = NULL;
int wordLength = 0;
wchar_t displayWord[100];
int missedLetters = 0;
time_t startTime = 0;
wchar_t guessedLetters[26];

void printBanner() {
	Print(L" _\n| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __\n| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\\n| | | | (_| | | | | (_| | | | | | | (_| | | | |\n|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n                   |___/\n");
	Print(L" _             ____  ____  ____   ____\n| |__  _   _  |  _ \\|  _ \\|  _ \\ / ___| _     _\n| '_ \\| | | | | | | | |_) | |_) | |   _| |_ _| |_\n| |_) | |_| | | |_| |  __/|  _ <| |__|_   _|_   _|\n|_.__/ \\__, | |____/|_|   |_| \\_\\\\____||_|   |_|\n       |___/\n");
}

void initialize() {
	srand(time(0));
	srand(rand() * time(0));
	printBanner();
}

void saveScore(const CHAR16 *newTime) {
	EFI_FILE_HANDLE scoreFile = openFile(scoreFileName, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE);
	if (scoreFile == NULL) return;
	uefi_call_wrapper(scoreFile->SetPosition, 2, scoreFile, 0xffffffffffffffffL);
	UINT8 *buffer = (void *) newTime;
	UINTN size = 2 * lwcslen(newTime);
	uefi_call_wrapper(scoreFile->Write, 3, scoreFile, &size, buffer);
	uefi_call_wrapper(scoreFile->Close, 1, scoreFile);
}

void resetScores() {
	EFI_FILE_HANDLE scoreFile = openFile(scoreFileName, EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE);
	if (scoreFile == NULL) return;
	uefi_call_wrapper(scoreFile->Delete, 1, scoreFile);

	CHAR16 scoreHeader[] = L"Name\t\tTime\t\tMissed Letters\n----\t\t----\t\t--------------\n";
	saveScore(scoreHeader);
}

int promptLevel() {
	Print(L"Choose a level (1-26, 0 for random): ");
	int level = scanNumber();
	if (level <= 0 || level > 26) {
		return rand() % 26;
	}
	return level - 1;
}

void setupGame() {
	int n = promptLevel();
	word = wordList[n];
	wordLength = lwcslen(word);
	for (int i = 0; i < wordLength; i++)
		displayWord[i] = '_';
	displayWord[wordLength] = '\0';
	for (int i = 0; i < 26; i++)
		guessedLetters[i] = ' ';
	missedLetters = 0;
	startTime = time(0);
}

bool checkGameOver() {
	bool isGameOver = false;
	bool lost = false;
	if (lwcscmp(displayWord, word) == 0) {
		Print(L"You win!\n");
		isGameOver = true;
	} else if (missedLetters >= 9) {
		Print(L"You lose!\n");
		isGameOver = true;
		lost = true;
	}

	if (isGameOver) {
		Print(L"The word was %s.\n", word);
		long playTime = time(0) - startTime;
		Print(L"Time: %ld\n", playTime);
		CHAR16 timeData[200];
		Print(L"Enter your name to save your score: ");
		scanString(timeData);
		int length = lwcslen(timeData);
		UnicodeSPrint(timeData + length, 200 - length, L"\t\t%ld%s\t\t%d\n", playTime, lost ? L" X" : L"", missedLetters);
		saveScore(timeData);
	}

	return isGameOver;
}

void printGameState() {
	Print(L"\n    _____\n   |     |\n   |     %s\n", hangman[missedLetters]);
	Print(L"\n%s (%d letter word)\n", displayWord, wordLength);
	Print(L"Guessed letters:\n");
	for (int i = 0; i < 26; i++) {
		Print(L"%c ", guessedLetters[i]);
		if (i % 6 == 5 || i == 25) {
			Print(L"\n");
		}
	}
}

char promptLetter() {
	Print(L"Guess a letter: ");
	char letter = '\0';
	while (letter < 'a' || letter > 'z') {
		letter = scanChar();
		if (letter >= 'A' && letter <= 'Z') letter -= 'a' - 'A';
	}
	Print(L"\n");

	if (guessedLetters[letter - 'a'] == letter) {
		Print(L"You already guessed that letter!\n");
		return '\0';
	}
	guessedLetters[letter - 'a'] = letter;
	return letter;
}

void checkLetter(char letter) {
	wchar_t *letterPosition = lwcschr(word, letter);
	if (letterPosition == NULL) {
		Print(L"The word does not contain %c.\n", letter);
		missedLetters++;
	} else {
		Print(L"Good guess!\n");
		while (letterPosition != NULL) {
			displayWord[letterPosition - word] = letter;
			letterPosition = lwcschr(letterPosition + 1, letter);
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
	EFI_FILE_HANDLE scoreFile = openFile(scoreFileName, EFI_FILE_MODE_READ);
	if (scoreFile == NULL) return;
	UINTN size = FileSize(scoreFile);
	UINT8 *buffer = AllocatePool(size + 2);
	uefi_call_wrapper(scoreFile->Read, 3, scoreFile, &size, buffer);
	buffer[size] = '\0';
	buffer[size + 1] = '\0';
	Print(L"%s", (CHAR16 *) buffer);
	FreePool(buffer);
	uefi_call_wrapper(scoreFile->Close, 1, scoreFile);
}

const int menuLength = 4;

bool promptMenu() {
	Print(L"\nChoose an action:\n1) New game\n2) See best times\n3) Reset scores\n0) Quit\nChoice: ");
	int action;
	do {
		action = scanDigit();
	} while (action < 0 || action >= menuLength);
	if (action == 1) playGame();
	else if (action == 2) printScores();
	else if (action == 3) resetScores();
	else return false;

	return true;
}

int main() {
	initialize();
	while (promptMenu());
	return 0;
}
