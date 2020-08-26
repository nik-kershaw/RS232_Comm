/*
	Main.c 
	
	Control the huffman compression and display string, size of the string plus
	compressed version of it

*/

#include "main.h";

#include <stdio.h>
#include <stdlib.h>


void compression(void)
{

	unsigned char *InputBuff;

	int size_input = 0;

	int outsize = 0;

	// Get file information
	InputBuff = 

	// get File size
	size_input = 

	printf("\nIts size is: %d bytes", size_input);
	printf("\n\nThis is your file: %s", InputBuff);

	printf("\n\n");
	system("pause");
	system("cls");

	// Create output buffer
	unsigned char *OutputBuff = (unsigned char*)calloc(size_input, sizeof(unsigned char));

	// Compression function will return compressed file size
	outsize = Huffman_Compress(InputBuff, OutputBuff, size_input);

	printf("\nYour compressed file info: ");
	printf("\n\nSize of compresed file: %d bytes", outsize);
	printf("\nDifference: %d", size_input - outsize);
	printf("\nCompression factor: %0.2f", ((float)size_input/(float)outsize));


	printf("\n\n");
	system("pause");
	system("cls");


	// Create output buffer
	unsigned char *uncompressed = (unsigned char*)calloc(size_input, sizeof(unsigned char));

	// Uncompress file to original state
	Huffman_Uncompress(OutputBuff, uncompressed, outsize, size_input);

	WCompress(fptr, uncompressed);

	printf("\nNow lets uncompress.");
	printf("\n\nYour uncompressed file: %s", uncompressed); 


	printf("\n\n");
	system("pause");
	system("cls");

}

