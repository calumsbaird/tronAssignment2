#include "calc.h"

// This functions processes our input from infix to postfix to a result
int calc(char * user_input) {
	
	// Define our max sizes
	int element_length = 16, max_expression_length = 1024;
	
	// Create a 2d char array for our infix expression
	char infix_expression[max_expression_length][element_length];
	
	// Create a pointer to the address of the first element of the array
	char *p_infix;
	p_infix = &infix_expression[0][0];
	
	// Create our infix expression and store the value of its length
	int infix_length;
	infix_length = createInfix(user_input, p_infix);
	
	// Print the infix_expression
	//print2D(p_infix, infix_length);
	
	// Create a postfix 2D char array
	char postfix_expression[max_expression_length][element_length];
	
	// Create a pointer to the address of the first element of the array
	char *p_postfix;
	p_postfix = &postfix_expression[0][0];
	
	// Create a postfix expression and store its length
	int postfix_length;
	postfix_length = infixToPostfix(p_infix, infix_length, p_postfix);
	
	// Print the postfix expression
	//print2D(p_postfix, postfix_length);
	
	// Calculate the value
	//double total = calculate(p_postfix, postfix_length);
	//printf("%lf\n", total);
	
	// Calculate our result, the result is printed within this function
	calculate(p_postfix, postfix_length);
	
	return 0;
}

// This creates an infix expression from a string of characters
int createInfix(char * user_input, char * infix_expression) {
	
	// Variable to count the number of terms in expression
	int expression_length = 0;
	
	// Define the length of each term in the expression
	int element_length = 16;
	
	// Create a temporary string that we put onto the infix_expression
	char * string;
	string = malloc(element_length*sizeof(char));
	char * p_string = string;
	
	// Put a bracket at the start of our infix expression - this is because brackets affect the creation of the postfix expression
	// We also add a closing bracket at the end of the expression
	strcpy(infix_expression, "(");
	infix_expression = infix_expression + element_length; // This increments to the next string in our infix expression
	expression_length++; // We record our expression length to make it easier to convert to postfix
	
	
	// Go through the input until we reach a null char
	while (*user_input) {
		
		// Here we put the character onto a string and either put it on to the expression
		// Or we keep adding to the string, depending on whether it forms part of a number
		int should_push = 0;
		
		// Put the character onto the string
		*string = *user_input;
		//printf("user iput: %c\n", *user_input);
				
		// If the first element and negative  // POTENTIAL CAUSE OF ERROR UNSURE WHETHER THE CHARACTER BEFORE WILL BE A NULL
		if ( (*user_input == '-') && (isCharInString("0123456789.", *(user_input+1)) == 1) && (*(user_input-1) == '\0') ) {
			
			should_push = 0;
		}
		// if format (5)-6  (minus after bracket)
		else if (*(user_input-1) == ')' && *(user_input) == '-') {
			
			should_push = 1;
		}
		// if format 1-(1+2)  minus before brackets
		else if (*(user_input) == '-' && isCharInString("(", *(user_input+1)) == 1) {
			
			//printf("fire 2\n");
			should_push = 1;
		}
		// If the number is negative (as opposed to minus sign) The number before must be one of these operators
		else if (*(user_input) == '-' && isCharInString("+-/*^(", *(user_input-1)) == 1) {
			
			//printf("1\n");
			should_push = 0;
		}
		// if format 1+(3*5) two operators in a row
		else if (isCharInString("()", *(user_input)) && isCharInString("+-/*^()", *(user_input-1)) == 1) {
			
			//printf("3\n");
			should_push = 1;
		}
		// if format 1e-5
		else if (*(user_input) == '-' && *(user_input-1) == 'e') {
			
			//printf("4\n");
			should_push = 0;
		}
		// If a valid double character and the next character isnt an operator
		else if (isCharInString("0123456789.e", *user_input) == 1 && isCharInString("+-/*^()", *(user_input+1)) == 0 ) {
			
			//printf("5\n");
			should_push = 0;
		}
		// If a vlaid double cahracter and the next character is an operator
		else if (isCharInString("0123456789.", *user_input) == 1 && isCharInString("+-/*^()", *(user_input+1)) == 1 ) {
			
			//printf("6\n");
			should_push = 1;
		}
		// If an operator
		else if (isCharInString("+-/*^()", *user_input) == 1) {
			
			//printf("7\n");
			should_push = 1;
		}	
		// If the last character
		if (*(user_input + 1) == '\0') {
			
			should_push = 1;
			//printf("last character\n");
		}
		
		// If we want to push the string
		if (should_push == 1) {
			
			// Copy the string to the infix_expression
			strcpy(infix_expression, p_string);
			
			// Go to the next element of the expression
			infix_expression = infix_expression + element_length;

			// Reallocate memory for the string
			p_string = malloc(element_length*sizeof(char));
			
			// Point back to the first element of the string
			string = p_string;
			
			expression_length++;
		}
		// Otherwise we will keep adding to the string
		else {
			
			// Go to next element of the string
			string++;
		}
		
		// Go to the next input character
		user_input++;	
	}
	
	//print2D(p_infix);
	
	// Free the memory for the string
	free(p_string);
	
	// Put a closing bracket on the end of the string
	strcpy(infix_expression, ")");
	expression_length++;	
	
	return expression_length;
}

