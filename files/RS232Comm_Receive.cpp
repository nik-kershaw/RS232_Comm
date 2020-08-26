#include <Windows.h>								// Includes the functions for serial communication via RS232
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "RS232Comm_Receive.h"
#include "Queue"
#include "main.h"
#include "VoteOn.h"

#define EX_FATAL 1
#define BUFSIZE 140										// Size of buffer for text
#define BUFAUDIO 96000
#define COMPORT "\\\\.\\COM11"							// COM port used for transmit / receive - If COM# is larger than 9 then use the following syntax--> "\\\\.\\COM10"
#define NUMb 3

extern bool voteon;

// Ensure that default character set is not Unicode
// Communication variables and parameters

HANDLE hComR;										// Pointer to a COM port
int nComRateR = 19200;								// Baud (Bit) rate in bits/second 
int nComBitsR = 8;									// Number of bits per frame
COMMTIMEOUTS timeoutR;								// A commtimout struct variable


extern bool text;
extern bool compres;

// Buffer variable
extern short iBigBuf[];								// buffer
extern long  lBigBufSize;

static DWORD NumberofBytesRead;

int Receive()
{
	char selection;					

	initPortR();									// Initialize the port

	printf("\nAre you receiving audio or text message?");
	printf("\n\n\t 1 - Text");
	printf("\n\t 2 - Audio");
	printf("\n\nSelection: ");
	selection = getche();

	if (selection - '0' == 1)
	{
		gettext();
	}
	else
	{
		audio();
	}
	return 1;
}

void receivetxt()
{
	int NumberofBytesRead = 0;
	char msgIn[BUFSIZE];	// Received message
	int msgsent [1];
	int success = 0;

		inputFromPortR((int*)msgsent, sizeof(int));

		Sleep(5000);

		for (int i = 0; i < msgsent[0]; i++)
{

	success = inputFromPortR(msgIn, BUFSIZE);	// Receive string from port

		if (success == 1){
		node* pnode = (link)malloc(sizeof(Node)); //adding the gatthered info into a node srtructure for adding into the queue

		memcpy(pnode->Data.txt, msgIn, strlen(msgIn) + 1);

		pnode->Data.BufSize = strlen(msgIn) + 1;

		AddToQueue(pnode);

		Sleep(5000);
		}
}

	printf("\n\n");
	system("pause");

//printing all of the messages	
	printf("\n\nYou got mail: \n");

	printf("\n\nHere are your messages: ");

	playbackAllt(gibhead());

	printf("\n\n");
	system("pause");
	system("cls");

}

// Initializes the port and sets the communication parameters
void initPortR() {
	createPortFileR();								// Initializes hCom to point to PORT5 (port 5 is used by USB-Serial adapter on my laptop)
	purgePortR();									// Purges the COM port
	SetComParmsR();									// Uses the DCB structure to set up the COM port
	purgePortR();
}

// Purge any outstanding requests on the serial port (initialize)
void purgePortR() {
	PurgeComm(hComR, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);
}




int inputFromPortR(LPVOID buf, DWORD szBuf) {

	int i = 0;
	
	LPDWORD lpErrors = 0;
	LPCOMSTAT lpStat = 0;

	i = ReadFile(
		hComR,										// Read handle pointing to COM port
		buf,										// Buffer size
		szBuf,  									// Size of buffer - Maximum number of bytes to read
		&NumberofBytesRead,
		NULL
		);

	// Handle the timeout error
	if (i == 0) {
		printf("\nRead Error: 0x%x\n", GetLastError());
		ClearCommError(hComR, lpErrors, lpStat);		// Clears the device error flag to enable additional input and output operations. Retrieves information ofthe communications error.
		return 0; // error - comm timeout
	}
	else if (NumberofBytesRead != 0) {
		printf("\nSuccessful reception!, There were %ld bytes read\n", NumberofBytesRead);
		return 1;	// success
	}
	else {
		printf("\nUnsucessful reception!, No bytes were read\n");
		return 0;	// error - no bytes received
	}
}



// Sub functions called by above functions
/**************************************************************************************/

// Set the hCom HANDLE to point to a COM port, initialize for reading and writing, open the port and set securities
void createPortFileR() {

	// Call the CreateFile() function 
	hComR = CreateFile(
		COMPORT,									// COM port number  --> If COM# is larger than 9 then use the following syntax--> "\\\\.\\COM10"
		GENERIC_READ | GENERIC_WRITE,				// Open for read and write
		NULL,										// No sharing allowed
		NULL,										// No security
		OPEN_EXISTING,								// Opens the existing com port
		FILE_ATTRIBUTE_NORMAL,						// Do not set any file attributes --> Use synchronous operation
		NULL										// No template
		);

	if (hComR == INVALID_HANDLE_VALUE) {
		printf("\nFatal Error 0x%x: Unable to open\n", GetLastError());
	}
	else {
		printf("\nCOM is now open\n");
	}
}

