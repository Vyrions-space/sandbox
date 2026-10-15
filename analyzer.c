#include "analyzer.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD 1000

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

/* returns the longest word in the file, if more than one word are the longest 
it returns the one that happears first, if there are no words, returns NULL;
assumes that the file pointer fp isn't NULL*/

char *longest_word(FILE *fp) {
    int curLen = 0;
    int longestLen = 0;

    char* curWord = malloc(1);
    char* longestWord = malloc(1);
    int stringCap = 1;

    char ch;
    while ((ch = fgetc(fp)) != EOF) {

        if (ch == ' ' || ch == '\n' || ch == '\t') {

            if (curLen > longestLen) {

                char* temp = realloc(longestWord, curLen +1);
                if (!temp) {
                    free(curWord);
                    free(longestWord);
                    return NULL;
                }

                longestLen = curLen;
                longestWord = temp;
                memcpy(longestWord, curWord, curLen);
                longestWord[curLen] = '\0';
            }
            
            curLen = 0;
        } else {

            if (curLen +1 > stringCap) {

                stringCap++;
                char *temp = realloc(curWord, stringCap);
                if (!temp) {
                    free(curWord);
                    free(longestWord);
                    return NULL;
                }
            }

            curWord[curLen] = ch;
            curLen++;
        }
    }

    if (curLen > longestLen) {
        char* temp = realloc(longestWord, curLen +1);
        if (!temp) {
            free(curWord);
            free(longestWord);
            return NULL;
        }

        longestWord = temp;
        memcpy(longestWord, curWord, curLen);
        longestWord[curLen] = '\0';
    }

    if (strlen(curWord) == 0) {
        free(longestWord);
        longestWord = NULL;
    }

    free(curWord);
    return longestWord;
}

/* returns the shortest word in the file, if more than one word are the shortest 
it returns the one that happears first, if there are no words, returns NULL;
assumes that the file pointer fp isn't NULL, also assumes that first word has less
than 1000 characters*/

char *shortest_word(FILE *fp) {
    int curLen = 0;
    int shortestLen = MAX_WORD;

    char* curWord = malloc(1);
    char* shortestWord = malloc(1);
    int stringCap = 1;

    char ch;
    while ((ch = fgetc(fp)) != EOF) {

        if (ch == ' ' || ch == '\n' || ch == '\t') {

            if (curLen < shortestLen) {

                char* temp = realloc(shortestWord, curLen +1);
                if (!temp) {
                    free(curWord);
                    free(shortestWord);
                    return NULL;
                }

                shortestLen = curLen;
                shortestWord = temp;
                memcpy(shortestWord, curWord, curLen);
                shortestWord[curLen] = '\0';
            }
            
            curLen = 0;
        } else {

            if (curLen +1 > stringCap) {

                stringCap++;
                char *temp = realloc(curWord, stringCap);
                if (!temp) {
                    free(curWord);
                    free(shortestWord);
                    return NULL;
                }
            }

            curWord[curLen] = ch;
            curLen++;
        }
    }

    if (curLen < shortestLen) {
        char* temp = realloc(shortestWord, curLen +1);
        if (!temp) {
            free(curWord);
            free(shortestWord);
            return NULL;
        }

        shortestWord = temp;
        memcpy(shortestWord, curWord, curLen);
        shortestWord[curLen] = '\0';
    }

    if (strlen(curWord) == 0) {
        free(shortestWord);
        shortestWord = NULL;
    } 

    free(curWord);
    return shortestWord;
}