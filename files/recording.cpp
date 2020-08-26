/*	Filename: main.cpp
Author: Michael Galle
Date: Nov 2017
Details: Testing mainline for Windows sound API
*/

#include "main.h"
#include "node.h"


extern short iBigBuf[];												// buffer
extern long  lBigBufSize;

// Prototypes

int	recording(void)
{																		// total number of samples
	short* iBigBufNew = (short*)malloc(lBigBufSize*sizeof(short));		// buffer used for reading recorded sound from file															// used to flush extra input

	int BuffSize = 0;													// Size of buffer for text instead of audio

	// initialize recording
	InitializeRecording();

	// start recording
	RecordBuffer(iBigBuf, lBigBufSize);
	CloseRecording();

	printf("\n");
	system("pause");
	
	playback();


	//Send();

	system("cls");
	return(0);
}

int playback(void) 
{
	InitializePlayback();

	// playback recording 
	printf("\nPlaying recording from buffer\n");
	PlayBuffer(iBigBuf, lBigBufSize);
	ClosePlayback();

	return 0;
}

void playbackfile(HWND hWnd)
{									
															
	FILE* f;
	InitializePlayback();

	// playback recording 
	printf("\nPlaying recording from file\n");

	char name[100];
	
	printf("Enter file name: ");
	scanf("%s", name);

	//this just makes it so user does not need to put the .dat ending
	char* ending = ".dat", fullname[140];
	int x = strlen(name);
	strncpy(fullname, name, x);
	fullname[x] = '\0';
	strcat(fullname, ending);
	strcat(fullname, name + x);
	printf("%s\n", fullname);

	fopen_s(&f, fullname, "rb");	//opening the file

	if (!f) {
		printf("unable to open %s\n", "recording.dat");
		return ;
	}
	
	
	fread(iBigBuf, sizeof(short), lBigBufSize, f);			 //putting file into the buffers

	
	
	fclose(f);//close file

	node* pnode = (link)malloc(sizeof(Node)); //adding the gatthered info into a node srtructure for adding into the queue
	
	pnode->Data.Buf = (short*)malloc(lBigBufSize * 2);//mallocing the buffer / creating the space for data
	
	pnode->Data.BufSize = lBigBufSize; //setting the size value
	
	memcpy(pnode->Data.Buf, iBigBuf, lBigBufSize * 2);

	pnode->Data.priority = 0;

	AddToQueue(pnode);

	PlayBuffer(iBigBuf, lBigBufSize); //playing the buffer
	ClosePlayback();//close the playback

	printf("played sound and added to queue");
	
	return;
}

int save(void)
{
	FILE* f;
	char name[140];
	char detect = '1';
	int move;

	printf("Enter your file name: ");
	scanf("%s", name);

	//this just makes it so user does not need to put the .dat ending
	char* ending = ".dat", fullname[140];
	int x = strlen(name);
	strncpy(fullname, name, x);
	fullname[x] = '\0';
	strcat(fullname, ending);
	strcat(fullname, name + x);
	printf("%s\n", fullname);

	/* Open input file */
	fopen_s(&f, fullname, "wb");
	if (!f) {
		printf("unable to open %s\n", "file");
		return 0;
	}
	printf("Writing to sound file ...\n");
	fwrite(iBigBuf, sizeof(short), lBigBufSize, f);
	fclose(f);

	printf("saved sound");
	return 0;
}


int playbackAll(Node* head)
{
	if (head == NULL)
	{
		printf("cant play nothing!");
		return 0;
	}

	short temps = *(head->Data.Buf);
	InitializePlayback();

	// playback recording 
	printf("\nPlaying recording...\n");
	PlayBuffer(head->Data.Buf, (head->Data.BufSize));
	ClosePlayback();

	if (head->Pnext != NULL)
		playbackAll(head->Pnext);
	else
		return 0;
}

int playbackAllt(Node* head)
{
	Node *ptemp;

	if (head == NULL)
	{
		printf("cant play nothing!");
		return 0;
	}

	// playback recording 
	printf("\n%s\n", &head->Data.txt);

	if (head->Pnext != NULL)
		playbackAllt(head->Pnext);
	else
		return 0;
}

int playbackAllpri(Node* head)
{
	if (head == NULL)
	{
		printf("cant play nothing!");
		return 0;
	}

	short temps = *(head->Data.Buf);
	InitializePlayback();

	// playback recording 
	printf("\nPlaying recording...\n");
	PlayBuffer(head->Data.Buf, (head->Data.BufSize));
	ClosePlayback();

	if (head->nextpri != NULL)
		playbackAllpri(head->nextpri);
	else
		return 0;
}

void counter(Node* head)
{

}