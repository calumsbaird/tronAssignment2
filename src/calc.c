#include "calc.h"

int calc(char * user_input) {
	
	// Create an array of pointers
	char ** infix_expression; 
	//char ** postfix_expression;
	int max_expression_length = 100;						// ONLY 10
	infix_expression =  malloc(max_expression_length*sizeof(char*));
	int expression_length;
	
	allocate2D(infix_expression, max_expression_length);
	
	// Create an infix expression and return the no of terms
	expression_length = createInfix(user_input, infix_expression);
	//infixToPostfix(infix_stack, postfix_stack);
	
	print2D(infix_expression, expression_length);
	//printStack(postfix_stack);
	
	// Free dat memory
	free2D(infix_expression, max_expression_length);
	free(infix_expression);
	//free(postfix_expression);
	
	return 0;
}

int createInfix(char * user_input, char ** infix_expression) {
	
	//char ** p_infix = infix_expression;
	// Variable to count the number of terms in expression
	int expression_length = 0;
	
	// Create a temporary string that we put onto the infix_expression
	int element_length = 16;
	char * string;
	string = malloc(element_length*sizeof(char));
	char * p_string = string;
	//printf("pointer to string: %p\n");

	printf("%s\n", user_input);
	
	
	
	// Go through the input until we reach a null char
	while (*user_input) {
		
		// Here we put the character onto a string and either put it on to the expression
		// Or we keep adding to the string, depending on wether it forms part of a number
		int should_push = 0;
		
		// Put the character onto the string
		*string = *user_input;
		printf("user iput: %c\n", *user_input);
		
		// POTENTIAL CAUSE OF ERROR
		//printf("|%s|\n", *(user_input-1));
		// If the first element and negative
		if ( (*user_input == '-') && (isCharInString("0123456789.", *(user_input+1)) == 1) && (*(user_input-1) == '\0') ) {
			should_push = 0;
		}
		// If the number is negative (as opposed to minus sign)
		else if (*(user_input) == '-' && isCharInString("+-/*^()", *(user_input-1)) == 1) {
			printf("1\n");
			should_push = 0;
		}
		// if format 1-(1+2)  minus before brackets
		else if (*(user_input-1) == '-' && isCharInString("+-/*^()", *(user_input)) == 1) {
			printf("2\n");
			should_push = 0;
		}
		// if format 1+(3*5) two operators in a row
		else if (isCharInString("()", *(user_input)) && isCharInString("+-/*^()", *(user_input-1)) == 1) {
			printf("3\n");
			should_push = 1;
		}
		// if format 1e-5
		else if (*(user_input) == '-' && *(user_input-1) == 'e') {
			printf("4\n");
			should_push = 0;
		}
		// If a valid double character and the next character isnt an operator
		else if (isCharInString("0123456789.e", *user_input) == 1 && isCharInString("+-/*()", *(user_input+1)) == 0 ) {
			printf("5\n");
			should_push = 0;
		}
		// If a vlaid double cahracter and the next character is an operator
		else if (isCharInString("0123456789.", *user_input) == 1 && isCharInString("+-/*()", *(user_input+1)) == 1 ) {
			printf("6\n");
			should_push = 1;
		}
		// If an operator
		else if (isCharInString("+-/*^()", *user_input) == 1) {
			printf("7\n");
			should_push = 1;
		}	
		// If the last character
		if (*(user_input + 1) == '\0') {
			should_push = 1;
			printf("last character\n");
		}
		
		// If we want to push the string
		if (should_push == 1) {
			
			printf("pushing string %s\n", p_string);
			
			// Copy the string to the infix_expression
			strcpy(*infix_expression, p_string);
			expression_length++;
			infix_expression++;


			// Reallocate memory for the string
			//p_string = realloc(p_string, element_length*sizeof(char));
			p_string = malloc(element_length*sizeof(char));
			
			// Point back to the first element of the string
			string = p_string;
			
			printf("wiped string %s\n", p_string);
		}
		else {
			
			// Go to next element of the string
			string++;
		}
		
		// Go to the next input character
		user_input++;
	}
	//print2D(p_infix);
	free(p_string);
	
	return expression_length;
}

