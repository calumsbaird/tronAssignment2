#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>

#define BUF_SIZE 2048

// auxiliary.c headers
void help(void);
void quit(void);
void error(void);

// checkInput.c headers
int checkInput (char *);
int isCharInString (char *, char);

// simplifyInput.c headers
void simplifyInput(char *);
void removeChar(char *, char);
void addStar(char * user_input);

// calc.c headers
int calc(char *);
int push(char * string, char * stack);
char peek(char * string);

void print2D(char *, int);
//int pushString (char * string, char character);
int createInfix(char * user_input, char *);
double evaluateStack(char ** stack);
int infixToPostfix(char*, int, char*);
int isOperator(char * input);
void free2D(char ** expression, int);
int convertScientific(char *);
double calculate(char *, int);


// auxiliary.c headers
int precedence(char character);
char pop(char * string);