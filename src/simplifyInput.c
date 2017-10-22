#include "calc.h"

// This file/function goes through and simplifies the input so we are processing the data more simply
void simplifyInput(char * user_input) {
	
	// Remove newline character from input
	char *pos;
	if ((pos = strchr(user_input, '\n')) != NULL)
	*pos = '\0';
	
	// Remove the spaces from the input
	removeChar(user_input, ' ');
	
	// if format 2(4) modify it to 2*(4)
	addStar(user_input);
	
	// Make input lowercase (to deal with E & e, H & h etc)
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
		
		// Copy the values
		*pout = *pin;
		
		// If the character is valid, move to the next "element" of the input
		if (*pout != garbage) {
			pout++;
		}
		// Otherwise pout wont be incremented and the garbage value will be overwritten
	}
	
	// Add a null character to the end for string format
	*pout = '\0';
}

void addStar(char * user_input) {	
	
	// Point to the first element of the input
	char * p_input = user_input;
	
	// Copy user input to another string
	char * copy;
	copy = malloc(100*sizeof(char));
	
	// Point to our copy string
	char * p_copy = copy;
	
	// Go through the input
	while (*p_input) {
		
		// Copy the value
		*p_copy = *p_input;
		
		p_input++;
		p_copy++;
	}
	
	// Add the null character to the end
	*p_copy = '\0';
	
	p_copy = copy;
	p_input = user_input;
	
	char insert[] = "*(";
	while (*p_copy) {
		
		if (*p_copy == '(' && isCharInString("+-/*^", *(p_copy - 1)) == 0 && *(p_copy - 1) != '\0') {
			//printf("adding *(\n");
			for (int i = 0; i < strlen(insert); i++) {
				*p_input = insert[i];
				p_input++;
			}
			//p_input	++;
			p_copy++;
		}
		else {
			*p_input = *p_copy;
			p_input++;
			p_copy++;
		}
	}
	
	//printf("usr input: |%s|\n", user_input);
	//printf("copy: |%s|\n", copy);
	free(copy);
	copy = NULL;
	
	//return 0;
}