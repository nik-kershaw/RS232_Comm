#include <windows.h>
#include "sound.h"
#include "main.h"
#include "node.h"
#include "RS232Comm_Send.h"
#include "RS232Comm_Receive.h"

#define ID_BTN 1000
#define ID_BTN2 1003
#define ID_SBM
#define Btx 60
#define Bty 40
#define seperation (width1 + 20)
#define Btx2 (Btx + seperation)
#define width1 150
#define height1 25

int  btn;

LRESULT CALLBACK buttons(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
HWND CreateButton(int id, char* name, int x, int y, int width, int height, HWND parent, DWORD Text, void(*pressed)(HWND), void(*unpressed)(HWND));
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void Addmenus(HWND);

HMENU hMenu;
HWND Record;
HWND Play;
HWND Save;
HWND PlayAll;
HWND sending;
HWND recieve;
HWND PlayAllt;
HWND PlayAllpri;
HWND dequeue;
HWND dequeue1;
HWND count;


struct ButtonSettings 
{
	int height = height1;
	int width = width1;
} button;

void function(void);
void function2(void);