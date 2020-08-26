
#include "node.h"

//tail and head for nodes
static Node *pHead, *pTail;
static Node *priHead, *priTail;

int counter;

void InitQueue(void)
{
	pHead = pTail = NULL;
	priHead = priTail = NULL;
}
// Returns non-zero iff queue is empty.
int IsQueueEmpty(void)
{
	return (pHead == NULL);
}

// Add Node (need to create) to the end of the queue
void AddToQueue(Node *pn)
{
	if (pHead == NULL) {
		pHead = pn; //make first item ‘head’
	}
	else {
		pTail->Pnext = pn;// make the last
	} //input point to the new item
	pn->Pnext = NULL;
	pn->nextpri = NULL;
	pTail = pn; // make this last input

	if (pn->Data.priority != 0)
	{
	//same thing but for priority
		if (priHead == NULL)
		{
			priHead = pn;
			priTail = pn;	
		}
		else if (pn->Data.priority >= priHead->Data.priority )
		{
			pn->nextpri = priHead;
			priHead = pn;
		}
		else if (pn->Data.priority <= priTail->Data.priority)
		{
			priTail->nextpri = pn;
			priTail = pn;
			pn->nextpri = NULL;
		}
		else
		{
			setpri(pn, priHead);
		}
	}
	else
	return;
} // item the ‘tail’


// Return item at the head
void DeQueue(Node *)
{
	Node *pTemp;
	if (pHead == NULL) return;//encase entered with no node

	pTemp = pHead;
	pHead = pHead->Pnext; // make next item new ‘head’
	free(pTemp);

	if (pHead != NULL)
		DeQueue(pTemp);	// returning till all messages cleared
	else
		return;
}

Node* gibhead()
{
	return(pHead);
}

Node* gibheadpri()
{
	return(priHead);
}
void setpri(Node* n,Node* set)
{
	if (n->Data.priority < set->Data.priority)
	{
		if (n->Data.priority > (set->nextpri)->Data.priority)
		{
			n->nextpri = set->nextpri;
			set->nextpri = n;
			return;
		}
		else
		setpri(n, set->nextpri);
	}
	else
		return;
}

void countQueue(Node* head)
{
	if (head != NULL)
	{
		counter++;
		countQueue(head->Pnext);
	}
	else
	{
		printf("\nthe amount of messages is: %d\n", counter);
		system("PAUSE");
		system("cls");
		return;
	}

}
void DeQueue1(Node *)
{
	Node *pTemp;
	if (pHead == NULL) return;//encase entered with no node

	pTemp = pHead;
	pHead = pHead->Pnext; // make next item new ‘head’
	free(pTemp);

	return;
}