#pragma once

#include "Information.h"
#include "CryptingProcess.h"

char SaveResults(string msg);

void SaveAll(shared_ptr<Crypt> method, fstream &fout);

string OpenFile(int option, fstream& file);