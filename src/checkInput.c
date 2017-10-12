#include "calc.h"

int checkInput (char * input_string) {
	
	
	
	// Go through the input
	while (*input_string++) {
		//printf("%c|", * (input_string + i));
		
		// Check for invalid characters
		char * validChar = "0123456789.-+/e^";
		if (isValidChar(validChar, *input_string) == 0) {
			// Return error state if invalid
			error();
			return 1;
		}
		
		
	}
	return 0;
}

int isValidChar (char * validChar, char character) {
	
	int isValid = 0;
		
	while (*validChar++) {
		if (character == *validChar) {
			isValid = 1;
		}
	}
	//printf("isValid: %d\n", isValid);
	return isValid;
}