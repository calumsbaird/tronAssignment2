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
int precedence(char character);
char pop(char * string);
int push(char * string, char * stack);
char peek(char * string);
int convertScientific(char *);
void print2D(char *, int);
int isCharInString (char *, char);
int isOperator(char * input);

// checkInput.c headers
int checkInput (char *);

// simplifyInput.c headers
void simplifyInput(char *);
void removeChar(char *, char);
void addStar(char *);

// calc.c headers
int calc(char *);
int createInfix(char *, char *);
int infixToPostfix(char*, int, char*);
double calculate(char *, int);



