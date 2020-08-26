#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <direct.h>
#include <malloc.h>
#include <time.h>




#define bufCHAR 140

//the data structure for the quote and ending length
struct MsgStruct
{
	long  BufSize;
	short* Buf;
	char txt[bufCHAR];
	int priority;
};

typedef struct node* link; // link is a pointer to a node

//node structure
typedef struct node Node;

struct node {
	link Pnext;
	link nextpri;
	struct MsgStruct Data;
}; 

//prototypes
void InitQueue(void);
int IsQueueEmpty(void);
void AddToQueue(Node *);
void DeQueue(Node *);
Node* gibhead(void);
int insert(node* cnode, node* ncheck);
Node* gibheadpri(void);
void setpri(Node* n, Node* set);
void countQueue(Node* head);
void DeQueue1(Node *);


