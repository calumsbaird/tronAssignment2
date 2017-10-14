#include "calc.h"

void simplifyInput(char * user_input) {
	
	// Remove newline character from input
	char *pos;
	if ((pos=strchr(user_input, '\n')) != NULL)
	*pos = '\0';
	
	// Remove the spaces from the input
	removeChar(user_input, ' ');
	
	// Make input lowercase (to deal with E & e)
	do {
			*user_input = tolower(*user_input);
	}
	while (*user_input++);
}

void removeChar(char * string, char garbage) {
	
	// Pointers for our input and output strings
	char *pin, *pout;
	
	// Go through the string
	for (pin = pout = string; *pin != '\0'; pin++) {
		
		*pout = *pin;
		
		// If the character is valid, move to the next "element"
		if (*pout != garbage) {
			pout++;
		}
	}
	
	*pout = '\0';
}