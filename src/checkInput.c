#include "calc.h"

int checkInput (char * input_string) {
	
	// Go through the input
	while (*input_string) {
		//printf("%c|", *input_string);
		
		// Check for invalid characters
		char * validChar = "0123456789.-+/e^()";
		if (isCharInString(validChar, *input_string) == 0) {
			
			// Return error state if invalid
			//error();
			return 1;
		}
		
		
		// Check for two sequential operators (and whether scientific notation 'e' is use before or after an invalid operator)
		char * initial_operators = "+-*/e";		
		// Go through operators
		while (*initial_operators){
		//do { 
			
			//printf("%c", *initial_operators);
			if (*input_string == *initial_operators) {
				
				// Check the next operator
				//printf("cehcking next operator\n");
				char * secondary_invalid_operators = "+*/e"; // note that two operators in a row is valid if the second is a '-' (indicating negative)
				if (isCharInString(secondary_invalid_operators, *(input_string+1)) == 1) {
					return 1;
				}
			}
			initial_operators++;
		}
		
		// Check that there is a number before and after the scientific notation 'e'
		if (*input_string == 'e') {

			char * valid_after = "-0123456789"; // '-' is valid after eg. 10e-5
			char * valid_before = " 0123456789"; // ' ' included to make strings same length

			//int is_valid_before = 0, is_valid_after = 0; // 'boolean' constants
			//printf("before and after e\n");	
			if (isCharInString(valid_before, *input_string) == 1) {
				return 1;
			}

			if (isCharInString(valid_after, *input_string) == 1) {
				return 1;
			}
		}
		
		// Check there isnt two sequential dp
		if (*input_string == '.') {
			if (*(input_string + 1) == '.') {
				return 1;
			}
		}
		
		// Check the last character isnt an operator
		// if the last character
		if (*(input_string + 1) == '\0') { 
			
			// If an operator
			char * operators = "+-/*";
			if (isCharInString (operators, *input_string)) {
				return 1; // Return an error
			}
		}
		input_string++;
	}
	return 0;	
}

int isCharInString (char * string, char character) {
	
	int isPresent = 0;
	//printf("character: %c\n", character);	
	
	// Go through the string until '\0'
	while (*string) {
		
		if (character == *string) {
			isPresent = 1;
		}
		//printf("string: %c\n", *string);
		string++;
	}
	//printf("isPresent: %d\n", isPresent);
	return isPresent;
}