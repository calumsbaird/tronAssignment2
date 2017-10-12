#include "calc.h"

// Testing harness, ensure no spaces are entered in your input
int main(void) {
	
	// Check input
	//checkInput("asd");
	assert(checkInput("1+1 ") == 1);
	
	
	
	printf("All tests passed!\n");
	return 0;
}