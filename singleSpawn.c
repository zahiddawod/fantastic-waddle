#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>

#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

int morph(char *number);

int main(int argc, char *argv[]) {
	int cpid;
	int pid;
	int status;
	
	cpid = fork();
	if (cpid < 0) {
		printf("Fork error!");
		exit(-1);
	}

	if (cpid == 0) {
		printf("Child process pid=%d  parent process id=%d\n", getpid(), getppid());

		// If the argv doesn't have at least 2 arguments then print how to use the program
		if (argc < 2) {
			printf("Usage: %s fileName.fileExtension\n", argv[0]);
			printf("\nWhere\n - 'fileName' is the name of the file\n - 'fileExtension' is the fileName's extension\n");
			return(-1);
		} else { // Otherwise that means the user is correctly using the program
			// Check if the second argument is valid (If the file exists in directory)
			FILE *file = fopen(argv[1], "r");
			if (file == NULL) {
				printf("FILE: %s does not exist.\n", argv[1]);
				return(-1);
			}

			// Check if file being opened is binary
			if (strstr(argv[1], ".bin") != NULL) { // file is binary
				unsigned int num;
				fread(&num, sizeof(unsigned int), 1, file);

				fclose(file);

				char buffer[10];
				sprintf(buffer, "%u", num);

				morph(buffer);
			} else {
				char *line;
				size_t len = 0;
				getline(&line, &len, file);

				fclose(file);

				morph(line);
			}
		}
	} else {
		pid = wait(&status); // wait until child thread completes
		printf("\nParent process pid=%d  child process id=%d\n\n", pid, cpid); // Show that we are now in parent process (parent pid = child id)

      	// checking if the program was signalled to terminate
		if (WIFSIGNALED(status)) printf("Child exited with WIFSIGNALED:\n child process terminated its execution because it was signalled to do so either by another process or because of an internal error.\n\n");

      	// checking if the program existed normally using return() or exit()
		if (WIFEXITED(status)) printf("Child exited with WIFEXITED:\n child process completed its execution normally either by calling return() or by calling the function exit().\n\n");

      	// when the value returned can be positive or negative (i.e., signed value) 
      	printf("Child exited with WEXITSTATUS(%d) (char)\n", (char)WEXITSTATUS(status));
      
      	// when the value returned is an unsigned value (positive)
      	printf("Child exited with WEXITSTATUS(%d) (unsigned int)\n\n", WEXITSTATUS(status));

		if (WIFEXITED(status)) { // ensure the child proccess exited with either a return() or exit()
			if (WEXITSTATUS(status) == 1) printf("INPUT IS A PRIME NUMBER\n");
			else if (WEXITSTATUS(status) == 0) printf("INPUT IS NOT A PRIME NUMBER\n");
			else printf("EXECUTABLE FILE WAS NOT PROPERLY USED.\n");
		}
	}
	return(0);
}

int morph(char *number) {
    char *args[3];
    int i;

    args[0] = "isPrime"; // The program to morph to
    args[1] = number; // Second argument needed to run isPrime program
    args[2] = NULL; // Last argument always has to be NULL
    printf("Morphing into the '%s' program using execvp()..\n", args[0]);

    i = execvp("./isPrime", args); // This program should terminate after this line
	//printf("execvp() did not execute but the number that would have been checked is %s\n", number);

	// If execvp() doesn't work then that means it failed and will return -1
    return(-1);
}
