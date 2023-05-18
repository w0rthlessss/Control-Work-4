#pragma once
#include "GetInfo.h"

class Crypt {

protected:
	std::string name;
	std::string original;
	std::string encrypted;
	std::string decrypted;

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

	Crypt(std::string s) {original = s;}

	virtual ~Crypt() = default;

	std::string GetName() {return name;}

	std::string GetOriginal() {return original;}
	
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

	std::string Encrypt(int key, std::string msg) {
		std::string tmp = "";
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

	Caesar(std::string s) { name = "Caesar cypher"; original = s; encrypted = s; }

	std::string GetEncrypted(int key) {
		encrypted = Encrypt(key, original);
		return encrypted;
	}

	std::string GetDecrypted(int key) {
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

	std::string Encrypt(std::string key, std::string &msg, bool encrypt) {
		std::string tmp = "";
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

	Vigenere(std::string s) { name = "Vigenere cypher"; original = s; encrypted = s; }

	std::string GetEncrypted(std::string key) {
		encrypted = Encrypt(key, original, true);
		return encrypted;
	}

	std::string GetDecrypted(std::string key) {
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

	std::string Encrypt(std::string msg) {
		std::string tmp = "";
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

	Atbash(std::string s) { name = "Atbash cypher"; original = s; encrypted = s; }

	std::string GetEncrypted() {
		encrypted = Encrypt(original);
		return encrypted;
	}

	std::string GetDecrypted() {
		decrypted = Encrypt(encrypted);
		return decrypted;
	}
};