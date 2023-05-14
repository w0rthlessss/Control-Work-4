#include "Cyphers.h"
#include <Windows.h>
#define uc unsigned char
int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");

	string o = GetLine("Enter a message:\n>>");
	//getline(cin, o);
	//Caesar tmp(o);
	//Vigenere tmp(o);
	Atbash tmp(o);
    
	cout << tmp.GetName() << endl;
	cout << "Original: " << tmp.GetOriginal() << endl;

	/*int key1 = GetInt("Enter a key for encrypting:\n>>");
	cout << "Encrypted: " << tmp.GetEncrypted(key1) << endl;
	int key2 = GetInt("Enter a key for decrypting:\n>>");
	cout << "Decrypted: " << tmp.GetDecrypted(key2) << endl;*/

    /*string key1 = GetString("Enter a key for encrypting:\n>>");
    cout << "Encrypted: " << tmp.GetEncrypted(key1) << endl;
    string key2 = GetString("Enter a key for decrypting:\n>>");
    cout << "Decrypted: " << tmp.GetDecrypted(key2) << endl;*/

	cout << "Encrypted: " << tmp.GetEncrypted() << endl;
	cout << "Decrypted: " << tmp.GetDecrypted() << endl;

	
}