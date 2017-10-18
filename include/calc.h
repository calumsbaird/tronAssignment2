#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <unistd.h>

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

// calc.c headers
int calc(char *);
int push(char **, char *);
char peekString(char * string);
char popString(char * string);
void print2D(char **, int);
int pushString (char * string, char character);
int createInfix(char * user_input, char **);
double evaluateStack(char ** stack);
int infixToPostfix(char**, int, char**);
int isOperator(char * input);
void free2D(char ** expression, int);
void allocate2D(char ** expression, int expression_length);