#include "calc.h"

// This file contains generic functions that ive used multiple times for differing purposes

// This prints a help message from a help.txt file
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

// Our quit message
void quit(void) {
	printf("Goodbye!\n");
}

// Our error message
void error(void) {
	printf("Error: Illegal input!\n");
}

// Prints a 2D infix/postfix expression (for testing)
void print2D(char * p_expression, int expression_length) {
	
	int element_length = 16;
	
	// Print 2d function
	printf("|||||||||||||||||||\n");
	
	for (int i = 0; i < expression_length; i++) {
		
		printf("%p\t%s\n", p_expression + i*element_length, p_expression + i*element_length);
	}
	
	printf("|||||||||||||||||||\n");
}

// Converts any 'e's in an input to *10^  note: not used in the final build
int convertScientific(char * user_input) {
	
	// Point to the first element of the string
	char * p_input = user_input;
	
	// Copy user input to another string
	char * copy;
	copy = malloc(100*sizeof(char));
	
	char * p_copy = copy;
	
	// Copy the result
	while (*p_input) {
		*p_copy = *p_input;
		
		p_input++;
		p_copy++;
	}
	
	//printf("usr input: %s\n", user_input);
	//printf("copy: %s\n", copy);
	
	// Write back to first element
	p_copy = copy;
	p_input = user_input;
	
	// The characters we will insert
	char scientific[] = "*10^";
	
	// Go through the copy
	while (*p_copy) {
		
		// If we find the character
		if (*p_copy == 'e') {
			
			// Write in the characters we will insert
			for (int i = 0; i < strlen(scientific); i++) {
				*p_input = scientific[i];
				p_input++;
			}
			
			p_copy++;
		}
		// Otherwise copy the values
		else {
			
			*p_input = *p_copy;
			p_input++;
			p_copy++;
		}
	}

	//printf("usr input: %s\n", user_input);
	//printf("copy: %s\n", copy);
	
	return 0;
}

// This takes an element of either expression and returns 1 for an opertor and 0 if not
int isOperator(char * input) {
	
	if (strlen(input) == 1 && isCharInString("+-*/^()", *input)) {
		return 1;
	}
	else 
		return 0;
}

// This is our push function which takes an element of our infix and pushes
int push(char * string, char * stack) {
	
	//printf("expression in push: %s\n", string);
	
	// The character is the first element of the string
	char character = *string;  
	
	// If the stack is empty
	if (*stack == '\0') {
		
		// Add the character to the stack
		*stack = *string;
		return 0;
	}
	
	// Find the top of the stack
	while (*stack) {

		stack ++;
	}
	
	// Write the character to the top of the stack
	*(stack) = character;
	
	return 0;
}

// This returns an integer based on the precedence of the operator
int precedence(char character) {
	
	char symbol = character;
	
	if (symbol == '^') {
		return 3;
	}
	else if (symbol == '*' || symbol == '/') {
		return 2;
	}
	else if (symbol == '+' || symbol == '-') {
		return 1;
	}
	else {
		return 0;
	}
}

// This looks at the top of the stack without removing it
char peek(char * stack) {
	
	// If the stack is empty return the null value
	if (*stack == '\0') {
		return *stack;
	}
	
	// Otherwise go through the stack till we hit a null
	while (*stack) {
		
		stack++;
	}
	// Print the value before this null
	stack--;
	return *stack;
	
}

// This removes the top of a stack and returns its value
char pop(char * stack) {
	
	// If the stack is empty return the null value
	if (*stack == '\0') {
		return *stack;
	}
	
	// Go to last element
	while (*stack) {
		stack++;
	}
	
	// return to the last element
	stack--;
	
	// Take the top off the stack and return it
	char temp = *stack;
	*stack = '\0';
	return temp;
}

// Returns 1 if the character is present
int isCharInString (char * string, char character) {
	
	// If character is a null
	if (character == '\0') {
		return 0;
	}
	
	// Boolean to check whether the character is present
	int isPresent = 0;
	
	// Go through the string until '\0'
	while (*string) {
		
		// If the characters are equal the character is evidently present
		if (character == *string) {
			
			isPresent = 1;
		}
		
		string++;
	}
	
	// Return the boolean value
	return isPresent;
}