// This converts an infix expression to a postfix expression, returning its length
int infixToPostfix (char * infix_expression, int infix_length, char * postfix_expression) {
	
	// Defines element length
	int element_length = 16;
	
	// Counter for no of elements of our postfix stack
	int postfix_length = 0;
	
	// This is a temporary string that we will use to pop strings to due to memory faults
	char string[] = "\0";
	
	// Define our stack
	int stack_length = 100;
	char * stack;
	stack = malloc(sizeof(char)*stack_length);
	
	// Go through our infix_expression
	int i = 0;
	while (i < infix_length) {
		
		//printf("address we are writing: %p\n", *postfix_expression);
		//printf("stack: |%s|\n", stack);
		
		// If the element is an operator (includes brackets)
		if (isOperator(infix_expression) == 1) {
			
			//printf("peek of stack: |%c|\n", peek(stack));
			
			// If the element is an opening bracket
			if (infix_expression[0] == '(') {
				
				//printf("case 1\n");
				
				// Push the bracket onto the stack
				push(infix_expression, stack);
				
			}
			// If the operator is a closing bracket
			else if (*infix_expression == ')') {
				
				//printf("case2\n");
				int i = 0;
				
				// Go through the stack (backwards)
				while (peek(stack) != '('  /*&& peek(stack) != '\0'*/) {
					
					//printf("stack currently: %s", stack);
					
					// Pop the stack onto the expression until we reach its corresponding opening bracket
					string[0] = pop(stack);

					// Put the top of the stack onto the expression
					strcpy(postfix_expression, string);
					
					// Go to next element of the postfix expression
					postfix_length++;
					postfix_expression = postfix_expression + element_length;

					// Write the temporary string back to null
					string[0] = '\0';
					
					//printf("peek of stack2: |%c|\n", peek(stack));
					
					i++;
				}
				
				//printf("peek of stack b4 poping: |%c|\n", peek(stack));
				
				// Pop the opening bracket off the stack
				pop(stack);
				
			}
			// If the operator has higher precedence than the top of the stack
			else if (precedence(*infix_expression) > precedence(peek(stack))) {
				
				//printf("case 3\n");
				
				// Put it on the stack
				push(infix_expression, stack);				
			}
			// Otherwise the precedence must be less than or equal to the top of the stack
			else {
				
				//printf("%c\n", *infix_expression);
				//printf("case 4\n");
				
				// While the precedence of the operator at the top of the stack is greater than the current operator
				while (precedence(*infix_expression) <= precedence(peek(stack)) && peek(stack) != '\0') {
					
					// Pop the value of the stack
					string[0] = pop(stack);
					
					// Put the top of the stack onto the expression
					strcpy(postfix_expression, string);
					
					// Write the temporary string back to null
					string[0] = '\0';
					
					// Increment the expression pointer and length
					postfix_expression = postfix_expression + element_length;
					
					//printf("address %p\n", *postfix_expression);
					postfix_length++;

					//printf("stack: %s", stack);
					//printf("precedence: 
				}
				
				// Put the infix operator onto the stack
				push(infix_expression, stack);
			}
		}
		// If the element is a number put it straight onto the postfix expression
		else {
			
			//printf("case 4\n");
			
			strcpy(postfix_expression, infix_expression);
			
			// Increment the expression pointer and length
			postfix_expression = postfix_expression + element_length;
			postfix_length++;	
		}

		i++;
		
		// Go to next element of the infix expression
		infix_expression = infix_expression + element_length;
	}
	
	// Free de memz
	free(stack);
	
	// Return the length of the postfix expression
	return postfix_length;
}

