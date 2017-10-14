#include "calc.h"

// Testing harness, ensure no spaces are entered in your input
int main(void) {
	
	// Check input
	//assert(strcmp(simplifyInput("1 +  E5 "),"1+e5"));
	assert(checkInput("1+1") == 0);
	assert(checkInput("1++1") == 1);
	assert(checkInput("1+e5") == 1);
	assert(checkInput("1+e") == 1);
	assert(checkInput("1+-5") == 0);
	assert(checkInput("1e-5") == 0);
	assert(checkInput("1e+5") == 1);
	assert(checkInput("1-e5") == 1);
	assert(checkInput("1..5") == 1);
	assert(checkInput("1+") == 1);
	
	
	printf("All tests passed!\n");
	return 0;
}