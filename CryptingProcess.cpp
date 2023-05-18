#include "CryptingProcess.h"
#include <regex>

void EncryptMessage(shared_ptr<Crypt> tmp) {
    fstream fout;
    cout << tmp->GetName() << endl<<endl;
    tmp->ShowInfo();
    int key = 0;
    cout << "Original message: " << tmp->GetOriginal() << endl;

    if (tmp->GetName() == "<<Caesar cypher>>")  key = GetInt("Enter a key for encrypting:\n>>");

    tmp->Encrypt(key);
    if(tmp->GetKeyE()!=0) cout << "Key for encryption = " << tmp->GetKeyE() << endl;
    cout << "Encrypted message: " << tmp->GetEncrypted() << endl;
    char c = SaveResults("\nDo you want to save encrypted message in the file");
    if (c == 'y') {
        OpenFile(WorkWithFiles::output, fout);
        fout << tmp->GetEncrypted();
        fout.close();
    }

    c = SaveResults("\nDo you want to decode this encoded message with current cypher");
    if (c == 'y') {
        if (tmp->GetName() == "<<Caesar cypher>>") key = GetInt("Enter a key for decrypting:\n>>");

        tmp->Decrypt(key);
        cout << "Decrypted message: " << tmp->GetDecrypted() << endl;
        if (SaveResults("\nDo you want to save whole crypting process in the file") == 'y') {
            OpenFile(WorkWithFiles::output, fout);
            SaveAll(tmp, fout);
            fout.close();
        }
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
            break;

        case SubBottomMenu::atbash:
            EncryptMessage(make_shared<Atbash>(msg));
            break;

        case SubBottomMenu::replace:
            EncryptMessage(make_shared<Replace>(msg));
            break;

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

    shared_ptr<Crypt> method = nullptr;
    fstream fout;
    int keyD = GetInt("\nEnter a key for decrypting. If the message don't require any, enter 0:\n>>");

    if (keyD != 0) {
        method = make_shared<Caesar>(msg);
    }

    else {
        regex pattern1("L[0-9a-f]{2}"), pattern2("C[0-9A-fa-f]{2}");
        if (regex_search(msg, pattern1) || regex_search(msg, pattern2)) method = make_shared<Replace>(msg);
        else method = make_shared<Atbash>(msg);
    }

    cout << endl << method->GetName() << endl;
    cout << "Encrypted message: " << method->GetEncrypted()<<endl;
    method->Decrypt(keyD);
    cout << "Decrypted message: " << method->GetDecrypted()<<endl;
    
    if (SaveResults("Do you want to save decoding process in the file") == 'y') {
        OpenFile(WorkWithFiles::output, fout);

        fout << method->GetName() << endl;
        fout << "Encrypted message: " << method->GetEncrypted() << endl;
        fout << "Decrypted message: " << method->GetDecrypted() << endl;
    }
}
