#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyzer.h"

/**
 * @brief Entry point of the program.
 *
 * This program processes a file based on the command-line arguments provided.
 * Currently, it supports counting the number of lines in a file.
 *
 * **Usage:**
 * ```
 * ./program <filename> <option>
 * ```
 *
 * **Options:**
 * - `-l` : Count and display the number of lines in the file.
 *
 * @param argc Argument count. The program expects at least 3 arguments:
 *             - `argv[0]`: program name
 *             - `argv[1]`: filename
 *             - `argv[2]`: option (currently `-l`).
 * @param argv Argument vector. Array of strings containing the command-line arguments.
 *
 * @return `0` on successful execution.
 *         `1` if incorrect usage, file open error, or unknown option.
 *
 * @note The program relies on the helper function ::count_lines to perform
 *       the line counting operation.
 *
 * @warning If the file cannot be opened, an error message is printed
 *          using `perror`, and the program exits with a non-zero status.
 */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <filename> <option>\n", argv[0]);
        printf("Options:\n");
        printf("  -l    Count lines\n");
        printf("  -w    Count words\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    if (strcmp(argv[2], "-l") == 0) {
        printf("Lines: %d\n", count_lines(fp));
    } else if(strcmp(argv[2], "-w") == 0){
        printf("Words: %d\n", count_words(fp));
    } else if (strcmp(argv[2], "-c") == 0){
        printf("Characters: %d\n", count_characters(fp));
    } else {
        printf("Unknown option: %s\n", argv[2]);
    }
    fclose(fp);
    return 0;
}
