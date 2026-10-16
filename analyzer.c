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

/* count the numbers of words in a file;
a "word" is considered as a series of characters separated by spaces */

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
a "word" is considered a collection of alfanumeric characters separated by 
eachother with punctuation and/or spaces, with the exeption of an apostrophe
(') placed inbeetween two of the alfanum characters, the returned word is fully
in lowercase;
assumes that the file pointer fp isn't NULL*/

char *longest_word(FILE *fp) {
    int curLen = 0;
    int longestLen = 0;

    char* curWord = malloc(sizeof(char));
    char* longestWord = malloc(sizeof(char));
    int stringCap = 1;

    char ch;
    while ((ch = fgetc(fp)) != EOF) {

        if (ch == ' ' || ch == '\n' || ch == '\t') {

            if (curLen > longestLen) {

                char* temp = realloc(longestWord, (curLen +1) * sizeof(char));
                if (!temp) {
                    free(curWord);
                    free(longestWord);
                    return NULL;
                }

                longestLen = curLen;
                longestWord = temp;
                memcpy(longestWord, curWord, (curLen +1) * sizeof(char));
                longestWord[curLen] = '\0';
            }
            
            curLen = 0;
        } else {

            if (curLen +1 > stringCap) {

                stringCap++;
                curWord = realloc(curWord, stringCap * sizeof(char));
                if (!curWord) {
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
        char* temp = realloc(longestWord, (curLen +1) * sizeof(char));
        if (!temp) {
            free(curWord);
            free(longestWord);
            return NULL;
        }

        longestWord = temp;
        memcpy(longestWord, curWord, (curLen +1) * sizeof(char));
        longestWord[curLen] = '\0';
        longestLen = curLen;
    }

    if (strlen(curWord) == 0) {
        free(longestWord);
        longestWord = NULL;
    }

    free(curWord);
    clean_up_word(&longestWord, &longestLen);
    return longestWord;
}

/* returns the shortest word in the file, if more than one word are the shortest 
it returns the one that happears first, if there are no words, returns NULL;
a "word" is considered a collection of alfanumeric characters separated by 
eachother with punctuation and/or spaces, with the exeption of an apostrophe
(') placed inbeetween two of the alfanum characters, the returned word is fully
in lowercase;
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

        if (ch == ' ' || ch == '\n' || ch == '\t' ) {

            if (curLen < shortestLen) {

                char* temp = realloc(shortestWord, curLen +1);
                if (!temp) {
                    free(curWord);
                    free(shortestWord);
                    return NULL;
                }

                shortestLen = curLen;
                shortestWord = temp;
                memcpy(shortestWord, curWord, curLen +1);
                shortestWord[curLen] = '\0';
            }
            
            curLen = 0;
        } else {

            if (curLen +1 > stringCap) {

                stringCap++;
                curWord = realloc(curWord, stringCap);
                if (!curWord) {
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
        shortestLen = curLen;
    }

    if (strlen(curWord) == 0) {
        free(shortestWord);
        shortestWord = NULL;
    } 

    free(curWord);
    clean_up_word(&shortestWord, &shortestLen);
    return shortestWord;
}

/* puts in the area pointed by wordArray an array with all the unique words in the
file pointed by fp while in the area pointed by freqArray it puts an array of how
many instances of each word there are in the file, int the area pointed by wordCnt 
it puts the lenght of these arrays;
assumes that fp isn't NULL*/

void words_array_and_frequency_array(char*** wordArray, int** freqArray, int* wordCnt, FILE* fp) {

    char** wordsArray = NULL;
    int wordCount = 0;
    int* frequencyArray = NULL;

    char* curWord = malloc(sizeof(char));
    int curWordLen = 0;
    char ch;

    while ((ch = fgetc(fp)) != EOF) {

        if (ch == ' ' || ch == '\n' || ch == '\t') {

            if (curWordLen > 0) {
                int found = 0;
                curWord[curWordLen] = '\0';
                clean_up_word(&curWord, &curWordLen);
                for (int i = 0; i < wordCount && !found; i++) {
                    if (strcmp(wordsArray[i], curWord) == 0) {
                        found = 1;
                        (frequencyArray[i])++;
                    }
                }

                if (!found) {

                    wordCount++;
                    wordsArray = realloc(wordsArray, wordCount * sizeof(char*));
                    frequencyArray = realloc(frequencyArray, wordCount * sizeof(int));
                    char* temp = malloc(curWordLen +1);
                    memcpy(temp, curWord, curWordLen +1);
                    wordsArray[wordCount -1] = temp;
                    frequencyArray[wordCount -1] = 1;
                }

            
                free(curWord); // rimuovo tutti gli elementi
                curWord = malloc(sizeof(char)); // come se rifacessi curWord = malloc(1)
                curWordLen = 0;
            }

        } else { 

            curWord = realloc(curWord, (curWordLen +2) * sizeof(char));
            curWord[curWordLen] = ch;
            curWordLen++; 
        }
    }

    // check for final word
    if (curWordLen > 0) {
        int found = 0;
        curWord[curWordLen] = '\0';
        clean_up_word(&curWord, &curWordLen);
        for (int i = 0; i < wordCount && !found; i++) {
            if (strcmp(wordsArray[i], curWord) == 0) {
                found = 1;
                (frequencyArray[i])++;
            }
        }

        if (!found) {

            wordCount++;
            wordsArray = realloc(wordsArray, wordCount * sizeof(char*));
            frequencyArray = realloc(frequencyArray, wordCount * sizeof(int));
            char* temp = malloc(curWordLen +1);
            memcpy(temp, curWord, curWordLen +1);
            wordsArray[wordCount -1] = temp;
            frequencyArray[wordCount -1] = 1;
        }

            
        free(curWord); // rimuovo tutti gli elementi
        curWord = malloc(sizeof(char)); // come se rifacessi curWord = malloc(1)
        curWordLen = 0;
    }

    *wordArray = wordsArray;
    *freqArray = frequencyArray;
    *wordCnt = wordCount;
}

/* puts in the area pointed by word a version of the original string pointed by word
but with all the alphabetical characters in lowercase and without punctuation, unless
it's an apostrophe/single quote (') that is inbetween two alphanumerical characters;
assumest that in *word there aren't any space characters */

// SEGFAULT!!//
void clean_up_word(char** word, int* wordLen) {

    char* newWord = malloc((*wordLen) +1 * sizeof(char));
    int newWordLen = *wordLen;
    int j = 0;

    for (int i = 0; i < (*wordLen) && j < newWordLen; i++) {

        if (isalnum((*word)[i])) {

            newWord[j] = tolower((*word)[i]);
            j++;

            

        } else if ((*word)[i] == '\'' && (i != 0 && i +1 != (*wordLen)) && !(ispunct((*word)[i +1]))) {
            
            
            newWord[j] = (*word)[i];
            j++;
        } else newWordLen--;
    }

    newWord = realloc(newWord, newWordLen+1);
    newWord[newWordLen] = '\0';
    free(*word);
    *word = newWord;
    *wordLen = newWordLen;
}

/* returns the most frequent word in the file, if more than one words are the
most frequent, returns the first one to appear in the file, if there are no words
in the file returns NULL;
a "word" is considered a collection of alfanumeric characters separated by 
eachother with punctuation and/or spaces, with the exeption of an apostrophe
(') placed inbeetween two of the alfanum characters, the returned word is fully
in lowercase;
assumes that the file pointer fp isn't NULL*/

char *most_frequent_word(FILE *fp) {

    int wordCount;
    char** wordsArray;
    int* frequencyArray;

    words_array_and_frequency_array(&wordsArray, &frequencyArray, &wordCount, fp);

    if (wordCount == 0) return NULL;

    int highestFrequency = frequencyArray[0];
    int mostFrequentIndex = 0;
    for (int i = 0; i < wordCount; i++) {

        if (frequencyArray[i] > highestFrequency) {
            highestFrequency = frequencyArray[i];
            mostFrequentIndex = i;
        }
    }

    char* mostFrequentWord = wordsArray[mostFrequentIndex];

    for (int i = 0; i < wordCount; i++) {

        if (i != mostFrequentIndex) free(wordsArray[i]);
    }
    free(wordsArray);
    free(frequencyArray);

    return mostFrequentWord;
}

/* returns the most frequent word in the file, if more than one words are the
most frequent, returns the first one to appear in the file, if there are no words
in the file returns NULL;
a "word" is considered a collection of alfanumeric characters separated by 
eachother with punctuation and/or spaces, with the exeption of an apostrophe
(') placed inbeetween two of the alfanum characters, the returned word is fully
in lowercase;
assumes that the file pointer fp isn't NULL*/

char *least_frequent_word(FILE *fp) {

    int wordCount;
    char** wordsArray;
    int* frequencyArray;

    words_array_and_frequency_array(&wordsArray, &frequencyArray, &wordCount, fp);

    if (wordCount == 0) return NULL;
    
    int lowestFrequency = frequencyArray[0];
    int leastFrequentIndex = 0;
    for (int i = 0; i < wordCount; i++) {

        if (frequencyArray[i] < lowestFrequency) {
            lowestFrequency = frequencyArray[i];
            leastFrequentIndex = i;
        }
    }

    char* leastFrequentWord = wordsArray[leastFrequentIndex];

    for (int i = 0; i < wordCount; i++) {

        if (i != leastFrequentIndex) free(wordsArray[i]);
    }
    free(wordsArray);
    free(frequencyArray);

    return leastFrequentWord;
}