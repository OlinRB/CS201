// jdh CS201 S22

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORDLEN 31
#define NUMVALS 26
#define FILENAME "words_file.dat"

//--------------------------------------------------------
// return 1 if any chararacters are non-alphabetic;
// otherwise return 0

long checkFileSize(FILE *fp) {
    int rc;
    long filesize;

    rc = fseek(fp, 0, SEEK_END);
    if (rc != 0) {
        printf("fseek() failed\n");
        return -1;
    }

    filesize = ftell(fp);
    return filesize;
}

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

int testFileFunctions() {
////    Try a simple test first, where you insert a single word, starting with ‘n’ for example. Count how many words
////    start with ‘n’ (there should be one). Count how many words start with ‘a’ (there should be zero). Examine
////    your file using od.
////            Then, delete the file and make a new testcase: insert a word starting with ‘n’, and then a word starting
////    with ‘a’, and then another word starting with ‘n’. Examine your file using od, and use the functions you’ve
////    written to be sure you’re seeing the correct results.

}

//-------------------------------------


typedef struct {
    char word[1+MAXWORDLEN];
    long long nextpos;
} Record;

//int getStartingIndex(FILE *fp, int position) {
//    // I know that all of the values in the file are longs
//    numValuesToRead = filesize / sizeof(long long);
//    printf("expect to read %d long values\n", numValuesToRead);
//
//    for (int i = 0; i < numValuesToRead; ++i) {
//        num = fread(&value, sizeof(long long), 1, fp);
//        if (num == 1) {
//            printf("read this value: %ld\n", value);
//        } else {
//            printf("ERROR: fread() failed to read a value\n");
//            fclose(fp);
//            return 8;
//        }
//    }
//
//};

int insertWord(FILE *fp, Record *word) {
////    This will insert a word into the file and update the data structures in the file, as described in the explanatory
////    slides. Return zero if there are no errors; otherwise return nonzero.
////            Use the functions checkWord() and convertToLower() (see below).
    // Determine where to jump in first 208 bytes of file
    char alpha[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                      'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    // Determine where to write file
    char firstLetter = word->word[0];
    int letterIndex;
    for (int i = 0; i < 26; ++i) {
        if (firstLetter == alpha[i])
            letterIndex = i * sizeof (long long);
    }
    printf("The starting letter index is: %d", letterIndex);

    // Now read file at position to see if word with letter exists in file yet





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
    // Open or create file
    FILE *fp;
    int fileExists, rc, i, num, numRead, numValuesToRead;
    long filesize, value, pos;

    // try to open a file
    // - if the file exists, we'll be able to access it
    // - if the file does not exist, then create it

    fileExists = 0;
    fp = fopen(FILENAME, "r+"); // r+ means read and write access, for a file
    if (fp != NULL) {           // that already exists
        printf("success, file '%s' already exists\n", FILENAME);
        fileExists = 1;
    }

    if ( ! fileExists ) {
        fp = fopen(FILENAME, "w+");  // w+ means read and write access, for a file
        if (fp == NULL) {            // that does not exist
            printf("ERROR: cannot open file '%s'\n", FILENAME);
            return 8;
        } else {
            printf("success, created new file '%s'\n", FILENAME);
        }
    }
    //printf("%d",fileExists);
//    Try a simple test first, where you insert a single word, starting with ‘n’ for example. Count how many words
//    start with ‘n’ (there should be one). Count how many words start with ‘a’ (there should be zero). Examine
//    your file using od.
//            Then, delete the file and make a new testcase: insert a word starting with ‘n’, and then a word starting
//    with ‘a’, and then another word starting with ‘n’. Examine your file using od, and use the functions you’ve
//    written to be sure you’re seeing the correct results.

    // Check file size
    filesize = checkFileSize(fp);
    if (filesize < 0) {
        printf("ERROR: checkFileSize() failed\n");
        fclose(fp);
        return 8;
    }
    printf("current size of file is %ld bytes\n", filesize);
    // If file size == 0, Add longs to start of file (26)
    // if the file is empty, then write 5 long values
    if (filesize == 0) {
        // don't need to seek to the beginning: already there, since file is empty
        value = 0;
        for (i = 0; i < NUMVALS; ++i) {
            num = fwrite(&value, sizeof(long long), 1, fp);
            if (num != 1) {
                printf("ERROR: fwrite() failed to write a value\n");
                fclose(fp);
                return 8;
            } else {
                printf("success: wrote the value %ld\n", value);
            }
        }

    }

    // Save word and next pos to struct
    Record word1;
    strcpy(word1.word, "nardles");
    word1.nextpos = 0;

    // Write word to file
    insertWord(fp, &word1);

    //testUtils();

}
