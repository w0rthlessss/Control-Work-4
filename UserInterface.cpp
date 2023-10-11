#include "UserInterface.h"

void Continue() {
	cout << "\nPress enter to continue!\n";
	if (getchar() != '\n') {
		IgnoreLine();
	}
}

void WorkWithConsole()
{
	int actionBottom = 1;
	string msg = "";
	while (actionBottom != BottomMenu::back) {
		OptionsBottom();
		actionBottom = GetInt(">>");
		switch (actionBottom) {

		case BottomMenu::encrypt:
			msg = ConsoleInput("\n\nEnter a message that must be encrypted. Press Enter 2 times to confirm\n\n>>");
			Encrypting(msg);
			return;

		case BottomMenu::decrypt:
			msg = ConsoleInput("\n\nEnter a message that must be decrypted. Press Enter 2 times to confirm\n\n>>");
			Decrypting(msg);
			return;

		case BottomMenu::back:
			system("cls");
			break;
		default:
			IncorrectOption();
			break;
		}

	}
}

void WorkWithFile()
{
	fstream fin;
	int actionBottom = 1;
	string msg = "";
	while (actionBottom != BottomMenu::back) {
		OptionsBottom();
		actionBottom = GetInt(">>");
		switch (actionBottom) {

		case BottomMenu::encrypt:
			OpenFile(WorkWithFiles::input, fin);
			msg = FileInput(fin);
			Encrypting(msg);
			return;

		case BottomMenu::decrypt:
			OpenFile(WorkWithFiles::input, fin);
			msg = FileInput(fin);
			Decrypting(msg);
			return;

		case BottomMenu::back:
			system("cls");
			break;

		default:
			IncorrectOption();
			break;
		}

	}
}


