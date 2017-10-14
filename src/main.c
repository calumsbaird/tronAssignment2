#include "calc.h"

int main (void) {
	
	// Start up
	printf("Simple Calculator\n");
	
	// Infinite loop
	while (1) {
		
		// Waiting prompt
		printf(">>> ");
		
		// Take input
		char * user_input = malloc(100*sizeof(char));
		fgets(user_input, BUF_SIZE, stdin);
		
		// Simplify user input
		simplifyInput(user_input);
		
		// If single character input
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
			}
		}
		
		//printf("%s\n", user_input);
		// Check the input
		if (checkInput(user_input) == 1) {
			error();
			free(user_input); // Unallocate memory for next pass
			continue;
		}
		
		// Parse the string to calc.c to be processed
		calc(user_input);
		
		//printf("user input: %s\n", user_input);
		
		free(user_input);
	}
	
	return 0;
}

