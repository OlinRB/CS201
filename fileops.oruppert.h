//
// Created by Mason Landis on 4/30/22.
//

#ifndef CS201_FILEOPS_ORUPPERT_H
#define CS201_FILEOPS_ORUPPERT_H

#define MAXWORDLEN 31
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char word[1+MAXWORDLEN];
    long nextpos;
} Record;


int insertWord(FILE *fp, char *word);

int countWords(FILE *fp, char letter, int *count);

char **getWords(FILE *fp, char letter);

int convertToLower(char *word, char *convertedWord);

int checkWord(char *word);

#endif //CS201_FILEOPS_ORUPPERT_H
