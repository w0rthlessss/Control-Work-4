#include "Information.h"

void Fio()
{
	cout << "Control work #4\nEfremov Ivan Andreevich\nGroup #423\nVariant #8\n\n";
}

void OptionsTop()
{
	cout << "[1] - Console input\n[2] - File input\n[3] - Run module tests\n[4] - Exit\n\n";
}

void OptionsBottom()
{
	cout << "\n[1] - Encrypt message\n";
	cout << "[2] - Decrypt message\n";
	cout << "[3] - Back\n\n";
}

void OptionsSubBottom() {
	cout << "\n\nChoose a crypting method:\n\n";
	cout << "[1] - Ceasar cypher\n";
	cout << "[2] - Atbash cypher\n";
	cout << "[3] - Replace cypher\n";
	cout << "[4] - Back\n\n";
}

void Task()
{
	cout << "Create 3 different text crypting methods.\n"
		<< "Implement the ability of decrypting the encrypting text.\n"
		<< "Program must independently determin which encrypting method was used\n"
		<< "At least one of the options must require a key for encrypting and decrypting\n\n";
}

void IncorrectOption()
{
	cout << "\nThere is no such option in menu!\n\n";
}