#include "calc.h"

int calc(char * user_input) {

	char ** infix_stack, ** postfix_stack;
	int stack_length = 2048;
	infix_stack =  malloc(stack_length*sizeof(char*));
	postfix_stack = malloc(stack_length*sizeof(char*));
	
	
	createInfix(user_input, infix_stack);
	//printf("test\n");
	infixToPostfix(infix_stack, postfix_stack);
	//printf("test\n");
	printf("stack addr: %p\n", infix_stack);
	
	//printStack(infix_stack);
	//printStack(postfix_stack);
	
	return 0;
}

int push(char ** stack, char *string) {
	
	//printf("value at stack |%s|\n", *stack);
	
	// Loop through stack to find a null position
	while (1) {
		//printf("value at stack |%s|\n", *stack);
		if (*stack == NULL) {
			//printf("firing null\n");
			
			// Allocate memory to an element of the stack
			int stack_element_length = 100;
			*stack = malloc(stack_element_length*sizeof(char));
			
			// Go through the string
			while (*string) {
				
				printf("character: %c\n", *string);
				// Copy the values into the stack
				**stack = *string;
				printf("address at stack: %p\n", stack);
				
				printf("stack string: %s\n", *stack);
				//printf("character: %c\n", *string);
				
				//*stack++;
				string++;
				
				
			}
			return 0;
		}
		else {
			stack ++;
		}
	}
	return 0;
}

char peekString(char * string) {
	while (*string) {
		string++;
	}
	return *(string-1);
}

char popString(char * string) {
	while (*string) {
		string++;
	}
	//printf("values poppin b4: |%c|\n", *(string-1));
	//printf("address we are opping: %p\n", (string-1));
	char temp = *(string-1);
	*(string-1) = '\0';
	//printf("values poppin after: |%c|\n", *(string-1));
	//printf("value returning: |%c|\n", temp);
	return temp;
}


int pushString(char * string, char character) {
	printf("value at string |%p|\n", string);
	while (1) {
		
		if (*string == '\0') {
			printf("value in str %p|\n", string);
			//printf("firing null\n");
			*string = character;
			//string++;
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

void createInfix(char * user_input, char ** infix_stack) {
	int stack_element_length = 16;
	char * string;
	string = malloc(stack_element_length*sizeof(char));
	
	// First element exceptions
	// If the first character is a minus it must be part of the number
	if (*user_input == '-' || *user_input == '.') {
		
		// Put is onto the string
		pushString(string, *user_input); 
		
		// Go to the next element
		user_input++;
	}
	// Go through the input
	while (*user_input) {
		
		// If the input is '-' and the previous was an operator format 3+-5 or 3*(-5) but not (2*3)-5
		if (*user_input == '-' && isCharInString("+-*/^(", *(user_input - 1)) == 1) {
			printf("1\n");
			// push the input to the string
			pushString(string, *user_input);
		}		
		// If the character is an operator put it straight onto the infix expression
		else if (isCharInString("+-*/^()", *user_input) == 1) {
			printf("2\n");
			// Create a temporary string with the operator in it and push it to the infix stack
			char *temp = malloc(2*sizeof(char));
			*temp = *user_input;
			push(infix_stack, temp);
			free(temp);
		}
		// Otherwise the input must be a number minus dp or e which all go on the string
		else {
			printf("should be running\n");
			pushString(string, *user_input);
		}
		printf("string: %s\n", string);
		// Check whether the string needs to be pushed to the expression
		// If the next character is an operator (with exception of 1e-5) OR the next input is a null
		//printf("user input%c \n", *user_input); 
		//printf("is char in string: %d\n", isCharInString("+-*/^()", *(user_input+1)));
		if ((*user_input != 'e' && isCharInString("+-*/^()", *(user_input+1)) == 1 ) || *(user_input+1) == '\0') {
			printf("running\n");
			printf("string: %s\n", string);
			// Push the string to the infix expression and wipe it
			push(infix_stack, string);
			string = malloc(stack_element_length*sizeof(char));
		}
		
		// Go to next element
		user_input++;
	}
	printStack(infix_stack);
}


double evaluateStack(char ** stack) {
	
	while (*stack) {		
		stack++;
	}
	return 0;
}
int precedence(char symbol) {
	
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

void infixToPostfix (char ** infix_stack, char ** postfix_stack) {
	
	// Define an operator stack to temporarily hold operators
	char * operator_stack;
	operator_stack = malloc(100*sizeof(char));

	while (*infix_stack) {
		
		// If an operator
		if (isOperator(*infix_stack)) {
			
			// If stack empty
			if (peekString(operator_stack) == '\0') {
				
				// Push the operator onto the stack
				pushString(operator_stack, ** infix_stack);
			}
			// If the current operator is larger than the operator at the top of the string
			else if (precedence(**infix_stack) > precedence(peekString(operator_stack))) {
				
				// Push the operator onto the stack
				pushString(operator_stack, ** infix_stack);
			}
			else if (precedence(**infix_stack) <= precedence(peekString(operator_stack))) {
				// Loop through the operator stack from the top
				while (precedence(**infix_stack) <= precedence(peekString(operator_stack)) /*&& peekString(operator_stack) != '\0'*/) {
					
					//printf("count: %d", count);
					//printf("operators: %s\n", operator_stack);
					
					// Pop last operator from stack to post_fix
					char *temp = malloc(2*sizeof(char));
					*temp = popString(operator_stack);
					push(postfix_stack, temp);
					free(temp);
				}
				
					pushString(operator_stack, **infix_stack);
				//}
				
				//printf("||%c||", popString(operator_stack));
				
				//push(postfix_stack, "hello");
			}
			
		}
		
		// Otherwise must be a number so put it on the stack
		else {

			push(postfix_stack, *infix_stack);
			//printf("test int\n");
			//printStack(postfix_stack);
			
		}
		infix_stack++;
	}
	
	//printStack(postfix_stack);
	//printStack(postfix_stack);
	
	//printf("operator_stack: |%s|\n", operator_stack);
	
	
	// Push the final operators onto the string
	while (peekString(operator_stack)) {
		
		// Create a temporary string
		char *temp = malloc(2*sizeof(char));
		
		// Pop the the top of the operator_stack
		*temp = popString(operator_stack);
		
		// Push the operator to the postfix expression
		push(postfix_stack, temp);
		free(temp);
	}

	//printf("count: %d", count);
	//prinnt
	printf("postfix: \n");
	printStack(postfix_stack);
	printf("operator_stack: |%s|\n", operator_stack);
}

int isOperator(char * input) {
	if (strlen(input) == 1 && isCharInString("+-*/^()", *input)) {
		return 1;
	}
	else 
		return 0;
}