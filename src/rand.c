// Implementation from the [C Standard](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf), section 7.22.2

#include "rand.h"

static unsigned long int next = 1;

int rand() {
	next = next * 1103515245 + 12345;
	return (unsigned int) (next / 65536) % 32768;
}

void srand(unsigned int seed) {
	next = seed;
}
