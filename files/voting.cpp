#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "VoteOn.h"

//repeating for error and checking
int VoteOn( int Instances[], int nInstances, int nSize)
{
	//variables
	int cmp;
	int* counters = (int*)calloc(nInstances , sizeof(int));
	int result;

	//looping for how ever many instances
	for (int x = 0; x < nInstances; x++)
	{
		//looping for compairing instances
		for (int y = (x + 1); y < nInstances; y++)
		{
			//comparing the memory locations
			cmp = Instances[x]- Instances[y];

			//checking to see if they match to count
			if (cmp == 0)
			{
				counters[x] += 1;
			}
		}
	}


	result = Instances[highestcnt(counters, nInstances)];
	//returning the index of highest number
	return result;
}

int highestcnt(int array[], int nbr)
{
	//variables for checking highest
	int greatest = 0;

	//compairing all the way through the array
	for (int i = 1; i < nbr; i++)
	{
		//changing the greatest value if something is greater than previous number or 0
		if (array[i] > array[greatest])
		{
			//int error = array[i];
			greatest = i;
		}
	}

	//testing for all the same result (error)
	if (greatest == 0 && array[greatest] == 0)
		return -1;
	else
		//returning the final index of greatest number
		return greatest;
}
