#include "GetInfo.h"
//очистка потока ввода
void IgnoreLine()
{
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

//считывание целого числа с консоли
int GetInt(string s) {

	cout << s;
	int tmp = 0;
	while (true) {
		cin >> tmp;
		if (cin.fail()) {
			IgnoreLine();
			cout << "\nUse correct values!\n\n";
			cout << s;
		}
		else if (tmp < 0) {
			cout << "\nValue must be >=0\n\n";
			IgnoreLine();
			cout << s;
		}
		else {
			IgnoreLine();
			return tmp;
		}
	}
}


//считывание  строки 
string GetLine(string s)
{
	string b = "";
	cout << s;
	do {
		cout << ">>";
		getline(cin, b);
		if (b.empty()){
			cout << "\nString must not be empty!\n\n";
			cout << s;
			continue;
		}
	} while (b.empty());
	return b;

}

//считывание ответа y/n
char GetChar(string s)
{
	char tmp = '\n';
	cout << s;
	while (true) {
		cin >> tmp;
		if (tmp == '\n') {
			cout << "\nYou must type y or n!\n\n";
			cout << s;
			IgnoreLine();
		}
		else if (getchar() != '\n') {
			cout << "\nIncorrect input! Type only y or n!\n\n";
			cout << s;
			IgnoreLine();
		}
		else return tmp;
	}
}
