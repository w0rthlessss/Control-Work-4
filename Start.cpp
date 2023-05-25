#include "UserInterface.h"
#include "ModuleTests.h"

int main() {
	win::SetConsoleCP(1251);
	win::SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

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
			LaunchAllTests();
			system("pause");
			break;
		case TopMenu::quit:
			cout << "Programm finished it's work!\n\n";
			exit(EXIT_SUCCESS);
		default:
			IncorrectOption();
			break;
		}
		system("cls");
	}
}