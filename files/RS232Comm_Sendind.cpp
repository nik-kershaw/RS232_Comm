#include <Windows.h>								// Includes the functions for serial communication via RS232
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "main.h"
#include "RS232Comm_Send.h"




#define EX_FATAL 1
#define BUFSIZE 140									// Size of buffer
#define COMPORT "\\\\.\\COM10"						// COM port used for transmit / receive - If COM# is larger than 9 then use the following syntax--> "\\\\.\\COM10"
#define NUMb 3

extern bool text = false;							// TRUE If it is a text message
extern bool voteon;

// Buffer variables
extern short iBigBuf[];								// buffer
extern long  lBigBufSize;
extern bool compres;

// Ensure that default character set is not Unicode
// Communication variables and parameters
HANDLE hCom;										// Pointer to a COM port
int nComRate = 19200;								// Baud (Bit) rate in bits/second 
int nComBits = 8;									// Number of bits per frame
COMMTIMEOUTS timeout;								// A commtimout struct variable

// The client - A testing main that calls the functions below
int Send() {

	int priority[1];
	int voteons[5];
	int result[1];
	// Compression variables
	int outsize = 0;
	unsigned char *OutputBuff = (unsigned char*)calloc(lBigBufSize, sizeof(short));

	char selection;

	initPort();										// Initialize the port

	printf("Do you want to send a text or sound?");
	printf("\n\n\t 1 - Text");
	printf("\n\t 2 - Audio");
	printf("\n\nSelection: ");
	selection = getche();

	if (selection - '0' == 1)
	{
		sendtxt();
	}

	else
	{
		printf("\nwhat the priority? ");
		scanf("%d", &priority[0]);

		if (compres == true)
		{printf("\n\nCompressing your file...");

			outsize = Huffman_Compress((unsigned char*)iBigBuf, OutputBuff,2*lBigBufSize);

			printf("\n\nSending File now...");

			outputToPort(OutputBuff, outsize);

			short error[NUMb];

			for (int i = 0; i < NUMb; i++)
			{
				error[i] = iBigBuf[i];
			}

			result[0] = hashU((char*)error,HASHNUM);

			Sleep(1000);
			outputToPort((char*)result, sizeof(int));		
		}

		else
		{
			outputToPort((char*)iBigBuf, lBigBufSize * 2);

		}
		if (voteon == true)
		{
			for (int i = 0; i < 5; i++)
			{
				voteons[i] = priority[0];
			}
			Sleep(2000);
			outputToPort((char*)voteons, sizeof(int)*4);
		}
		else{
			Sleep(1000);
			outputToPort((char*)priority, sizeof(int));
		}
			purgePort();									// Purge the port
			CloseHandle(hCom);								// Closes the handle pointing to the COM port
			
			system("pause");
	}
	
	system("CLS");

	return 1;	
}

// Sent a text message instead of audio
void sendtxt()
{

	char msgOut[BUFSIZE];							// Sent message
	int loop[1];

	printf("\n\nHow many messages you want to send?: ");
	loop[0] = getche();

	loop[0] = loop[0] - '0';



	for (int i = 0; i < loop[0]; i++)
	{
		flushall();
		printf("\n\nType message: ");
		fgets(msgOut, BUFSIZE, stdin);
		flushall();

		node* pnode = (link)malloc(sizeof(Node)); //adding the gatthered info into a node srtructure for adding into the queue

		memcpy(pnode->Data.txt, msgOut, BUFSIZE);

		pnode->Data.BufSize = strlen(msgOut) + 1;

		AddToQueue(pnode);
	
	}

	node* pHead = gibhead();

	outputToPort((char*)loop, sizeof(int));
	Sleep(5000);

	for (int i = 0; i < loop[0]; i++)
	{

		outputToPort(pHead->Data.txt, pHead->Data.BufSize);		// Send string to port - include space for '\0' termination

		Sleep(5000);

		pHead = pHead->Pnext;

	

	}

	purgePort();									// Purge the port
	CloseHandle(hCom);								// Closes the handle pointing to the COM port


	printf("\n");
	system("pause");
}




