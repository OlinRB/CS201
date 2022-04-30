#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// example program that takes an input string consisting of
// separate words and returns an array of strings consisting
// of each of the words in the string

char **fetchStrings(char *input) {
    int i, index, start, len, wordCount, wordLen;
    char **rtnval, *word;

    // first count how many words there are
    wordCount = 0;
    len = strlen(input);
    i = 0;
    while (i < len) {
        while (i < len && input[i] == ' ')
            i = i + 1;
        if (i < len) {
            // found the start of a word
            ++wordCount;
            while (i < len && input[i] != ' ')
                i = i + 1;
        }
    }

    printf("count = %d\n", wordCount);

    rtnval = (char **) malloc((1+wordCount) * sizeof(char *));

    if (wordCount == 0) {
        // degenerate case: no words
        rtnval[0] = NULL;
        return rtnval;
    }

    // now go through again and pick out words
    i = 0;
    index = 0;
    while (i < len) {
        while (i < len && input[i] == ' ')
            i = i + 1;
        if (i < len) {
            // found the start of a word
            start = i;
            while (i < len && input[i] != ' ')
                i = i + 1;
            //printf("from pos %d to %d\n", start, i-1);
            wordLen = i-start;
            word = (char *) malloc((wordLen + 1) * sizeof(char));
            strncpy(word, &input[start], wordLen);
            word[wordLen] = '\0';
            //printf("word is |%s|\n", word);
            rtnval[index] = word;
            index = index + 1;
        }
    }

    rtnval[index] = NULL;
    return rtnval;
}

int test(char *input) {
    char **strings;
    int i;
    printf("input is |%s|\n", input);
    strings = fetchStrings(input);
    i = 0;
    while (strings[i] != NULL) {
        printf("word[%d] is |%s|\n", i, strings[i]);
        i = i + 1;
    }
    return 0;
}

int main() {
    test("  now  is    the time ");
//    test("now  is the time");
//    test("");
//    test("  ");
//    test(" cat  ");


    return 0;
}


