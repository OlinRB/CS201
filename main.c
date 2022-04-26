// jdh CS201 S22

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORDLEN 64

//--------------------------------------------------------
// return 1 if any chararacters are non-alphabetic;
// otherwise return 0

int checkWord(char *word) {
    int i, len;

    len = strlen(word);
    for (i=0; i<len; ++i) {
        if ( ! isalpha(word[i]) )
            return 1;
    }

    return 0;
}

//--------------------------------------------------------
// convert all characters to their lower-case equivalents;
// leaves characters that are already lower case unchanged
// returns zero always

int convertToLower(char *word, char *convertedWord) {
    int i, len;

    strcpy(convertedWord, word);

    len = strlen(word);
    for (i=0; i<len; ++i)
        convertedWord[i] = tolower(word[i]);

    return 0;
}

//--------------------------------------------------------

int test_tolower(char *word) {
    int len, i, val;
    char newword[MAXWORDLEN];

    len = strlen(word);
    strcpy(newword, word);
    for (i=0; i<len; ++i) {
        newword[i] = tolower(word[i]);
    }
    printf("newword is |%s|\n", newword);
    return 0;
}

//--------------------------------------------------------

int testUtils() {
    char buffer[MAXWORDLEN];
    char convertedBuffer[MAXWORDLEN];
    int rc;

    test_tolower("Nargles");

//strcpy(buffer, "nargles");
//test_tolower(buffer);

    strcpy(buffer, "John's");
    rc = checkWord(buffer);
    printf("%s: %d\n", buffer, rc);

    strcpy(buffer, "maryRose");
    rc = checkWord(buffer);
    printf("%s: %d\n", buffer, rc);
    if (rc) {
        convertToLower(buffer, convertedBuffer);
        printf("converted: |%s|\n", convertedBuffer);
    }

    strcpy(buffer, "mary Rose");
    rc = checkWord(buffer);
    printf("%s: %d\n", buffer, rc);

    return 0;
}

//-------------------------------------

int insertWord(FILE *fp, char *word) {
////    This will insert a word into the file and update the data structures in the file, as described in the explanatory
////    slides. Return zero if there are no errors; otherwise return nonzero.
////            Use the functions checkWord() and convertToLower() (see below).
    int x = 1;
    return x;
}

int countWords(FILE *fp, char letter, int *count) {
////    Count how many words are in the file that start with the specified letter. The letter parameter can be
////    upper case or lower case (all of the words in the file will have been converted to lower case). Check to see
////    though that letter is actually an alphabetic character—if it isn’t, then return 1. If any errors occur, return
////            nonzero. Otherwise, return zero and set the count parameter to the number of words in the file that start
////    with letter.
//
    int x = 1;
    return x;
}

//char **getWords(FILE *fp, char letter) {
////    Get all of the words starting with the specified letter. Return them in an array of strings (remember: in C,
////    a string can be represented as a char*). If there are n words in the file that start with the specified letter,
////    then the array returned by this function will have n+1 entries, and the last entry will be NULL.
////            The letter parameter can be upper case or lower case (all of the words in the file will have been converted
////    to lower case). Check to see though that letter is actually an alphabetic character—if it isn’t, then return
////            NULL.
////                    If there are no words starting with the specified letter, then return an array of one char*, and set the value
////    of the first element of the array to NULL. If any errors are encountered, then return NULL as the return value
////    of the function.
////            Here’s how to create a char** that has a single element that is set to NULL:
////    char **rtnval;
////    rtnval = (char **) malloc(sizeof(char *));
////    rtnval[0] = NULL;
//
//
//}


int main() {
  testUtils();
}
