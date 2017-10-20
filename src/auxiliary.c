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

void allocate2D(char ** expression, int expression_length) {
	
	for (int i = 0; i < expression_length; i++) {
		
		
		//printf("pointer: %p\n", *(expression));
		//printf("pointer: %p\n", *(expression+1));
		*(expression+i) = (char*)malloc(sizeof(char) * expression_length);
	}
	
	
	/*
	char *x;  // Memory locations pointed to by x contain 'char'
	char **y; // Memory locations pointed to by y contain 'char*'

	x = (char*)malloc(sizeof(char) * 100);   // 100 'char'
	y = (char**)malloc(sizeof(char*) * 100); // 100 'char*'
	*/
	// below is incorrect:
	//y = (char**)malloc(sizeof(char) * 50 * 50);
	// 2500 'char' not 50 'char*' pointing to 50 'char'
	/*
	*expression = calloc(expression_length, sizeof(char));

	for (int ii = 0; ii < 50; ++ii) {
		// Note that each string is just an OFFSET into the memory block
		// You must be sensitive to this when using these 'strings'
		**expression = &*expression[ii * 50];
	}
	printf("memorys allocated\n");
	*/
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
	/*if (symbol == '\0') {
		return 5;
	}*/
	if (symbol == '(') {
		return 4;		
	}
	else if (symbol == '^') {
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