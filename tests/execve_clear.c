#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void clear_terminal() {
	// Path to the 'clear' command
	char *path = "/usr/bin/clear";

	// Arguments for the command (first argument is the command name)
	char *args[] = {"clear", NULL};

	// Environment variables (use the current process environment)
	char *env[] = {"TERM=xterm-256color", NULL};

	// Execute the 'clear' command
	if (execve(path, args, env) == -1) {
		perror("execve failed");
		exit(EXIT_FAILURE); // Exit if execve fails
	}
}

int main() {
	printf("This text will be cleared!\n");

	// Clear the terminal screen
	clear_terminal();

	// This line will not execute if execve succeeds
	printf("You won't see this if execve works.\n");

	return 0;
}
