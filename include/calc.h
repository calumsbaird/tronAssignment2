#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define BUF_SIZE 2048

// calc.c headers
void help(void);
void quit(void);
void error(void);

// checkInput.c headers
int checkInput (char *);
int isValidChar (char *, char);

// simplifyInput.c headers
void simplifyInput(char *);
void removeChar(char *, char);