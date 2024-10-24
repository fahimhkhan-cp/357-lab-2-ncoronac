#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    /* Takes file as a command-line argument and prints the last two lines of file.
    if there are fewer than two lines, print what is available */

    FILE *file;
    char *line = NULL;
    size_t len = 0;
    char *line1 = NULL;        // second to last line
    char *line2 = NULL;        // last line

    if(argc > 1) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("Could not open file.");
            return 1;
        }
    } else {
        file = stdin;
    }

    // if getline()==-1, then the line was not successfully read
    while (getline(&line, &len, file) != -1) {
        if (line2 != NULL) {
            free(line1);        // free allocated memory to update it
            line1 = line2;      // updates second to last line
        }
        line2 = strdup(line);   // duplicates current line to be last line
    }

    if (line1 != NULL) printf("%s", line1);
    if (line2 != NULL) printf("%s\n", line2);

    free(line);
    free(line1);
    free(line2);
    fclose(file);

    return 0;
}