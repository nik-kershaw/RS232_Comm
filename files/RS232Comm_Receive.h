#pragma once
#include "Hashing.h"
// Prototype the functions to be used

int Receive();
void initPortR(); 
void purgePortR();
void gettext(void);
void audio(void);

int inputFromPortR(LPVOID buf, DWORD szBuf);
void receivetxt();
void getaudio();

// Sub functions
void createPortFileR();
static int SetComParmsR();

#define HASHNUM 29