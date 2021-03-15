// PID: 730238995
// I pledge the COMP211 honor code.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* defined numbers for the maximum line length and the maximum number of lines in input.
 * */
#define MAX_LINE_LENGTH 9000
#define MAXIMUM_AMT_OF_LINES 500000

int pstrcmp(const void *input, const void *line_count);
void printOutput(char *input[], int line_count);
void freeMemory(char *input[], int line_count);

int main()
{
    /* Memory allocated for array of pointers, and then handled if empty.
     * A line count integer variable is established to hold the number of lines from the input.
     * Each pointer is given a line of text from input and line_count is enumerated accordingly.
     * */ 
    char **input = malloc(MAXIMUM_AMT_OF_LINES * sizeof(char *));
    if (input == NULL)
    {
        fprintf(stderr, "out of memory\n");
        return EXIT_FAILURE;
    }

    int line_count = 0;
    char *copyOver;
    char *copy = malloc(MAX_LINE_LENGTH + 1);
    if (copy == NULL) {
        fprintf(stderr, "out of memory\n");
        return EXIT_FAILURE;
    }
    /* This while loop iterates through the input using the fgets function.
     * Memory is allocated for a buffer array, that is pointed to by "copy" and is read into via the stdin stream, for each line of text in
     * the "input" array of pointers..
     * */
    while ((copyOver = fgets(copy, MAX_LINE_LENGTH, stdin)) != NULL) {
        input[line_count] = (char *)malloc(MAX_LINE_LENGTH);
        if (input[line_count] == NULL) {
            fprintf(stderr, "out of memory\n");
            return EXIT_FAILURE;
        }
        /* Each line of text is copied over at each index of the array that is pointed to by "input"
         * */
        strcpy(input[line_count], copyOver);
        line_count++;
    }
    // this space is freed once it is finished
    free(copy);
    
    qsort(input, line_count, sizeof(char *), pstrcmp);

    printOutput(input, line_count);

    freeMemory(input, line_count);

   return EXIT_SUCCESS;
}

/* intermediary method for our compare function, strcmp, because qsort does not allow direct access to strcmp for some reason.
 * */
int pstrcmp(const void *input, const void *line_count)
{
    return strcmp(*(char * const *)input, *(char * const *)line_count);
}

/* print each line at each index.
 * */ 
void printOutput(char *input[], int line_count)
{
    int i;
    for (i = 0; i < line_count; ++i) {
        printf("%s", input[i]);
    }
}

/* frees rest of memory in "input" array that was used, once everything is sorted and printed properly.
 * */
void freeMemory(char *input[], int line_count)
{
    int i;
    for (i = 0; i < line_count; ++i) {
        free(input[i]);
    }
    free(input);
}
