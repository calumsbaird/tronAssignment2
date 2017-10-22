#include "calc.h"

// This function returns 1 for an error and 0 if the function is fine
int checkInput (char * input_string) {
	
	// Go through the input
	while (*input_string) {
		
		// Check for invalid characters
		char * validChar = "0123456789.-+*/e^()";
		if (isCharInString(validChar, *input_string) == 0) {
			
			// Return error
			return 1;
		}
		
		// Check for two sequential operators (and whether scientific notation 'e' is use before or after an invalid operator)
		char * initial_operators = "+-*/e";
		
		// Go through operators
		while (*initial_operators){
			
			// If an operator
			if (*input_string == *initial_operators) {
				
				// Check the next operator
				char * secondary_invalid_operators = "+*/e"; // note that two operators in a row is valid if the second is a '-' (indicating negative)
				if (isCharInString(secondary_invalid_operators, *(input_string+1)) == 1) {
					
					// Return error
					return 1;
				}
			}
			initial_operators++;
		}
		
		// Check that there is a number before and after the scientific notation 'e'
		if (*input_string == 'e') {

			char * valid_after = "-0123456789"; // '-' is valid after eg. 10e-5
			char * valid_before = " 0123456789"; // ' ' included to make strings same length

			// Check the characters before and after to see if they are valid
			if (isCharInString(valid_before, *(input_string-1)) == 0) {
				
				// Return error if not valid
				return 1;
			}
			if (isCharInString(valid_after, *(input_string+1)) == 0) {
				
				// Return error if not valid
				return 1;
			}
		}
		
		// Check there isnt two sequential dp
		if (*input_string == '.') {

			// Go through all the characters from that point
			int i = 1;
			while (*(input_string + i)) {
				
				// If we find an operator there isnt 2 sequential dps
				if (isCharInString("+-/*^()", *(input_string + i)) == 1) {
					
					break;
				}
				// Otherwise if we find a second dp first return an error
				else if (*(input_string + i) == '.') {
					
					return 1;
				}
				
				i ++;
			}
		}
		
		// Check the last character isnt an operator
		// If the last character
		if (*(input_string + 1) == '\0') { 
			
			// If an operator
			char * operators = "+-/*";
			if (isCharInString (operators, *input_string)) {
				
				return 1; // Return an error
			}
		}
		
		// Go to next element of the string
		input_string++;
	}
	return 0;	
}