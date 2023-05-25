#pragma once

#include "Cyphers.h"
#include "OutputController.h"

void EncryptMessage(shared_ptr<Crypt> tmp);

void Encrypting(string msg);

bool CheckMsg(string msg);

void Decrypting(string msg);