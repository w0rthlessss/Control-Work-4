#include "ModuleTests.h"

const string original = "dumb sequence - bogey for limited minds";

//File input test
bool Test1()
{
    const string fileName = "test_info.txt";
    fstream file(fileName, ios::out | ios::trunc);
    file << original << endl << endl << endl << endl << endl;
    file.close();
    file.open(fileName, ios::in);
    if (!file.is_open()) {
        cout << "TEST#1 (File Input): FAILURE!\nFile, created by programm does not exist!\n\n";
        return false;
    }

    string tmp = FileInput(file);

    if (tmp != original + '\n') {
        cout << "TEST#1 (File Input): FAILURE!\nText, that was read from the file, does not match the original message!\n\n";
        return false;
    }

    return true;
    
}

//Caesar Cypher test
bool Test2()
{
    
    Caesar tmp(original);
    const int key = 21;
    const string encrypted = "yphw nzlpzixz - wjbzt ajm gdhdozy hdiyn";

    tmp.Encrypt(key);

    if (tmp.GetEncrypted() != encrypted) {
        cout << "TEST#2 (Caesar Cypher): FAILURE!\nEncrypted messages do not match!\n\n";
        return false;
    }

    tmp.Decrypt(key);

    if (tmp.GetDecrypted() != original) {
        cout << "TEST#2 (Caesar Cypher): FAILURE!\nDecrypted message does not match the original one!\n\n";
        return false;
    }
    
    return true;
}

//Atbash Cypher test
bool Test3()
{
    Atbash tmp(original);
    const string encrypted = "wfny hvjfvmxv - yltvb uli ornrgvw nrmwh";
    const int key = 0;

    tmp.Encrypt(key);

    if (tmp.GetEncrypted() != encrypted) {
        cout << "TEST#3 (Atbash Cypher): FAILURE!\nEncrypted messages do not match!\n\n";
        return false;
    }

    tmp.Decrypt(key);

    if (tmp.GetDecrypted() != original) {
        cout << "TEST#3 (Atbash Cypher): FAILURE!\nDecrypted message does not match the original one!\n\n";
        return false;
    }

    return true;
}

//Number replace Cypher test
bool Test4()
{
    Replace tmp(original);
    const string encrypted = "L03L14L0cL01 L12L04L10L14L04L0dL02L04 - L01L0eL06L04L18 L05L0eL11 L0bL08L0cL08L13L04L03 L0cL08L0dL03L12";
    const int key = 0;

    tmp.Encrypt(key);

    if (tmp.GetEncrypted() != encrypted) {
        cout << "TEST#4 (Number replace Cypher): FAILURE!\nEncrypted messages do not match!\n\n";
        return false;
    }

    tmp.Decrypt(key);

    if (tmp.GetDecrypted() != original) {
        cout << "TEST#3 (Number replace Cypher): FAILURE!\nDecrypted message does not match the original one!\n\n";
        return false;
    }

    return true;
}

//Console input test
bool Test5()
{
    istringstream test("576\n\n");
    streambuf* cinbuf = cin.rdbuf(test.rdbuf());

    bool res = (GetInt("") == 576);

    if (!res) {
        cout << "TEST#5 (Console Input): FAILURE!\nIncorrect console input!\n\n";
        return false;
    }

    cin.rdbuf(cinbuf);

    return true;
}

void LaunchAllTests()
{
    bool tests[5] = { Test1(), Test2(), Test3(), Test4(), Test5() };
    if (tests[0] && tests[1] && tests[2] && tests[3] && tests[4]) cout << "\nAll tests SUCCEDED!\n\n";
}
