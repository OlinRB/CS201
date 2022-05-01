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

typedef struct {
    char word[1+MAXWORDLEN];
    long nextpos;
} Record;


//-------------------------------------


int setFile(FILE *fp, long locationIndex) {
    // Set to start
    fseek(fp, 0, SEEK_SET);
    int rc = fseek(fp, locationIndex, SEEK_SET);
    if (rc != 0) {
        printf("fseek() failed\n");
        fclose(fp);
        return rc;
    }
    return rc;
}

void printFileData(FILE *fp) {
    // Set file to beginning
    setFile(fp, 0);
    printf("\n----READING DATA------\n");
    long iterator = 0;
    int filesize = checkFileSize(fp);
    char tempWord[MAXWORDLEN + 1];
    long ptr = 0;
    long data;
    long value;
    // Seek to beginning
    setFile(fp, 0);
    for (int i=0; i<26; ++i) {
        int num = fread(&value, sizeof(long), 1, fp);
        if (num == 1) {
            printf("read this value: %ld\n", value);
        } else {
            printf("ERROR: fread() failed to read a value\n");
            fclose(fp);
            //return 8;
        }
    }
    iterator = sizeof(long) * NUMVALS;
    // get filesize
    filesize = checkFileSize(fp);
    setFile(fp, 0);

    // With struct
    Record inputRecord;

    // In while loop
    int fileIndex = 208;
    setFile(fp, 208);
    while (fileIndex < filesize) {
        fread(&inputRecord, sizeof(Record), 1, fp);
        printf("Word read: | %s |, ptr = %ld\n", inputRecord.word, inputRecord.nextpos);
        fileIndex += 40;
    }
}

