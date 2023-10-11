#include "InputOutputController.h"
#include <io.h>
#include <cerrno>
#include <filesystem>

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
	if (option == WorkWithFiles::input) {
		do {
			name = GetLine("\nEnter the name of file with data. Example: testFile.txt\n");

			if (_access(name.c_str(), 0) == 0) {
				file.open(name.c_str(), ios::in);
			}
			else {
				if (errno == ENOENT) {
					cout << "\nError opening file. Make sure, that file exists!\n";
					continue;
				}
				else {
					cout << "\nAdress contains forbidden value!\n";
					continue;
				}
			}
			
			return;
		} while (true);


	}
	else {
		do {
			name = GetLine("\nEnter the name of file where results will be stored.\nExample: results.txt\n\n");

			if (_access(name.c_str(), 0) == 0) {

				if (filesystem::exists(name)) {
					if (SaveResults("\nFile exists. Do you want to overwrite current data in the file") == 'n') continue;
				}

				file.open(name.c_str(), ios::out);
			}
			else {
				if (errno == ENOENT) {
					file.open(name.c_str(), ios::out);
				}
				else {
					cout << "\nAdress contains forbidden value!\n";
					continue;
				}
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

string ConsoleInput(string msg)
{
	cout << msg;
	string tmp = "tmp", res = "";
	while (getline(cin, tmp) && !tmp.empty()) {
		cout << ">>"; res += tmp + '\n';
	}
	return res;
}
