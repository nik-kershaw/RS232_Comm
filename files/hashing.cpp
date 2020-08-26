/* Implements a hash function for strings.
* Pseudo-random numbers(a and b)are used for the
* multipliers, which is even more effective at
* creating random hashes.
*/

#include "Hashing.h"

int hashU(char *v, int M) {
	unsigned int h, a = 31415, b = 27183;
	for (h = 0; *v != '\0'; v++, a = (a*b) % (M - 1))
		h = (h*a + *v) % M;
	return(h);
}