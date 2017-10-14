#include "calc.h"

int calc(char * user_input) {
	
	//double number;
	
	char * expression = malloc(100*sizeof(char));
	expression = user_input;
	char ** stack;
	int stack_length = 2048;
	stack =  malloc(stack_length*sizeof(char*));
	//*(stack) = "abc";
	//*(stack+1) = "def";
	//char * p_stack = *stack;
	//int stack_index = 0;
	
	//printStack(stack);
	while (*user_input) {
		
		char * operators = "+-/*()";
		char * integers = "0123456789";
		
		if (isCharInString( integers, *user_input)) {
		
			push(stack, user_input);
		}
		// If an operator
		else if (isCharInString(operators, *user_input) == 1) {
			push(stack, user_input);
		}
		
		//printf("%s\n", *stack);
		
		//stack_index++;
		//stack++;
		user_input++;
	}
	
	
	
	//sscanf(user_input, "%lf", &number);
	
	//printf("number: %lf\n", number);
	
	printf("expression: %s\n", expression);
	
	printStack(stack);
	
	return 0;
}

int push(char ** stack, char *character) {
	//char ** p = stack;
	int stack_element_length = 16;
	//printf("pushing! %p\n", stack);
	//printf("|%s|\n", *stack);
	while (1) {
		if (*stack == NULL) {

			printf("NULL\n");
			*stack = malloc(stack_element_length*sizeof(char));
			**stack = *character;
			printf("2stacked: %s address: %p\n", *stack, stack);
			break;
		}
		else
			stack++;	
	}
	printf("|%s|\n", *stack);
	return 0;
}

int pushString (char * string, char character) {
	while (1) {
		if (string == NULL) {

			printf("NULL\n");
			int stack_element_length = 16;
			string = malloc(stack_element_length*sizeof(char));
			*string = character;
			//printf("2stacked: %s address: %p\n", *stack, stack);
			break;
	}
	else
		string++;	
	}
	return 0;
}

void printStack(char ** stack) {
	printf("nearlu");
	
	while(*stack) {
		printf("inside");
		while(**stack) {
			printf("%c", **stack);
			stack++;
			//printf("aaa%saaa\n", *stack);
		}
		printf("%s", *stack);
		printf("|\n");
		stack++;
	}
	
}