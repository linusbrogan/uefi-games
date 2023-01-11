/*******************************************************************************
* Created by Linus B. from DPRC++ (The Democratic People's Republic of C++).   *
*******************************************************************************/
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;
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

	cout << " _\n| |__   __ _ _ __   __ _ _ __ ___   __ _ _ __\n| '_ \\ / _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\\n| | | | (_| | | | | (_| | | | | | | (_| | | | |\n|_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n                   |___/" << endl;
	cout << " _             ____  ____  ____   ____\n| |__  _   _  |  _ \\|  _ \\|  _ \\ / ___| _     _\n| '_ \\| | | | | | | | |_) | |_) | |   _| |_ _| |_\n| |_) | |_| | | |_| |  __/|  _ <| |__|_   _|_   _|\n|_.__/ \\__, | |____/|_|   |_| \\_\\\\____||_|   |_|\n       |___/" << endl;
	//Main game loop
	while (true) {
		//define vars
		int usrInt;
		//Main menu
		cout << "\n\n1) New Game\n2) See Best Times\n3) Quit\nChoice: ";
		cin >> usrInt;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
			cin >> usrInt;
		}
		switch (usrInt) {
		case 1:
			//begin game
			gameStart();
			break;
		case 2:
			//MAGIC
			cout << fromScores();
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
	string guessed = "                          ";
	int diff, fails = 0;
	cout << "Choose difficulty (1-26, 0 for random): ";
	do {
		cin.clear();
		cin.ignore();
		cin >> diff;
	} while (cin.fail());
	if (diff > 26 || diff < 0) {
		diff = 0;
	} 
	string word, dispWord, bakWord, winWord;
	word = wordList[diff];
	bakWord = word;
	for (int i = 0; i < word.length(); i++) {
		dispWord += '_';
		winWord += ' ';
	}
	int start = time(0), finish = 0;
	//int lettPos = 0;
	//Game loop
	while (true) {
		int lettPos = 0;
		//print hanger
		cout << endl << "    _____\n   |     |\n   |     ";
		switch (fails) {
		case 0:
			cout << "\n   |\n   |\n   |\n___|________" << endl;
			break;
		case 1:
			cout << "0\n   |  \n   |\n   |\n___|________" << endl;
			break;
		case 2:
			cout << "0\n   |     |\n   |\n   |\n___|________" << endl;
			break;
		case 3:
			cout << "0\n   |    /|\n   |\n   |\n___|________" << endl;
			break;
		case 4:
			cout << "0\n   |    /|\\\n   |\n   |\n___|________" << endl;
			break;
		case 5:
			cout << "0\n   |    /|\\\n   |     |\n   |\n___|________" << endl;
			break;
		case 6:
			cout << "0\n   |    /|\\\n   |     |\n   |    /\n___|________" << endl;
			break;
		case 7:
			cout << "0\n   |    /|\\\n   |     |\n   |    / \\\n___|________" << endl;
			break;
		case 8:
			cout << "0\n   |    /|\\\n   |     |\n   |   _/ \\\n___|________" << endl;
			break;
		case 9:
			cout << "0\n   |    /|\\\n   |     |\n   |   _/ \\_\n___|________" << endl;
			break;
		default:
			while (true) {
				cout << endl;
			}
		}
		//check wins
		if (word == winWord) {
			cout << "You win" << endl << "The word was " << bakWord << endl;
			finish = time(0);
			cout << "Time: " << finish - start << endl;
			string timeData;
			cout << "Enter your name to save your score: ";
			cin.ignore();
			getline(cin, timeData);
			timeData += "\t\t" + to_string(finish - start) + "\t\t" + to_string(fails);
			toScores(fromScores(), timeData);
			break;
		}
		else if (fails >= 9) {
			cout << "You lose :(" << endl << "The word was " << bakWord << endl;
			finish = time(0);
			cout << "Time: " << finish - start << endl;
			string timeData;
			cout << "Enter your name to save your score: ";
			cin.ignore();
			getline(cin, timeData);
			timeData += "\t\t" + to_string(finish - start) + " X" + "\t\t" + to_string(fails);
			toScores(fromScores(), timeData);

			break;
		}
		//print word
		cout << endl << dispWord << endl << word.length() << " letter word" << endl;
		//guessed letters:
		cout << "Guessed letters:" << endl;
		for (int i = 0; i < 26; i++) {
			cout << guessed[i] << ' ';
			if (i == 5 || i == 11 || i == 17 || i == 23 || i == 25) {
				cout << endl;
			}
		}
		//get new lettter
		cout << "New letter guess: ";
		cin >> usrChar;
		while (cin.fail()) {
			cin.clear();
			cin.ignore();
		}
		while (usrChar < 'a' || usrChar > 'z') {
			do {
				cin.clear();
				cin.ignore();
				cin >> usrChar;
			} while (cin.fail());
		}
		posFinder = usrChar;
		//check letter
		while (posFinder != 'a') {
				posFinder--;
				lettPos++;
		}
		if (guessed[lettPos] == usrChar) {
			cout << "You already guessed that letter!" << endl;
			continue;
		}
		else {
			guessed[lettPos] = usrChar;
		}

		if (word.find(usrChar) == -1) {
			cout << "Letter not found :(" << endl;
			fails++;
		}
		else {
			cout << "Good guess!" << endl;
			while (word.find(usrChar) != -1) {
				dispWord[word.find(usrChar)] = usrChar;
				word[word.find(usrChar)] = ' ';
			}
		}
	}
}

void toScores(string oldTimes, string newTime) {
	ofstream outData;
	outData.open("bestTimes.dat");
	if (outData.is_open()) {
		outData << oldTimes << endl << newTime << endl;
		outData.close();
	}


}
string fromScores() {
	string tmp;
	string inFo;
	ifstream inData;
	inData.open("bestTimes.dat");
	if (inData.is_open()) {
		while (getline(inData, tmp)) {
			inFo += tmp;
			inFo += "\n";
		}
	}
	return inFo;

}

