#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <locale>
#include <algorithm>

namespace win {
	#include <Windows.h>
}

#define uc unsigned char

enum WorkWithFiles { input, output };
enum TopMenu { console = 1, file, module, quit };
enum BottomMenu { encrypt = 1, decrypt, back };
enum SubBottomMenu { caesar = 1, atbash, replace, backToBottom };
enum AlphabetBorders {cLower = 224, cUpper = 255, lLower = 97, lUpper = 122};

using namespace std;

void IgnoreLine();
int GetInt(string s);
string GetLine(string s);
string GetString(string s);
char GetChar(string s);