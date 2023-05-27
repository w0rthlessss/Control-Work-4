#pragma once
#include "GetInfo.h"
#include <sstream>

class Crypt {

protected:
	string name;
	string original;
	string encrypted;
	string decrypted;
	int keyE;
	int keyD;

	bool isCyrillic(int c) {
		if (c >= AlphabetBorders::lLower && c <= AlphabetBorders::lUpper) return false;
		else return true;
	}

	bool isUpper(uc c){
		if (toupper(c) == int(c)) return true;
		else return false;
	}

	void Check(uc &c) {
		if (tolower(c) == 184) {
			if (isUpper(c)) c = 197;
			else c = 229;
		}
	}

public:
	Crypt() {
		name = "";
		original = "";
		encrypted = "";
		decrypted = "";
	}

	Crypt(string s) {original = s;}

	virtual ~Crypt() = default;

	virtual void Encrypt(int key) = 0;

	virtual void Decrypt(int key) = 0;

	int GetKeyE() { return keyE; }

	int GetKeyD() { return keyD; }

	string GetName() {return name; }

	string GetOriginal() {return original;}
	
	string GetEncrypted() { return encrypted; }

	string GetDecrypted() { return decrypted; }

	virtual void ShowInfo() = 0;
};

class Caesar : public Crypt {
private:
	
	uc CryptLetter(uc c, int key, int l, int r) {
		uc tmp = '\0';
		if (tolower(c) + key < l) {
			tmp = uc(r - (l - (tolower(c) + key))+1);
		}
		else if (tolower(c) + key > r) {
			tmp = uc(l + (tolower(c) + key - r) - 1);
		}
		else tmp = uc(c + key);

		if (isUpper(c)) return uc(toupper(tmp));
		else return tmp;
	}

	string Crypt(int key, string msg) {
		string tmp = "";
		for (int i = 0; i < msg.length(); i++) {
			uc c = msg[i];
			if (isalpha(c)) {
				if (!isCyrillic(tolower(c))) {
					key %= 26;
					tmp += CryptLetter(c, key, AlphabetBorders::lLower, AlphabetBorders::lUpper);
				}
				else {
					key %= 33;
					Check(c);
					tmp += CryptLetter(c, key, AlphabetBorders::cLower, AlphabetBorders::cUpper);
				}
			}
			else tmp += msg[i];
		}
		return tmp;
	}

public:
	
	virtual ~Caesar() = default;

	Caesar(string s) { name = "<<Caesar cypher>>"; original = s; encrypted = s; }

	virtual void Encrypt(int k) override{
		keyE = k;
		encrypted = Crypt(k, original);
	}

	virtual void Decrypt(int k) override{
		keyD = k;
		decrypted = Crypt(-k, encrypted);
	}

	virtual void ShowInfo() override {
		cout << "Cypher replaces letters in text with a letter \"key\" positions down the alphabet.\n";
		cout << "Example:\nKey = 3\nOriginal text = ABCD\nEncrypted text = DEFG\n\n";
	}
};


//class Vigenere : public Crypt {
//private:
//	 
//	uc CryptLetter(bool encrypt, uc c, uc k, int l, int alphSize) {
//		uc tmp = '\0';
//		
//		if (encrypt)  tmp = uc((tolower(c) + tolower(k) - 2 * l) % alphSize + l);
//		else  tmp = uc((tolower(c) - tolower(k) + alphSize) % alphSize + l);
//
//		if (isUpper(c)) return uc(toupper(tmp));
//		else return tmp;
//	}
//
//	string Crypt(string key, string msg, bool encrypt) {
//		string tmp = "";
//		for (int i = 0, j = 0; i < msg.length(); i++) {
//			uc c = msg[i];
//			uc k = key[j];
//			if (isalpha(c)) {
//				if (!isCyrillic(tolower(c))) {
//					tmp += CryptLetter(encrypt, c, k, AlphabetBorders::lLower, 26);
//					j = (j + 1) % key.length();
//				}
//				else {
//					Check(c);
//					Check(k);
//					tmp += CryptLetter(encrypt, c, k, AlphabetBorders::cLower, 32);
//					j = (j + 1) % key.length();
//				}
//			}
//			else tmp += c;
//		}
//		return tmp;
//	}
//
//public:
//
//	virtual ~Vigenere() = default;
//
//	Vigenere(string s) { name = "<<Vigenere cypher>>"; original = s; encrypted = s; }
//
//	void Encrypt(string key) {
//		encrypted = Crypt(key, original, true);
//	}
//
//	void Decrypt(string key) {
//		decrypted = Crypt(key, encrypted, false);
//	}
//	
//};


