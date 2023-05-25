#include "InputOutputController.h"
#include <filesystem>

using namespace filesystem;

char SaveResults(string msg)
{
	cout << msg<<" ? (y / n)\n\n";
	char res = 'n';
	do {
		res = GetChar(">>");
		if (res != 'y' && res != 'n') {
			cout << "Incorrect input. Type 'y' or 'n' only!\n\n";
		}
	} while (res != 'y' && res != 'n');

	return res;
}

void OpenFile(int option, fstream& file)
{
	string name = "";
	error_code ec;
	if (option == WorkWithFiles::input) {
		do {
			name = GetLine("\nEnter the name of file with data. Example: students.txt\n");
			file.open(name, ios::in);
			if (!file.is_open()) {
				cout << "\nError opening file. Make sure, that file exists!\n";
				continue;
			}

			if (!is_regular_file(name, ec)) {
				cout << "\nAdress contains forbidden value. Try another file path!\n";
				continue;
			}
			return;
		} while (true);


	}
	else {
		do {
			name = GetLine("\nEnter the name of file where results will be stored.\nExample: results.txt\n\n");

			if (exists(name)) {
				if (SaveResults("\nFile exists. Do you want to overwrite current data in the file") == 'n') continue;
			}

			file.open(name, ios::out | ios::trunc);

			if (!is_regular_file(name, ec)) {
				cout << "\nAdress contains forbidden value. Try another file path!\n";
				continue;
			}

			return;
		} while (true);

	}
}

string FileInput(fstream& fin)
{
	string tmp = "", res ="";
	while (getline(fin, tmp)) if (!tmp.empty()) res += tmp + '\n';
	fin.close();
	return res;
}
