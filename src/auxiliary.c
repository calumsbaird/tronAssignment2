#include "calc.h"

void help(void)
{
	// Define a integer to store the ASCII of a character
	int character;
	
	// Assign file a pointer
	FILE *fpointer;
	
	// Opens the help file assigning it to a pointer, (read only)
	fpointer = fopen("src/help.txt", "r");
	
	// Go through the file character by character until the end of file (EOF) character
	while ((character = getc(fpointer)) != EOF) {
		// Print the character
        printf("%c",character);
	}
	
	// Close the file
	fclose(fpointer);
}

void quit(void) {
	printf("Goodbye!\n");
}

void error(void) {
	printf("Error: Illegal input!\n");
}

void print2D(char ** row, int expression_length) {
	printf("|||||||||||||||||||\n");
	
	for (int i = 0; i < expression_length; i++) {
		
		printf("%p\t%s\n", row + i, row[i]);
	}
	
	printf("|||||||||||||||||||\n");
}

void free2D(char ** expression, int expression_length) {
	
	for (int i = 0; i < expression_length; i++) {
		
		//printf("pointer: %p\n", *(expression));
		//printf("pointer: %p\n", *(expression+1));
		free(expression[i]);
	
	}
}

void allocate2D(char ** expression, int expression_length) {
	
	for (int i = 0; i < expression_length; i++) {
		
		//printf("pointer: %p\n", *(expression));
		//printf("pointer: %p\n", *(expression+1));
		*(expression+i) = malloc(sizeof(char) * expression_length);
	}
}

int isOperator(char * input) {
	if (strlen(input) == 1 && isCharInString("+-*/^()", *input)) {
		return 1;
	}
	else 
		return 0;
}