// This takes a postfix expression and calculates the result, printing within
double calculate(char * postfix_expression, int postfix_length) {
	
	// Point to the start of postfix
	char * p_postfix = postfix_expression;
	
	// Boolean to see if we divide by zero
	int divZero = 0;
	
	// Define our element length
	int element_length = 16;
	
	// Loop until we recieve a result
	while(1) {
		
		// Define our operator and 2 operands
		char operator;
		double operand2;
		double operand1;
		
		// Get the first operator
		for (int i = 0; i < postfix_length; i++) {
			
			// If the expression element is an operator
			if (isOperator(postfix_expression) == 1) {
				
				// Our operator becomes this element
				operator = postfix_expression[0];
				
				//printf("operator string: %s", postfix_expression);
				
				// Write the position to null so we skip over it on the next pass
				postfix_expression[0] = '\0';
				
				//printf("operator: %p\t%c\n", postfix_expression, operator);
				//printf("address: %p\n", postfix_expression);
				break;
			}
			// If we never find an operator that means the result has been calculated and must be stored in the first element
			else if (postfix_expression >= p_postfix + i * element_length && i == postfix_length - 1) {
				
				// Convert the result to a double
				double total = atof(p_postfix);
				
				// Make sure we never divided by zero
				if (divZero == 0) {
					
					// Print the result to 3dp
					printf("%.3lf\n", total);
				}
				else {
					
					printf("Error: Divide by zero!\n");
				}
				
				// Return the answer which will be stored in the first element - this is not necessary for the functionality of the current
				// configuration of the program
				return total;
			}
			// Otherwise go to the next element
			else {
				
				postfix_expression += element_length;
			}
			
		}
		
		// The 2nd operand is the first non null string before the operator
		// Go backwards from the operator
		postfix_expression -= element_length;
		
		//printf("postfix: |%s|\n", postfix_expression);
		
		// Go backwards till we get to the starting address
		while (postfix_expression >= p_postfix) {
			
			// If the expression doesnt start with a null character
			if (postfix_expression[0] != '\0') {
				
				// This must be our 2nd operand
				operand2 = atof(postfix_expression);
				
				//printf("operand2: %p\t%lf\n", postfix_expression, operand2);
					
				// Write the first element to null so that we skip over it on the next pass
				postfix_expression[0] = '\0';
				break;
			}
			
			postfix_expression -= element_length;
		}
		
		// The first operand is the first non null string before the second operand
		while (postfix_expression >= p_postfix) {
			
			// If the expression doesnt start with a null character
			if (postfix_expression[0] != '\0') {
				
				// This must be our 1st operand
				operand1 = atof(postfix_expression);
				
				//printf("operand1: %lf\n", operand1);
				
				// Calculate the partial result
				double partial;
				
				// Depending on the operator make a calculation
				switch (operator) {
					case '+':
						partial = operand1 + operand2;
						break;
					case '-':
						partial = operand1 - operand2;
						break;
					case '*':
						partial = operand1 * operand2;
						break;
					case '/':
						partial = operand1 / operand2;
						
						// If we divide by zero
						if (operand2 == 0) {
							divZero = 1;
						}
						break;
					case '^':
						partial = pow(operand1, operand2);
						break;
					default:
						printf("error in calculation\n");
						break;					
				}
				
				// Convert the partial total back into a string
				char partial_string[element_length];
				snprintf(partial_string, element_length, "%lf", partial);

				// Write the answer into the position where the first operand was for calculation on the next pass
				strcpy(postfix_expression, partial_string); 
				
				break;
			}
			
			postfix_expression -= element_length;
		}
	}
	
	// We shouldnt get to this section of the code as we already return a result when trying to find an operator
	// However this is written so we dont get a warning
	
	// Now the last value of the postfix_expression should be our total
	double total = atof(postfix_expression - element_length);
	return total;
}