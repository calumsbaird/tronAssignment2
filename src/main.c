#include "calc.h"

int main (void) {
	
	// Start up
	printf("Simple Calculator\n");
	
	// Infinite loop
	while (1) {
		
		// Waiting prompt
		printf(">>> ");
		
		// Take input
		char * user_input = malloc(1024*sizeof(char));
		fgets(user_input, BUF_SIZE, stdin);
		
		// Simplify user input
		simplifyInput(user_input);
		
		// If single character input user
		int length = strlen(user_input);
		
		if (length == 1) {
			
			// If user wants to quit
			if (*user_input == 'q') {
				
				quit();
				return 0;
			}		
			// If user wants help
			else if (*user_input == 'h') {
				
				help();
				
				// Free the memory for the next pass
				free(user_input);
				continue;
			}
		}
		
		// Check input
		if (checkInput(user_input) == 1) {
			
			// Print our error message
			error();
			
			// Free memory for next pass
			free(user_input);
			continue;
		}
		
		// No need to convert scientific as atof deals with scientific anywayzz
		// Convert from scientific notation e -> *10^
		//convertScientific(user_input);
		
		// Parse the string to calc.c to be processed and calculated
		calc(user_input);	
		
		// Free dat memz
		free(user_input);
	}
	
	return 0;
}

