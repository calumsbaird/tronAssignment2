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
	while (1) {
		//printf("value at stack |%s|\n", *stack);
		if (*stack == NULL) {
			//printf("firing null\n");
			int stack_element_length = 100;
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
	char temp = *(string-1);
	*(string-1) = '\0';
	return temp;
}


int pushString(char * string, char character) {
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
	else if (*user_input == '(') {
		pushString(string, *user_input);
		push(stack, string);
		string = malloc(stack_element_length*sizeof(char));
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
		// if format 1+(3*5) two operators in a row
		else if (isCharInString("()", *(user_input)) && isCharInString("+-/*^()", *(user_input-1)) == 1) {
			//push(stack, string);
			string = malloc(stack_element_length*sizeof(char));
			pushString(string, *user_input);
			push(stack, string);
			string = malloc(stack_element_length*sizeof(char));
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

	//printf("length: %ld\n", strlen(*infix_stack));
	//printf("is operator:  %d\n", isOperator(*infix_stack));
	
	int count = 0;
	while (*infix_stack) {
		//printf("infix stack ---- %s\n", *infix_stack);
		count++;
		// If an operator
		if (isOperator(*infix_stack)) {
			
			// If stack empty
			if (peekString(operator_stack) == '\0') {
				//printf("fire*|%c|\n", **infix_stack);
				// Push the operator onto the stack
				pushString(operator_stack, ** infix_stack);
			}
			// If the current operator is larger than the operator at the top of the string
			else if (precedence(**infix_stack) > precedence(peekString(operator_stack))) {
				
				// Push the operator onto the stack
				pushString(operator_stack, ** infix_stack);
			}
			else if (precedence(**infix_stack) <= precedence(peekString(operator_stack))) {
				
				printf("the fuxk is infix : |%c|", **infix_stack);
				// Loop through the operator stack from the top
				while (precedence(**infix_stack) <= precedence(peekString(operator_stack)) /*&& peekString(operator_stack) != '\0'*/) {
					
					//printf("count: %d", count);
					//printf("operators: %s\n", operator_stack);
					
					// Pop last operator from stack to post_fix
					char temp[2] = "\0";
					temp[0] = popString(operator_stack);
					push(postfix_stack, temp);			
				}
				
				//printf("TESSSTTTT : |%s|", *operator_stack);
				
				/*
				// If the operator stack is empty
				if (*operator_stack == NULL) {
					//printf("hoorah");
					//printf("the fuxk is infix : |%c|", **infix_stack);
					// Put the operator at the end of the postfix
					char temp[2] = "\0";
					temp[0] = **infix_stack;
					
					
					push(postfix_stack, temp);
					//pushString(operator_stack, **infix_stack);
				}
				
				*/
				// Otherwise add it to the operator stack
				//else {
					// Push the character to the operator stack
					//printf("HELLO\n");
					pushString(operator_stack, **infix_stack);
				//}
				
				//printf("||%c||", popString(operator_stack));
				
				//push(postfix_stack, "hello");
			}
			
		}
		
		// Otherwise must be a number so put it on the stack
		else {

			push(postfix_stack, *infix_stack);
			printf("test int\n");
			//printStack(postfix_stack);
			
		}
		infix_stack++;
	}
	
	printStack(postfix_stack);
	printf("operator_stack: |%s|\n", operator_stack);
	// Push the final character onto the string
	//printf("||%c||", popString(operator_stack));
	char temp[2] = "\0";
	//temp[0] = popString(operator_stack);
	temp[0] = '+';
	push(postfix_stack, "4");
	

	printf("count: %d", count);
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