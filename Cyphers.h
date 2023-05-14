#pragma once
#include "GetInfo.h"

class Crypt {

protected:
	string name;
	string original;
	string encrypted;
	string decrypted;

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

	string GetName() {return name;}

	string GetOriginal() {return original;}
	
};

//template<typename T>
class Caesar : public Crypt {
private:
	
	uc EncryptLetter(uc c, int key, int l, int r) {
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

	string Encrypt(int key, string msg) {
		string tmp = "";
		for (int i = 0; i < msg.length(); i++) {
			uc c = msg[i];
			if (isalpha(c)) {
				if (!isCyrillic(tolower(c))) {
					key %= 26;
					tmp += EncryptLetter(c, key, AlphabetBorders::lLower, AlphabetBorders::lUpper);
				}
				else {
					key %= 33;
					Check(c);
					tmp += EncryptLetter(c, key, AlphabetBorders::cLower, AlphabetBorders::cUpper);
				}
			}
			else tmp += msg[i];
		}
		return tmp;
	}

public:
	
	virtual ~Caesar() = default;

	Caesar(string s) { name = "Caesar cypher"; original = s; encrypted = s; }

	string GetEncrypted(int key) {
		encrypted = Encrypt(key, original);
		return encrypted;
	}

	string GetDecrypted(int key) {
		decrypted = Encrypt(-key, encrypted);
		return decrypted;
	}

};


class Vigenere : public Crypt {
private:

	uc EncryptLetter(bool encrypt, uc c, uc k, int l, int alphSize) {
		uc tmp = '\0';
		
		if (encrypt)  tmp = uc((tolower(c) + tolower(k) - 2 * l) % alphSize + l);
		else  tmp = uc((tolower(c) - tolower(k) + alphSize) % alphSize + l);

		

		if (isUpper(c)) return uc(toupper(tmp));
		else return tmp;
	}

	string Encrypt(string key, string &msg, bool encrypt) {
		string tmp = "";
		for (int i = 0, j = 0; i < msg.length(); i++) {
			uc c = msg[i];
			uc k = key[j];
			if (isalpha(c)) {
				if (!isCyrillic(tolower(c))) {
					tmp += EncryptLetter(encrypt, c, k, AlphabetBorders::lLower, 26);
					j = (j + 1) % key.length();
				}
				else {
					Check(c);
					Check(k);
					tmp += EncryptLetter(encrypt, c, k, AlphabetBorders::cLower, 32);
					j = (j + 1) % key.length();
				}
			}
			else tmp += c;
		}
		return tmp;
	}

public:

	virtual ~Vigenere() = default;

	Vigenere(string s) { name = "Vigenere cypher"; original = s; encrypted = s; }

	string GetEncrypted(string key) {
		encrypted = Encrypt(key, original, true);
		return encrypted;
	}

	string GetDecrypted(string key) {
		decrypted = Encrypt(key, encrypted, false);
		return decrypted;
	}

	
};


class Atbash : public Crypt {
private:

	uc EncryptLetter(uc c, int l, int r) {
		uc tmp = '\0';
		tmp = uc(r - (tolower(c) - l));
		if (isUpper(c)) return uc(toupper(tmp));
		else return tmp;
	}

	string Encrypt(string msg) {
		string tmp = "";
		for (int i = 0; i < msg.length(); i++) {
			uc c = msg[i];
			if (isalpha(tolower(c))) {
				if (!isCyrillic(tolower(c))) tmp += EncryptLetter(c, AlphabetBorders::lLower, AlphabetBorders::lUpper);
				else {
					Check(c);
					tmp += EncryptLetter(c, AlphabetBorders::cLower, AlphabetBorders::cUpper);
				}
			}
			else tmp += c;
		}
		return tmp;

	}

public:

	virtual ~Atbash() = default;

	Atbash(string s) { name = "Atbash cypher"; original = s; encrypted = s; }

	string GetEncrypted() {
		encrypted = Encrypt(original);
		return encrypted;
	}

	string GetDecrypted() {
		decrypted = Encrypt(encrypted);
		return decrypted;
	}
};