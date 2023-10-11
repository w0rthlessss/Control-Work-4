#pragma once

#include "Information.h"
#include "CryptingProcess.h"

char SaveResults(string msg);

void OpenFile(int option, fstream& file);

string FileInput(fstream& fin);

string ConsoleInput(string msg);