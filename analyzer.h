#ifndef ANALYZER_H
#define ANALYZER_H

#include <stdio.h>

// Functions to analyze a text file
int count_lines(FILE *fp);
int count_words(FILE *fp);
int count_characters(FILE *fp);

int longest_word_lenght(FILE *fp);
char *find_word_from_len(FILE *fp, int wordLen);
char *longest_word(FILE *fp);


#endif