// Initializes the port and sets the communication parameters
void initPort() {

	createPortFile();								// Initializes hCom to point to PORT5 (port 5 is used by USB-Serial adapter on my laptop)
	purgePort();									// Purges the COM port
	SetComParms();									// Uses the DCB structure to set up the COM port
	purgePort(); 
}

// Purge any outstanding requests on the serial port (initialize)
void purgePort() {
	PurgeComm(hCom, PURGE_RXABORT | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_TXCLEAR);
}

// Output message to port (COM4)
void outputToPort(LPCVOID buf, DWORD szBuf) {

	int i=0;
	DWORD NumberofBytesTransmitted;
	LPDWORD lpErrors=0;
	LPCOMSTAT lpStat=0; 

	i = WriteFile(
		hCom,										// Write handle pointing to COM port
		buf,										// Buffer size
		szBuf,										// Size of buffer
		&NumberofBytesTransmitted,					// Written number of bytes
		NULL
	);

	// Handle the timeout error
	if (i == 0) {
		printf("\nWrite Error: 0x%x\n", GetLastError());
		ClearCommError(hCom, lpErrors, lpStat);		// Clears the device error flag to enable additional input and output operations. Retrieves information ofthe communications error.	
	}
	else
		printf("\nSuccessful transmission, there were %ld bytes transmitted\n", NumberofBytesTransmitted);
}


// Sub functions called by above functions
/**************************************************************************************/

// Set the hCom HANDLE to point to a COM port, initialize for reading and writing, open the port and set securities
void createPortFile() {

	// Call the CreateFile() function 
	hCom = CreateFile(
		COMPORT,									// COM port number  --> If COM# is larger than 9 then use the following syntax--> "\\\\.\\COM10"
		GENERIC_READ | GENERIC_WRITE,				// Open for read and write
		NULL,										// No sharing allowed
		NULL,										// No security
		OPEN_EXISTING,								// Opens the existing com port
		FILE_ATTRIBUTE_NORMAL,						// Do not set any file attributes --> Use synchronous operation
		NULL										// No template
	);

	if (hCom == INVALID_HANDLE_VALUE) {
		printf("\nFatal Error 0x%x: Unable to open\n", GetLastError());
	}
	else {
		printf("\nCOM is now open\n");
	}
}

static int SetComParms() {
	DCB dcb;										// Windows device control block

	// Clear DCB to start out clean, then get current settings
	memset(&dcb, 0, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);
	if (!GetCommState(hCom, &dcb))
		return(0);

	// Set our own parameters from Globals
	dcb.BaudRate = nComRate;						// Baud (bit) rate
	dcb.ByteSize = (BYTE)nComBits;					// Number of bits(8)
	dcb.Parity = 0;									// No parity	
	dcb.StopBits = ONESTOPBIT;						// One stop bit
	if (!SetCommState(hCom, &dcb))
		return(0);

	// Set communication timeouts (SEE COMMTIMEOUTS structure in MSDN) - want a fairly long timeout
	memset((void *)&timeout, 0, sizeof(timeout));
	timeout.ReadIntervalTimeout = 10;				// Maximum time allowed to elapse before arival of next byte in milliseconds. If the interval between the arrival of any two bytes exceeds this amount, the ReadFile operation is completed and buffered data is returned
	timeout.ReadTotalTimeoutMultiplier = 1;			// The multiplier used to calculate the total time-out period for read operations in milliseconds. For each read operation this value is multiplied by the requested number of bytes to be read
	timeout.ReadTotalTimeoutConstant = 1000;		// A constant added to the calculation of the total time-out period. This constant is added to the resulting product of the ReadTotalTimeoutMultiplier and the number of bytes (above).
	SetCommTimeouts(hCom, &timeout);
	return(1);
}