class Atbash : public Crypt {
private:

	uc CryptLetter(uc c, int l, int r) {
		uc tmp = '\0';
		tmp = uc(r - (tolower(c) - l));
		if (isUpper(c)) return uc(toupper(tmp));
		else return tmp;
	}

	string Crypt(string msg) {
		string tmp = "";
		for (int i = 0; i < msg.length(); i++) {
			uc c = msg[i];
			if (isalpha(tolower(c))) {
				if (!isCyrillic(tolower(c))) tmp += CryptLetter(c, AlphabetBorders::lLower, AlphabetBorders::lUpper);
				else {
					Check(c);
					tmp += CryptLetter(c, AlphabetBorders::cLower, AlphabetBorders::cUpper);
				}
			}
			else tmp += c;
		}
		return tmp;

	}

public:

	virtual ~Atbash() = default;

	Atbash(string s) { name = "<<Atbash cypher>>"; original = s; encrypted = s; }

	virtual void Encrypt(int k) override{
		keyE = k;
		encrypted = Crypt(original);
	}

	virtual void Decrypt(int k) override{
		keyD = k;
		decrypted = Crypt(encrypted);
	}

	virtual void ShowInfo() override {
		cout << "Cypher replaces letters in text with a letter from another side of the aplhabet on the same position\n";
		cout << "Example:\nOriginal text = ABCXYZ\nEncrypted text = ZYXCBA\n\n";
	}
};

class Replace : public Crypt {
private:

	string DecToHex(int n) {
		stringstream s;
		s << hex << n;
		return s.str();
	}

	string EncryptLetter(uc c) {
		string res = "";
		char check = '\0';
		if (!isCyrillic(tolower(c))) {
			check = 'L';
			res = DecToHex(tolower(c) - AlphabetBorders::lLower);
		}
		else {
			check = 'C';
			Check(c);
			res = DecToHex(tolower(c) - AlphabetBorders::cLower);
		}
		return (res.length() < 2) ? (check + to_string(0) + res) : (check + res);
	}

	string EncryptMessage(string msg) {
		string tmp = "";
		for (int i = 0; i < msg.length(); i++) {
			uc c = msg[i];
			if (isalpha(tolower(c))) {
				tmp += EncryptLetter(c);
			}
			else {
				tmp += c;
			}
		}
		return tmp;
	}

	string DecryptMessage(string msg) {
		string tmp = "", code ="";
		for (int i = 0; i < msg.length() - 2; i++) {
			uc c = msg[i];
			code += msg[i + 1]; code += msg[i + 2];
			switch (c) {

			case 'L':
				tmp += uc(AlphabetBorders::lLower + stoul(code, nullptr, 16));
				i += 2;
				break;
			case 'C':
				tmp += uc(AlphabetBorders::cLower + stoul(code, nullptr, 16));
				i += 2;
				break;
			default:
				tmp += c;
				break;
			}

			if (i == msg.length() - 3 && code != "") {
				tmp += msg[i + 1];
				tmp += msg[i + 2];
			}
			
			code = "";
		}
		return tmp;
	}

public:

	virtual ~Replace() = default;

	Replace(string s) { name = "<<Number replace cypher>>"; original = s; encrypted = s; }

	virtual void Encrypt(int k) override{
		keyE = k;
		encrypted = EncryptMessage(original);
	}

	virtual void Decrypt(int k) override{
		keyD = k;
		decrypted = DecryptMessage(encrypted);
	}

	virtual void ShowInfo() override {
		cout << "Cypher replaces letters in text with an alphabet code and their number in the alphabet in hexadecimal system\n";
		cout << "Example:\nOriginal text = ALOHA\nEncrypted text = L00L0bL0eL07L00\n\n";
	}
};