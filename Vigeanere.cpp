#include <iostream>
#include <string>

using namespace std;

string encrypt(string message, string key) {
    string result = "";
    int keyIndex = 0;
    for (int i = 0; i < message.length(); i++) {
        char c = message[i];
        if (isalpha(c)) {
            c = toupper(c);
            int shift = key[keyIndex] - 'A';
            c = ((c - 'A' + shift) % 26) + 'A';
            keyIndex = (keyIndex + 1) % key.length();
        }
        result += c;
    }
    return result;
}

string decrypt(string message, string key) {
    string result = "";
    int keyIndex = 0;
    for (int i = 0; i < message.length(); i++) {
        char c = message[i];
        if (isalpha(c)) {
            c = toupper(c);
            int shift = key[keyIndex] - 'A';
            c = ((c - 'A' - shift + 26) % 26) + 'A';
            keyIndex = (keyIndex + 1) % key.length();
        }
        result += c;
    }
    return result;
}

int main() {
    string message = "I love Ilya Ekkert";
    string key = "WORLD";
    string encrypted = encrypt(message, key);
    cout << "Encrypted message: " << encrypted << endl;
    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted message: " << decrypted << endl;
    return 0;
}