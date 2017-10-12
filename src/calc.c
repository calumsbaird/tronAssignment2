#include "calc.h"

void help(void)
{
	// Define a integer to store the ASCII of a character
	int character;
	
	// Assign file a pointer
	FILE *fpointer;
	
	// Opens the help file assigning it to a pointer, (read only)
	fpointer = fopen("src/help.txt", "r");
	
	// Go through the file character by character until the end of file (EOF) character
	while ((character = getc(fpointer)) != EOF)
	{
		// Print the character
        printf("%c",character);
	}
	
	// Close the file
	fclose(fpointer);
}

void quit(void) {
	printf("Goodbye!\n");
}

void error(void) {
	printf("Error: Illegal input!\n");
}