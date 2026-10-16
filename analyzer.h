#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdio.h>

// Functions to analyze a text file
int count_lines(FILE *fp);
int count_words(FILE *fp);
int count_characters(FILE *fp);

char *longest_word(FILE *fp);
char *shortest_word(FILE *fp);

void words_array_and_frequency_array(char*** wordArray, int** freqArray, int* wordCnt, FILE* fp);
void clean_up_word(char** word, int* wordLen);

char *most_frequent_word(FILE *fp);
char *least_frequent_word(FILE *fp);

#endif
