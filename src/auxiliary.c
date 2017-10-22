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

void print2D(char * p_expression, int expression_length) {
	
	int element_length = 16;
	
	// Print 2d function
	printf("|||||||||||||||||||\n");
	
	for (int i = 0; i < expression_length; i++) {
		
		printf("%p\t%s\n", p_expression + i*element_length, p_expression + i*element_length);
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

int convertScientific(char * user_input) {
	
	char * p_input = user_input;
	
	// Copy user input to another string
	char * copy;
	copy = malloc(100*sizeof(char));
	
	char * p_copy = copy;
	while (*p_input) {
		*p_copy = *p_input;
		
		p_input++;
		p_copy++;
	}
	
	//printf("usr input: %s\n", user_input);
	//printf("copy: %s\n", copy);
	
	p_copy = copy;
	p_input = user_input;
	
	char scientific[] = "*10^";
	while (*p_copy) {
		
		if (*p_copy == 'e') {
			
			for (int i = 0; i < strlen(scientific); i++) {
				*p_input = scientific[i];
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

	//printf("usr input: %s\n", user_input);
	//printf("copy: %s\n", copy);
	
	return 0;
}

int isOperator(char * input) {
	
	if (strlen(input) == 1 && isCharInString("+-*/^()", *input)) {
		return 1;
	}
	else 
		return 0;
}

int push(char * string, char * stack) {
	
	//printf("expression in push: %s\n", string);
	char character = *string;
	
	// If the stack is empty
	if (*stack == '\0') {
		//printf("empty\n");
		// Add the character to the stack
		*stack = *string;
		return 0;
	}
	
	while (*stack) {
		//printf("in loop\n");
		stack ++;
	}
	*(stack) = character;
	return 0;
}

int precedence(char character) {
	
	char symbol = character;
	/*
	if (symbol == '(') {
		return 4;		
	}
	*/
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

char pop(char * stack) {
	
	// If the stack is empty return the null value
	if (*stack == '\0') {
		return *stack;
	}
	
	// Go to last element
	while (*stack) {
		stack++;
	}
	stack--;
	char temp = *stack;
	*stack = '\0';
	return temp;
}