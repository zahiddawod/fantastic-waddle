#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

// Assume that the binary file will onsist of 10 unsigned int numbers
#define amountOfNumbers 10

int morph(char *number);

int main(int argc, char *argv[]) {
	unsigned int numbers[amountOfNumbers]; // Array to store the numbers retrieved from file
	int cpid[amountOfNumbers]; // amountOfNumbers child process to be executed
	int pid; // Parent process
	int status;

	int childProcessIds[amountOfNumbers];

	int i, j;

	if (argc < 2) { // Ensures the user inputs a file when using the executable
		printf("Usage: %s fileName.fileExtension\n", argv[0]);
		printf("\nWhere\n - 'fileName' is the name of the file\n - 'fileExtension' is the fileName's extension\n");
		return(-1);
	} else {
		FILE *file = fopen(argv[1], "r");
		if (file == NULL) { // Check if file exists in directory
			printf("FILE: %s does not exist.\n", argv[1]);
			return(-1);
		}

		// Go through 10 lines in the file and store them in array
		for (i = 0; i < amountOfNumbers; i++) {
			char *line;
			size_t len = 0;
			getline(&line, &len, file);
			
			numbers[i] = atoi(line);
		}

		fclose(file); // Close file stream
	}

	for (i = 0; i < amountOfNumbers; i++) { // creates 'amountOfNumbers' child processes
		cpid[i] = fork();
		if (cpid[i] < 0) exit(-1); // fork error
		
		if (cpid[i] == 0) { // child processes
			char buffer[10]; // convert arr[i] back to string
			sprintf(buffer, "%u", numbers[i]);

			childProcessIds[i] = cpid[i];

			morph(buffer); // morph child to isPrime program with number 'buffer'
		}/* else {
			waitpid(-1, &status, 0);
			
		}*/
	}
	while (pid = wait(&status) > 0); // Waits until all child processes end

	// print the results of the child processes that checked if the numbers in the array were prime
	for (i = 0; i < amountOfNumbers; i++) {
		if (WIFEXITED(status)) {
			if(WEXITSTATUS(status) == 1) printf("%d is a prime number.\n", numbers[i]);
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
