#include "calc.h"

int calc(char * user_input) {

	char ** infix_stack, ** postfix_stack;
	int stack_length = 2048;
	infix_stack =  malloc(stack_length*sizeof(char*));
	postfix_stack = malloc(stack_length*sizeof(char*));
	
	
	createInfix(user_input, infix_stack);
	infixToPostfix(infix_stack, postfix_stack);
	
	printf("stack addr: %p\n", infix_stack);
	
	printStack(infix_stack);
	printStack(postfix_stack);
	
	return 0;
}

int push(char ** stack, char *string) {
	//printf("value at stack |%s|\n", *stack);
	while (1) {
		//printf("value at stack |%s|\n", *stack);
		if (*stack == NULL) {
			//printf("firing null\n");
			int stack_element_length = 16;
			*stack = malloc(stack_element_length*sizeof(char));
			*stack = string;
			return 0;
		}
		else {
			stack ++;
			//printf("incremented");
			//*stack = string;
		}
	}
	return 0;
}


int pushString (char * string, char character) {
	//printf("value at string |%c|\n", *string);
	while (1) {
		
		if (*string == '\0') {
			//printf("firing null\n");
			*string = character;
			return 0;
		}
		else {
			string ++;
			//printf("incremented");
			//*stack = string;
		}
	}
	return 0;
}


void printStack(char ** stack) {
	printf("|||||||||||||||||||\n");
	
	while(*stack) {
		printf("inside");
		printf("%p\t%s\n", stack, *stack);
		stack++;
	}	
	printf("|||||||||||||||||||\n");
}

void createInfix(char * user_input, char ** stack) {
	int stack_element_length = 16;
	char * string;
	string = malloc(stack_element_length*sizeof(char));
	
	// If the first input is a negative number
	if (*user_input == '-') {
		pushString(string, *user_input);
		user_input++;
	}

	// Go through the user input
	while (*user_input) {
		// If the number is negative (as opposed to minus sign)
		if (*(user_input) == '-' && isCharInString("+-/*^()", *(user_input-1)) == 1) {
			// Put string on stack
			//push(stack,string);
			pushString(string, *user_input);
		}
		// if format 1-(1+2)  minus before brackets
		else if (*(user_input-1) == '-' && isCharInString("+-/*^()", *(user_input)) == 1) {
			pushString(string, *user_input);
			// Put the operator on the stack
			push(stack,string);
			// Wipe the string
			string = malloc(stack_element_length*sizeof(char));
		}
		// if format 1e-5
		else if (*(user_input) == '-' && *(user_input-1) == 'e') {
			// Put the operator on the string
			pushString(string, *user_input);
		}
		// If a valid double character
		else if (isCharInString("0123456789.e", *user_input) == 1) {
			//put it in a string
			pushString(string, *user_input);
			//printf("adding\n");
			// If the next character is not an integer we want to put the string on the stack
			if (isCharInString("01234567890.e", *(user_input + 1) == 0) || *(user_input + 1) == '\0') {
				push(stack, string);
			}
		}
		// If an operator
		else if (isCharInString("+-/*^()", *user_input) == 1) {
			// Put string on stack
			push(stack,string);
			// Wipe the string
			string = malloc(stack_element_length*sizeof(char));
			// Put the operator on the string
			pushString(string, *user_input);
			// Put the operator on the stack
			push(stack,string);
			// Wipe the string
			string = malloc(stack_element_length*sizeof(char));
		}
		// Go to next element
		user_input++;
	}
}

double evaluateStack(char ** stack) {
	
	while (*stack) {		
		stack++;
	}
	return 0;
}
int precedence(char symbol) {
	return 0;
}

void infixToPostfix (char ** infix_stack, char ** postfix_stack) {
	char * operator_stack;
	operator_stack = malloc(100*sizeof(char));
	printf("runnning\n");
	while (*infix_stack) {
		
		if (**infix_stack == '(') {
			printf("openbracket\n");
			// Push the bracket to the operator stack
			pushString(operator_stack, **infix_stack);
		}
		else if (**infix_stack ==
		//else if (
		
		infix_stack++;
	}
	printf("operator_stack: |%s|", operator_stack);
}