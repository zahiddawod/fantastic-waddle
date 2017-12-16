#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

#include <string.h>

int morph(char *number);

int main(int argc, char *argv[]) {
	// If the argv doesn't have at least 2 arguments then print how to use the program
	if (argc < 2) {
		printf("Usage: %s fileName.fileExtension\n", argv[0]);
		printf("\nWhere\n - 'fileName' is the name of the file\n - 'fileExtension' is the fileName's extension\n");
	} else { // Otherwise that means the user is correctly using the program
		// Check if the second argument is valid (If the file exists in directory)
		FILE *file = fopen(argv[1], "r");
		if (file == NULL) {
			printf("FILE: %s does not exist.\n", argv[1]);
			return(-1);
		}
		
		// Check if file is a binary since we read from file differently
		if (strstr(argv[1], ".bin") != NULL) { // File is binary
			unsigned int num;
			fread(&num, sizeof(unsigned int), 1, file);

			fclose(file);

			char buffer[10]; // Array to hold value of num
			sprintf(buffer, "%u", num); // Convert num to string

			morph(buffer);
		} else {
			char *line;
			size_t len = 0;
			getline(&line, &len, file);

			fclose(file);

			morph(line);
		}
	}
}

int morph(char *number) {
    char *args[3];
    int i;

    args[0] = "isPrime"; // The program to morph to
    args[1] = number; // Second argument needed to run isPrime program
    args[2] = NULL; // Last argument always has to be NULL
    printf("Morphing into the '%s' program using execvp()..\n", args[0]);

	i = execvp("./isPrime", args);	// This program should terminate after this line
	//printf("execvp() did not execute but the number that would have been checked is %s\n", number);

	// If excevp() doesn't work then that means it failed and will return -1
    return(-1);
}

