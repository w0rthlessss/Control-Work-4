//#include <iostream>
//#include <string>
//
//using namespace std;
//
//string encrypt(string text, int shift) {
//    string result = "";
//    for (int i = 0; i < text.length(); i++) {
//        char c = text[i];
//        if (isalpha(c)) {
//            c = toupper(c);
//            c = (c + shift - 65) % 26 + 65;
//        }
//        result += c;
//    }
//    return result;
//}
//
//string decrypt(string text, int shift) {
//    return encrypt(text, 26 - shift);
//}
//
//int main() {
//    string text = "I love Ilya Gnidin";
//    int shift = 100;
//    string encrypted = encrypt(text, shift);
//    string decrypted = decrypt(encrypted, shift);
//    cout << "Original text: " << text << endl;
//    cout << "Encrypted text: " << encrypted << endl;
//    cout << "Decrypted text: " << decrypted << endl;
//    return 0;
//}


#include <iostream>
#include <string>

using namespace std;

string encrypt(string message, int key) {
    string result = "";
    for (int i = 0; i < message.length(); i++) {
        char c = message[i];
        if (isalpha(c)) {
            c = toupper(c);
            c = ((c - 65 + key) % 26) + 65;
        }
        result += c;
    }
    return result;
}

string decrypt(string message, int key) {
    string result = "";
    for (int i = 0; i < message.length(); i++) {
        char c = message[i];
        if (isalpha(c)) {
            c = toupper(c);
            c = ((c - 65 - key + 26) % 26) + 65;
        }
        result += c;
    }
    return result;
}

int main() {
    string message = "I love Ilya Gnidin";
    int key = 100;
    string encrypted = encrypt(message, key);
    cout << "Encrypted message: " << encrypted << endl;
    string decrypted = decrypt(encrypted, key);
    cout << "Decrypted message: " << decrypted << endl;
    /*int a = 10, b = 5;
    cout << [](int x, int y) {return x + y; } (a, b);
    return 0;*/
}

