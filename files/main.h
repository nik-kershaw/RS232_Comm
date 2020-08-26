// Libraries
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include"sound.h"
#include "node.h"
#include "huffman.h"

//prototypes
int playback(void);
int recording(void);
void playbackfile(HWND hWnd);
int save(void);
int playbackAll(Node* head);
int playbackAllt(Node* head);
void compression(void);
int playbackAllpri(Node* head);