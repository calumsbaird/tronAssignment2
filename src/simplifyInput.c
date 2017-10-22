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

// This function adds the asterisk before opening brackets if no operator has been specified
void addStar(char * user_input) {	
	
	// Point to the first element of the input
	char * p_input = user_input;
	
	// Copy user input to another string
	char * copy;
	copy = malloc(100*sizeof(char));
	
	// Point to our copy string
	char * p_copy = copy;
	
	// Go through the input and copy it
	while (*p_input) {
		
		// Copy the value
		*p_copy = *p_input;
		
		p_input++;
		p_copy++;
	}
	
	// Add the null character to the end
	*p_copy = '\0';
	
	// Point back to the first elements
	p_copy = copy;
	p_input = user_input;
	
	// Characters to replace '(' with
	char insert[] = "*(";
	
	// Go through copy
	while (*p_copy) {
		
		// If there is an opening bracket and there is no operator before
		if (*p_copy == '(' && isCharInString("+-/*^", *(p_copy - 1)) == 0 && *(p_copy - 1) != '\0') {
			
			// Add the insert characters '*(' to the input
			for (int i = 0; i < strlen(insert); i++) {
				*p_input = insert[i];
				p_input++;
			}
			
			p_copy++;
		}
		// Otherwise we just want to copy the values
		else {
			*p_input = *p_copy;
			p_input++;
			p_copy++;
		}
	}
	
	//printf("usr input: |%s|\n", user_input);
	//printf("copy: |%s|\n", copy);
	
	// Free the copy memory and assign a null pointer so we dont use it later
	free(copy);
	copy = NULL;
	
}