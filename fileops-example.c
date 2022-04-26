// jdh CS201 April 2022
// example of file operations on binary files
//
// The first time you run this, it will create the file "newfile.dat"
// and write five long integers (0, 2, 4, 6, 8) into the file and
// then exit.
//
// Subsequent times that you run this, it will check the size of the file,
// determine how many long integers there are, and then read them in order.
// Then, it will seek to the start of one of the middle integers in the
// sequence of integers.

#include <stdio.h>

#define FILENAME "newfile.dat"
#define NUMVALS 5

//--------------------------------------------------
// a helper function

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

//--------------------------------------------------

int main() {
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

    // now see how big the file is
    filesize = checkFileSize(fp);
    if (filesize < 0) {
        printf("ERROR: checkFileSize() failed\n");
        fclose(fp);
        return 8;
    }

    printf("current size of file is %ld bytes\n", filesize);

    // if the file is empty, then write 5 long values
    if (filesize == 0) {
        // don't need to seek to the beginning: already there, since file is empty
        value = 0;
        for (i=0; i<NUMVALS; ++i) {
            num = fwrite(&value, sizeof(long), 1, fp);
            if (num != 1) {
                printf("ERROR: fwrite() failed to write a value\n");
                fclose(fp);
                return 8;
            } else {
                printf("success: wrote the value %ld\n", value);
            }

            value = value + 2;
        }
    } else {
        // file already exists; read long values until there aren't any more
        // must first seek to the beginning
        rc = fseek(fp, 0, SEEK_SET);
        if (rc != 0) {
            printf("fseek() failed\n");
            fclose(fp);
            return rc;
        }

        // check how big the file is

        filesize = checkFileSize(fp);
        if (filesize < 0) {
            printf("ERROR: checkFileSize() failed\n");
            fclose(fp);
            return 8;
        }

        // must seek back to the beginning
        rc = fseek(fp, 0, SEEK_SET);
        if (rc != 0) {
            printf("fseek() failed\n");
            fclose(fp);
            return rc;
        }

        // I know that all of the values in the file are longs
        numValuesToRead = filesize / sizeof(long);
        printf("expect to read %d long values\n", numValuesToRead);

        for (i=0; i<numValuesToRead; ++i) {
            num = fread(&value, sizeof(long), 1, fp);
            if (num == 1) {
                printf("read this value: %ld\n", value);
            } else {
                printf("ERROR: fread() failed to read a value\n");
                fclose(fp);
                return 8;
            }
        }

        // now, seek to the one of the middle values
        if (numValuesToRead >= 4) {
            pos = (numValuesToRead / 2) * sizeof(long);
            printf("will seek to position %ld and read a value\n", pos);

            rc = fseek(fp, pos, SEEK_SET);
            if (rc != 0) {
                printf("fseek() to pos %ld failed\n", pos);
                fclose(fp);
                return rc;
            }

            num = fread(&value, sizeof(long), 1, fp);
            if (num == 1) {
                printf("read this value: %ld\n", value);
            } else {
                printf("ERROR: fread() failed to read a value\n");
                fclose(fp);
                return 8;
            }
        }
    }

    fclose(fp);

    return 0;
}

