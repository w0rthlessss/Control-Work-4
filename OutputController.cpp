#include "OutputController.h"
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

//void SaveAll(shared_ptr<Crypt> method, fstream &fout)
//{
//	fout << method->GetName() << endl;
//	fout << "Encrypted: " << method->GetEncrypted() << endl;
//	fout << "Decrypted: " << method->GetDecrypted() << endl;
//	fout.close();
//}

string OpenFile(int option, fstream& file)
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

			if (!filesystem::is_regular_file(name, ec)) {
				cout << "\nAdress contains forbidden value. Try another file path!\n";
				continue;
			}
			return name;
		} while (true);


	}
	else {
		do {
			name = GetLine("\nEnter the name of file where results will be stored.\nIf there is data in the file it will be overwritten.\nExample: results.txt\n");

			file.open(name, ios::out, ios::trunc);

			if (!filesystem::is_regular_file(name, ec)) {
				cout << "\nAdress contains forbidden value. Try another file path!\n";
				continue;
			}

			return name;
		} while (true);

	}
}