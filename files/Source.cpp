#include "Gui.h"
#include <stdio.h>

extern int counter;
bool compres = true;
bool voteon = true;

void main(HINSTANCE hInst)
{
	InitQueue();


	WNDCLASSW wc = {0};

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowCLass";
	wc.lpfnWndProc = WindowProcedure;


	RegisterClassW(&wc);

	CreateWindowW(L"myWindowCLass", L"window",WS_OVERLAPPEDWINDOW|WS_VISIBLE, 0,0,500,500,NULL,NULL,NULL,NULL);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL))
{
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

	return;
}

LRESULT CALLBACK WindowProcedure( HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int used = 0;
	int* ptr = 0;
	int result = 0;
	switch (msg)
	{
	case WM_COMMAND:
		
		switch (wp)
		{
			case 1:
				//put function for recording here for set time
				compres = true;
				Addmenus(hWnd);//making the top menu ie file
				break;
			case 2:
				//put function for recording here for set time
				compres = false;
				Addmenus(hWnd);//making the top menu ie file
				break;
			case 3:
				//put function for recording here for set time
				voteon = true;
				Addmenus(hWnd);//making the top menu ie file
				break;
			case 4:
				//put function for recording here for set time
				voteon = false;
				Addmenus(hWnd);//making the top menu ie file
				break;
			case BN_CLICKED:
				if ((HWND)lp == PlayAll)
						playbackAll(gibhead());

				else if ((HWND)lp == Record){
						recording();			//using the recording to file 
						result = MessageBox(hWnd, "Do you want to save this file?", "file", MB_YESNO);
						if (result == 6)
							save();}
				else if ((HWND)lp == Play){
					playbackfile(hWnd);			//playing from the file
					}
				else if ((HWND)lp == Save)
					//put function for recording here for set time
					used = MessageBox(hWnd, "Are you sure you want to save?", "file", MB_YESNO);//creating beep on the file button press

				else if ((HWND)lp == sending)
					Send();

				else if ((HWND)lp == recieve)
					Receive();

				else if ((HWND)lp == PlayAllt)
				{
					printf("\nYour messages are: \n");
					playbackAllt(gibhead());
				}

				else if ((HWND)lp == PlayAllpri)
				{
					playbackAllpri(gibheadpri());
				}

				else if ((HWND)lp == count)
				{
					counter = 0;
					countQueue(gibhead());
				}
				else if ((HWND)lp == dequeue)
				{
					DeQueue(gibhead());
				}
				else if ((HWND)lp == dequeue1)
				{
					DeQueue1(gibhead());
				}
				break;
				
			
		}
	
		break;
	case WM_CREATE:
		Addmenus(hWnd);//making the top menu ie file
		Record = CreateWindow("button", "Record", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, Btx, Bty, button.width, button.height, hWnd, NULL, GetModuleHandle(NULL), NULL); //typecasting id btn switches it to a menu item that can then be used no matter previous value
		
		Play = CreateWindow("button", "Playback file", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, Btx, Bty + button.height, button.width, button.height, hWnd, NULL, GetModuleHandle(NULL), NULL);
		
		Save = CreateWindow("button", "Save", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, Btx, Bty + button.height * 2, button.width, button.height, hWnd, NULL, GetModuleHandle(NULL), NULL);
		
		PlayAll = CreateWindow("button", "Play All Audio", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, Btx2, Bty, button.width, button.height, hWnd, NULL, GetModuleHandle(NULL), NULL); //typecasting id btn switches it to a menu item that can then be used no matter previous value
		
		PlayAllt = CreateWindow("button", "Play All text", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, Btx2, Bty + button.height * 2, button.width, button.height, hWnd, NULL, GetModuleHandle(NULL), NULL);

		PlayAllpri = CreateWindow("button", "Play All messages recieved by priority", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, Btx+10, Bty + button.height * 4, button.width+150, button.height, hWnd, NULL, GetModuleHandle(NULL), NULL);

		dequeue = CreateWindow("button", "clear all messages", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, Btx, Bty + button.height * 6, button.width, button.height, hWnd, NULL, GetModuleHandle(NULL), NULL);
		count = CreateWindow("button", "count queue", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, Btx2, Bty + button.height * 6, button.width, button.height, hWnd, NULL, GetModuleHandle(NULL), NULL);
		dequeue1 = CreateWindow("button", "clear single message", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, Btx, Bty + button.height * 8, button.width, button.height, hWnd, NULL, GetModuleHandle(NULL), NULL);
		
		Play = CreateWindow("button", "Play", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, Btx2, Bty  + button.height , button.width, button.height, hWnd, NULL, GetModuleHandle(NULL), NULL);
		
		sending = CreateWindow("button", "Send", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, Btx, Bty + button.height * 3, button.width, button.height, hWnd, NULL, GetModuleHandle(NULL), NULL);
		recieve = CreateWindow("button", "recieve", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, Btx2, Bty + button.height * 3, button.width, button.height, hWnd, NULL, GetModuleHandle(NULL), NULL);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); //allowing user to quit
		break;
	default:
		return DefWindowProcW(hWnd,msg,wp,lp);
	}
}


void Addmenus(HWND hWnd)
{
	HMENU hsubmen = CreateMenu();
	HMENU links = CreatePopupMenu();
	HMENU hMenu = CreateMenu();//retruning a menu
	AppendMenu(hMenu, MF_POPUP, (UINT)hsubmen,"File");//adding an item to the menu
	AppendMenu(hsubmen, MF_STRING| MF_POPUP, (UINT)links, "Settings...");//adding an item to the menu

	if (compres == false)
	{
	AppendMenu(links, MF_UNCHECKED , 1, "compression");//adding an item to the menu
	}
	else
	{
	AppendMenu(links, MF_CHECKED, 2, "compression");//adding an item to the menu
	}
	if (voteon == false)
	{
		AppendMenu(links, MF_UNCHECKED, 3, "vote on");//adding an item to the menu
	}
	else
	{
		AppendMenu(links, MF_CHECKED, 4, "vote on");//adding an item to the menu
	}
	SetMenu(hWnd,hMenu);//adding menu to the window
}

void function()
{
	printf("the function call worked\n");
}
void function2()
{
	printf("the function call worked second\n");
}