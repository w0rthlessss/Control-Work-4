#include "CryptingProcess.h"
#include <regex>

void EncryptMessage(shared_ptr<Crypt> tmp) {
    fstream fout;

    cout << endl <<tmp->GetName() << endl << endl;
    tmp->ShowInfo();
    int key = 0;
    cout << "\nOriginal message:" << endl << tmp->GetOriginal() << endl << endl;

    if (tmp->GetName() == "<<Caesar cypher>>")  key = GetInt("Enter a key for encrypting:\n>>");

    tmp->Encrypt(key);
    if (tmp->GetKeyE() != 0) cout << "\nKey for encryption = " << tmp->GetKeyE() << endl << endl;
    cout << "Encrypted message:" << endl << tmp->GetEncrypted() << endl;

    char ans = SaveResults("\nDo you want to save the encrypted message in the file");
    if (ans == 'y') {
        OpenFile(WorkWithFiles::output, fout);
        fout << tmp->GetEncrypted() << endl;
        fout.close();
        cout << "\nData was successfully written in the file!\n\n";
    }
}

void Encrypting(string msg)
{
    shared_ptr<Crypt> method = nullptr;
    int actionSubBottom = 1;
    
    while (actionSubBottom != SubBottomMenu::backToBottom) {
        OptionsSubBottom();
        actionSubBottom = GetInt(">>");
        switch (actionSubBottom) {
        case SubBottomMenu::caesar:
            EncryptMessage(make_shared<Caesar>(msg));
            return;

        case SubBottomMenu::atbash:
            EncryptMessage(make_shared<Atbash>(msg));
            return;

        case SubBottomMenu::replace:
            EncryptMessage(make_shared<Replace>(msg));
            return;

        case SubBottomMenu::backToBottom:
            system("cls");
            Task();
            Fio();
            break;

        default:
            IncorrectOption();
            break;
        }
    }
   
}

bool CheckMsg(string msg) {
    for (uc u : msg) {
        int n = tolower(u);
        if ((n >= AlphabetBorders::cLower && n <= AlphabetBorders::cUpper || n == 184)
            || (n >= AlphabetBorders::lLower && n <= AlphabetBorders::cUpper))
            return true;
    }
    return false;
}

void Decrypting(string msg)
{
    if (!CheckMsg(msg)) {
        cout << "\nMessage does not contain any text information. Nothing to decode!\n\n";
        return;
    }

    int keyD = 0;

    shared_ptr<Crypt> method = nullptr;
    fstream fout;
    char code = msg[0];
    switch (code) {
    case '1':
        method = make_shared<Caesar>(msg);
        break;
    case '2':
        method = make_shared<Atbash>(msg);
        break;
    case '3':
        method = make_shared<Replace>(msg);
        break;
    }

    cout << endl << method->GetName() << endl;
    cout << "Encrypted message:" << endl << method->GetEncrypted() << endl << endl;
    if (code == '1') {
        keyD = GetInt("Enter a key for decrypting:\n>>");
    }
    method->Decrypt(keyD);
    cout << "Decrypted message:" << endl << method->GetDecrypted() << endl;
    
    if (SaveResults("Do you want to save decrypted message in the file") == 'y') {
        OpenFile(WorkWithFiles::output, fout);
        fout << method->GetDecrypted()<<endl;
        fout.close();
        cout << "\nData was successfully written in the file!\n\n";
    }
}
