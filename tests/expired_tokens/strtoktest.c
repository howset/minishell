#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <string.h>

int main() {
    // Read a line of input from the user
    char *input = readline("Enter something: ");
    
    if (input != NULL) {
        // Use strtok to split the string into words
        char *delimiters = " \t\n";  // Whitespace characters as delimiters
        char *word = strtok(input, delimiters);
        
        int word_count = 0;
        
        // Iterate through the string to count words
        while (word != NULL) {
            word_count++;
            word = strtok(NULL, delimiters); // Continue to the next word
        }
        
        // Print the number of words
        printf("Number of words: %d\n", word_count);
        
        // Free the memory allocated by readline
        free(input);
    } else {
        printf("Error: readline returned NULL.\n");
    }

    return 0;
}