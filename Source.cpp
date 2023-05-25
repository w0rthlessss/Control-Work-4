#include "UserInterface.h"

int main() {
	win::SetConsoleCP(1251);
	win::SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

	/*Atbash tmp("ABCXYZ");
	cout << "ABCXYZ" << endl;
	tmp.Encrypt(0);
	cout << tmp.GetEncrypted() << endl;
	tmp.Decrypt(0);
	cout << tmp.GetDecrypted() << endl;*/
	int actionTop = 1;
	
	while (actionTop != TopMenu::quit) {
		Task();
		Fio();
		OptionsTop();
		actionTop = GetInt(">>");
		switch (actionTop) {
		case TopMenu::console:
			WorkWithConsole();
			break;
		case TopMenu::file:
			WorkWithFile();
			break;
		case TopMenu::module:
			//
			break;
		case TopMenu::quit:
			cout << "Programm finished it's work!\n\n";
			exit(EXIT_SUCCESS);
		default:
			IncorrectOption();
			Continue();
			break;
		}
		system("cls");
	}
}