int insertWord(FILE *fp, char *word) {
////    This will insert a word into the file and update the data structures in the file, as described in the explanatory
////    slides. Return zero if there are no errors; otherwise return nonzero.
////            Use the functions checkWord() and convertToLower() (see below).
    // Determine where to jump in first 208 bytes of file
    char alpha[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                      'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int success = 0;
    // Change to lower case
    char convertedWord[MAXWORDLEN+1];
    convertToLower(word, convertedWord);
    // Determine where to write file
    Record newWord;
    strcpy(newWord.word, convertedWord);
    char firstLetter = word[0];

    // Get letter index
    long letterIndex;
    for (int i = 0; i < 26; ++i) {
        if (firstLetter == alpha[i])
            letterIndex = i * sizeof (long);
    }

    // file already exists; read long value at specified index
    // Seek to beginning of file
    setFile(fp, 0);

    // Seek to location
    setFile(fp, letterIndex);
    long value;

    long num = fread(&value, sizeof(long), 1, fp);
    // If num == 1 read was successful
    if (num == 1) {
        if (value == 0) {
            // Write word to end of file and replace 0 with byte location
            int filesize = checkFileSize(fp);
            // Go to end of file to write word
            setFile(fp, filesize);
            // Use struct instead and assume pointer is 0
            newWord.nextpos = 0;
            num += fwrite(&newWord, sizeof(Record), 1, fp);

            // Now write starting location of word at letter location within first 26 bytes
            setFile(fp, letterIndex);
            long wordStarts = filesize;
            num += fwrite(&wordStarts, sizeof(long), 1, fp);
            // Set file back to start
            setFile(fp, 0);

            if (num != 3)
                printf("Error on write\n");

        } else {
            // There is already a word with such a letter
            // Seek to this word to read in the next pointer (if it exists)
            // Seek to value
            setFile(fp, value);
            Record storedWord;
            fread(&storedWord, sizeof(storedWord), 1, fp);
            // If pointer is zero add word to end of file
            if (storedWord.nextpos == 0) {
                long filesize = checkFileSize(fp);
                setFile(fp, 0);
                // seek to end of file
                setFile(fp, filesize);
                // Write to end of file
                newWord.nextpos = 0;
                fwrite(&newWord, sizeof(Record), 1, fp);
                // Update pointer on first word to point to next word
                setFile(fp, 0);
                setFile(fp, value + 32);
                fwrite(&filesize, sizeof(long), 1, fp);
                //printf("\nDuplicate first letter word written starting at %ld\n", filesize);
                //printf("First word |%s| second word |%s|", newWord.word, "test");
            } else {
                // if pointer is not zero, must traverse linked list ptr == 0
                // Seek to value
                setFile(fp, value);
                Record tempRecord;
                long prevPos;
                int read = fread(&tempRecord, sizeof(Record), 1, fp);
                //printf("First word is |%s| -> |%ld|", tempRecord.word,tempRecord.nextpos);
                while (tempRecord.nextpos != 0 && read == 1) {

                    // set to new position
                    setFile(fp, tempRecord.nextpos);
                    prevPos = tempRecord.nextpos;
                    fread(&tempRecord, sizeof(Record), 1, fp);
                }
                long filesize = checkFileSize(fp);
                //printf("\nFilesize = %ld\n", filesize);
                // Write pointer to last word with identical letter
                setFile(fp, prevPos + sizeof(Record));
                fwrite(&filesize, sizeof(long), 1, fp);

                // Now write new word to end of file
                setFile(fp, filesize);
                newWord.nextpos = 0;
                fwrite(&newWord, sizeof(Record), 1, fp);
            }
        }

    } else {
        printf("Read not successful");
        success = 1;
    }

    return success;

}

int countWords(FILE *fp, char letter, int *count) {
////    Count how many words are in the file that start with the specified letter. The letter parameter can be
////    upper case or lower case (all of the words in the file will have been converted to lower case). Check to see
////    though that letter is actually an alphabetic character—if it isn’t, then return 1. If any errors occur, return
////            nonzero. Otherwise, return zero and set the count parameter to the number of words in the file that start
////    with letter.

    // Get letter index
    char alpha[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                      'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    *count = 0;
    int wordCnt = 0;
    // Get letter index
    long letterIndex;
    // Check if char is char
    if (isalpha(letter) == 0)
        return 1;
    // Set char to lower case
    char lowLetter = tolower(letter);

    // Find letter index
    for (int i = 0; i < 26; ++i) {
        if (lowLetter == alpha[i])
            letterIndex = i * sizeof (long);
    }

    // Check if file exists
    int fileExists = 0;
    fp = fopen(FILENAME, "r+"); // r+ means read and write access, for a file
    if (fp == NULL) {           // that already exists
        printf("ERROR -> File does not exist\n", FILENAME);
        return 1;
    }

    // Seek to location
    setFile(fp, letterIndex);
    long value;

    long num = fread(&value, sizeof(long), 1, fp);
    // If num == 1 read was successful
    if (num == 1) {
        // Case for no words with starting letter in file
        if (value == 0) {
            return 0;
        } else {
            // Case for at least one word in file, read in until ptr == 0
            *count += 1;
            setFile(fp, value);
            Record tempRecord;
            fread(&tempRecord, sizeof(Record), 1, fp);
            while (tempRecord.nextpos != 0) {
                // set to new position
                setFile(fp, tempRecord.nextpos);
                fread(&tempRecord, sizeof(Record), 1, fp);
                *count += 1;
            }
        }
    }
    return 0;
}

char **getWords(FILE *fp, char letter) {
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

    // Get number of items with specificed letter to initialize array
    // Declare array
    int wordCnt;
    char **wordArr;
    int cnt = countWords(fp, letter, &wordCnt);
    wordArr = (char **) malloc((wordCnt + 1) * sizeof(char *));
    if (cnt != 0) {
        wordArr[0] = NULL;
        return wordArr;
    }
    // Get letter index
    char alpha[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                      'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    long letterIndex;

    // Set char to lower case
    char lowLetter = tolower(letter);

    // Find letter index
    for (int i = 0; i < 26; ++i) {
        if (lowLetter == alpha[i])
            letterIndex = i * sizeof (long);
    }

    // Check if file exists
    int fileExists = 0;
    fp = fopen(FILENAME, "r+"); // r+ means read and write access, for a file
    if (fp == NULL) {           // that already exists
        printf("ERROR -> File does not exist\n", FILENAME);
        wordArr[0] = NULL;
        return wordArr;
    }

    // Seek to location
    setFile(fp, letterIndex);
    long value;

    long num = fread(&value, sizeof(long), 1, fp);
    // If num == 1 read was successful
    if (num == 1) {
        // Case for no words with starting letter in file
        if (value == 0) {
            wordArr[0] = NULL;
            printf("val == 0");
            return wordArr;
        } else {
            // Case for at least one word in file, read in until ptr == 0
            setFile(fp, value);
            Record tempRecord;
            fread(&tempRecord, sizeof(Record), 1, fp);
            int i = 0;
            char *word;
            word = (char *) malloc((MAXWORDLEN + 1) * sizeof(char));
            strncpy(word, tempRecord.word, MAXWORDLEN+1);
            wordArr[i] = word;
            while (tempRecord.nextpos != 0) {
                word = (char *) malloc((MAXWORDLEN + 1) * sizeof(char));
                // set to new position
                setFile(fp, tempRecord.nextpos);
                fread(&tempRecord, sizeof(Record), 1, fp);
                i += 1;
                strncpy(word, tempRecord.word, MAXWORDLEN+1);
                wordArr[i] = word;

            }
            return wordArr;
        }
    }
    return wordArr;


}

int testFileFunctions() {
////    Try a simple test first, where you insert a single word, starting with ‘n’ for example. Count how many words
////    start with ‘n’ (there should be one). Count how many words start with ‘a’ (there should be zero). Examine
////    your file using od.
////            Then, delete the file and make a new testcase: insert a word starting with ‘n’, and then a word starting
////    with ‘a’, and then another word starting with ‘n’. Examine your file using od, and use the functions you’ve
////    written to be sure you’re seeing the correct results.
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
            num = fwrite(&value, sizeof(long), 1, fp);
            if (num != 1) {
                printf("ERROR: fwrite() failed to write a value\n");
                fclose(fp);
                return 8;
            } else {
                //printf("success: wrote the value %ld\n", value);
            }
        }

    }

    int testPassed = 0;

    // Write word to file
    insertWord(fp, "nardles");
    // Test word count and words with n
    int cnt;
    char testLetter = 'n';
    countWords(fp, testLetter, &cnt);
    //printf("\nThere are %d words with the letter %c\n", cnt, testLetter);
    if (cnt != 1)
        testPassed = 1;
    else
        printf("\nPASSED letter count with %c\n", testLetter);
    cnt = 0;
    testLetter = 'a';
    countWords(fp, testLetter, &cnt);
    if (cnt != 0)
        testPassed = 1;
    else
        printf("\nPASSED letter count with %c\n", testLetter);

    // Insert more words and test return array
    insertWord(fp, "middle");
    insertWord(fp, "node");
    insertWord(fp, "next");
    insertWord(fp, "march");
    insertWord(fp, "NOOdles");
    printFileData(fp);
    char **stringArr;
    cnt = 0;
    testLetter = 'n';
    countWords(fp, testLetter, &cnt);
    if (cnt != 3)
        testPassed = 1;
    else
        printf("\nPASSED letter count with %c\n", testLetter);

    stringArr = getWords(fp, testLetter);
    i = 0;
    char testArr[3][32] = {{"nardles"}, {"node"}, {"next"}};
    printf("\nPrinting words from returned array:\n");
    while (stringArr[i] != NULL) {
        printf("Return word[%d] is |%s|, expected result: |%s|\n", i, stringArr[i], testArr[i]);
        if ((strcmp(testArr[i], stringArr[i])))
            testPassed = 1;
        i += 1;
    }
    if (!testPassed)
        printf("\nPassed return array test\n");
    //printFileData(fp);

    return testPassed;
}


int main() {
    testFileFunctions();

    //testUtils();

}
