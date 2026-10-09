#include "analyzer.h"
#include <ctype.h>

/**
 * @brief Count the number of lines in a file.
 *
 * This function reads through the given file stream character by character
 * and counts how many newline characters (`'\n'`) are present, which
 * corresponds to the number of lines in the file. After counting, the
 * file pointer is reset to the beginning of the file using `rewind(fp)`.
 *
 * @param fp Pointer to an open file (`FILE*`) to be read.
 *           The file must be opened in a readable mode.
 *
 * @return The number of lines found in the file.
 *
 * @note The file pointer is reset to the start of the file after counting,
 *       so subsequent reads will begin from the beginning.
 *
 * @warning If `fp` is `NULL`, the behavior is undefined.
 */
int count_lines(FILE *fp) {
    int lines = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    rewind(fp); // reset file pointer
    return lines;
}

/* count the numbers of words in a file */

int count_words(FILE *fp){
    int words = 0, in_word = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF){
        if (ch == ' ' || ch == '\n' || ch == '\t'){
            in_word = 0;
        } else if (in_word == 0){
            in_word = 1;
            words++;
        }
    }
    rewind(fp);
    return words;
}

/* count the number of characters in a file */

int count_characters(FILE *fp) {

    int characters = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        characters++;
    }

    rewind(fp);
    return characters;
}