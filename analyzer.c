#include "analyzer.h"
#include <ctype.h>
#include <stdlib.h>

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

/* returns the lenght of the longest word in the file */

int longest_word_lenght(FILE *fp) {

    int maxLen = 0;
    int curWordLen = 0;
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t'){ 

            if (curWordLen > maxLen) maxLen = curWordLen;
            curWordLen = 0;
        } else {
            curWordLen++;
        }
    }

    if (curWordLen > maxLen) maxLen = curWordLen; // in case the last word is the longest

    rewind(fp);
    return maxLen;
}

/* returns the longes word in the file, if two or more words have the same max lenght,
it returns the one that appears first in the file */

char *longest_word(FILE *fp, int maxWordLen) { //

    char *longestWord = malloc(maxWordLen +1);
    int curWordLen = 0;
    char ch;
    int found = 0;
    while (!found && (ch = fgetc(fp)) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {

            if (curWordLen == maxWordLen) {
                found = 1;
                longestWord[maxWordLen] = '\0';
            }
            curWordLen = 0;
        } else {

            longestWord[curWordLen] = ch;
            curWordLen++;
        }
    }

    // if longest word is the last one
    if (curWordLen == maxWordLen) {
        found = 1;
        longestWord[maxWordLen] = '\0';
    }

    if (found) {
        return longestWord;
    } else {
        free(longestWord);
        return NULL;
    }

}