static int SetComParmsR() {
	DCB dcb;										// Windows device control block
	// Clear DCB to start out clean, then get current settings
	memset(&dcb, 0, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);
	if (!GetCommState(hComR, &dcb))
		return(0);

	// Set our own parameters from Globals
	dcb.BaudRate = nComRateR;						// Baud (bit) rate
	dcb.ByteSize = (BYTE)nComBitsR;					// Number of bits(8)
	dcb.Parity = 0;									// No parity	
	dcb.StopBits = ONESTOPBIT;						// One stop bit
	if (!SetCommState(hComR, &dcb))
		return(0);

	// Set communication timeouts (SEE COMMTIMEOUTS structure in MSDN) - want a fairly long timeout
	memset((void *)&timeoutR, 0, sizeof(timeoutR));
	timeoutR.ReadIntervalTimeout = 500;				// Maximum time allowed to elapse before arival of next byte in milliseconds. If the interval between the arrival of any two bytes exceeds this amount, the ReadFile operation is completed and buffered data is returned
	timeoutR.ReadTotalTimeoutMultiplier = 10;		// The multiplier used to calculate the total time-out period for read operations in milliseconds. For each read operation this value is multiplied by the requested number of bytes to be read
	timeoutR.ReadTotalTimeoutConstant = 1000;		// A constant added to the calculation of the total time-out period. This constant is added to the resulting product of the ReadTotalTimeoutMultiplier and the number of bytes (above).
	SetCommTimeouts(hComR, &timeoutR);
	return(1);
}

void audio(void)
{
	struct TestStruct {
		int i;
		int	j;
		int	k;
		int	l;
		int m;
	};

	char key;
	char msgIn[BUFSIZE];							// Received message
	int msgsent[1];
	int result;
	int msgpri[1];
	int voteons[5];

	//this is the grabbing of audio
	printf("\n\nPress any key to receive your message: ");
	key = getche();
	printf("\n\n");


	int success = inputFromPortR((char*)iBigBuf, lBigBufSize * 2);	// Receive audio from port

	if (success == 1)
	{
		if (compres == true)
		{
			unsigned char *uncompress = (unsigned char*)malloc(lBigBufSize * 2);		// Create output buffer

			Huffman_Uncompress((unsigned char*)iBigBuf, uncompress, (int)NumberofBytesRead, 2 * lBigBufSize);	// Uncompress received audio

			memcpy(iBigBuf, (short*)uncompress, 2 * lBigBufSize);
			//iBigBuf = uncompress;	// Save outputbuffer to iBigBuf


			short error[NUMb];

			for (int i = 0; i < NUMb; i++)
				error[i] = iBigBuf[i];

			result = hashU((char*)error, HASHNUM);

			inputFromPortR((int*)msgsent, sizeof(int));

			if (msgsent[0] == result)
			{
				printf("\nno error in messasge\n");


				playback();
			}
			else
			{
				printf("error in message being sent, playback will not be done");
				lBigBufSize = NULL;
			}

		}
		else
			playback();

		//putting buffer info into queue
			node* pnode = (link)malloc(sizeof(Node)); //adding the gatthered info into a node srtructure for adding into the queue

			pnode->Data.Buf = (short*)malloc(lBigBufSize * 2);//mallocing the buffer / creating the space for data

			pnode->Data.BufSize = lBigBufSize; //setting the size value

			memcpy(pnode->Data.Buf, iBigBuf, lBigBufSize * 2);

			

		//now setting priority
		Sleep(1000);
		

		if (voteon == true)
		{
			inputFromPortR((int*)voteons, sizeof(int)*4);
			result = VoteOn(voteons, 3, sizeof(int)*5);
			pnode->Data.priority = result;
			printf("priority after voting is: %d\n", pnode->Data.priority);
		}
		else{
		inputFromPortR((int*)msgpri, sizeof(int));
		pnode->Data.priority = msgpri[0];
		}


		AddToQueue(pnode);

	}

	else
	{
		printf("\nMessage not received due to error\n");	// Indicate error in reception
	}

	purgePortR();									// Purge the port
	CloseHandle(hComR);								// Closes the handle pointing to the COM port

	system("pause");
	system("CLS");

	return;
}

void gettext(void)
{
	char key;
	char msgIn[BUFSIZE];							// Received message

	printf("\n\nPress any key to receive your message: ");
	key = getche();
	printf("\n\n");

		receivetxt();

		purgePortR();									// Purge the port
		CloseHandle(hComR);								// Closes the handle pointing to the COM port

		return;
}

