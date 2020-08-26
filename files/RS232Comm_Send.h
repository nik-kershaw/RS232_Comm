#pragma once
#include "Hashing.h"
// Prototype the functions to be used

int Send();
void initPort(); 
void purgePort();
void outputToPort(LPCVOID buf, DWORD szBuf);
int inputFromPort(LPVOID buf, DWORD szBuf);

// Sub functions
void createPortFile();
static int SetComParms();
void sendtxt();

#define HASHNUM 29