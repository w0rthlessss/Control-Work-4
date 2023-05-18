#include "UserInterface.h"
#include "CryptingProcess.h"

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
			msg = GetLine("\n\nEnter a message that must be encrypted:\n");
			Encrypting(msg);
			break;

		case BottomMenu::decrypt:
			msg = GetLine("\n\nEnter a message that must be decrypted:\n");
			Decrypting(msg);
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
			getline(fin, msg);
			Encrypting(msg);
			break;

		case BottomMenu::decrypt:
			OpenFile(WorkWithFiles::input, fin);
			getline(fin, msg);
			Decrypting(msg);
			break;
		case BottomMenu::back:
			system("cls");
			break;
		default:
			IncorrectOption();
			break;
		}

	}
}


