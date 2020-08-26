
#include "main.h"

void InitQueue(void)
{
	pHead = pTail = NULL;
}
// Returns non-zero iff queue is empty.
int IsQueueEmpty(void)
{
	return (pHead == NULL);
}

// Add Node (need to create) to the end of the queue
void AddToQueue(Node *pn)
{
	//setting the key of a node first before adding to the tree
	setkey(pn);

	if (pHead == NULL) {
		pHead = pn; //make first item ‘head’
		pHead->PLeft = NULL;
		pHead->PRight = NULL;
	}
	else 
	{
		pn->PLeft = NULL;
		pn->PRight = NULL;
		insert(pn, pHead); // make the last
	} 
	return;
} // item the ‘tail’


Node* gibhead()
{
	return(pHead);
}

void setkey(Node *pn)
{	
	//start of the quote
	int strt = 0;

	//setting the key to first letter of the quote
	pn->key = pn->Data.sentence[strt];

	//using this incase first char is a " or \n or SPACE key 
	while (pn->key == '\n' || pn->key == '"' || pn->key == ' ' || pn->key == '.')
	{
		strt++;
		pn->key = pn->Data.sentence[strt];
	};

	pn->key = tolower(pn->Data.sentence[strt]);

	return;
}

// count the number of nodes in a tree
int countnode(link h) {
	if (h == NULL) return(0);
	return(countnode(h->PLeft) + countnode(h->PRight) + 1);
}

// determine greatest height of tree
int height(link h) {
	int	iLeftH, iRightH;
	if (h == NULL) return(-1);
	iLeftH = height(h->PLeft);
	iRightH = height(h->PRight);
	if (iLeftH > iRightH)
		return(iLeftH + 1);
	else
		return(iRightH + 1);
}