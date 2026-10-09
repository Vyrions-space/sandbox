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
    // check for last word
    if (curWordLen > maxLen) maxLen = curWordLen;

    rewind(fp);
    return maxLen;
}

/* returns the first word of length wordLen that appears in the file */

char *find_word_from_len(FILE *fp, int wordLen) { //

    char *word = malloc(wordLen +1);
    int curWordLen = 0;
    char ch;
    int found = 0;
    while (!found && (ch = fgetc(fp)) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {

            if (curWordLen == wordLen) {
                found = 1;
                word[maxWordLen] = '\0';
            }
            curWordLen = 0;
        } else {

            word[curWordLen] = ch;
            curWordLen++;
        }
    }
    // if longest word is the last one
    if (curWordLen == wordLen) {
        found = 1;
        word[curWordLen] = '\0';
    }

    if (found == 1) {
        return longestWord;
    } else {
        free(longestWord);
        return NULL;
    }

}

/* returns the longest word of the file, if two or more words are the longest
returns the first one that appears in the file */
char *longest_word(FILE *fp) {
    return find_word_from_len(fp, longest_word_lenght(fp));
}