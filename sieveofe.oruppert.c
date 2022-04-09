// This program find the maximum value in a global array of integers
// by creating two threads and having each thread look at half of the
// array.  After the two threads are complete and have/ each computed
// the max value in their respective region, the main() thread computes
// the max of the two partial max values.
//
// Compile this on silk this way:
// $ gcc pthreads-example.c -lpthread
//
// Unfortunately, you won't be able to run this on a Windows computer.
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


#define NUM_THREADS 5
#define NUM_NUMS 15
#define DONE = 255
#define NUM_ELEMENTS 1000
#define RANGE 1000000

void *runner(void *param);

typedef struct {
    int id;
    int lowVal;
    int highVal;
    int maxVal;
} SumStruct;

typedef struct {
    int lowerBound;
    int upperBound;
    int sVal;
    char arr[NUM_NUMS];
} SieveStruct;


void *runner(void *param) {
    SumStruct *data;
    int i, maxVal;

    data = (SumStruct *) param;

    printf("Thread number: %d\n", data->id);

    pthread_exit(NULL);
}

//--------------------------------------------------------------


// Non threaded implementation
void nonThreaded(void *param) {
    SieveStruct *sieve;
    sieve = (SieveStruct *) param;
    int done = 0;
    int startingNum = 2;
    while (!done) {
        for (int p = 0; p < NUM_NUMS; ++p) {
            printf("%d ", sieve->arr[p]);
        }
        printf("\n");
        // Find multiples of startNum
        printf("Number: %d, Multiples: ", startingNum);
        int prime = 1;
        for (int i = startingNum * 2; i <= NUM_NUMS; ++i) {
            if (i % startingNum == 0) {
                prime = 0;
                printf("%d, ", i);
                sieve->arr[i-1] = 0;
            }
        }
        // Set myNumber as completed (Mutex section)
        if (sieve->arr[startingNum-1] != 0)
            sieve->arr[startingNum-1] = -1;

        printf("\n");
        ++startingNum;
        if (startingNum == NUM_NUMS)
            done = 1;
        while (startingNum == 0)
            ++startingNum;
    }
    for (int i = 1; i <= NUM_NUMS; ++i) {
        if (sieve->arr[i] == DONE) {
            printf("%d = ", i+1);
            printf("Prime | ");
        }
    }
}


int main(int argc, char *argv[]) {
    SieveStruct sieve;

    // Create an array of char of size m
    char numberArr[NUM_NUMS];
    // Populate array with 1s
    for (int i = 0; i < NUM_NUMS; ++i) {
        sieve.arr[i] = 1;
    }
    sieve.sVal = 2;
    nonThreaded(&sieve);




//    // set up bounds for the threads
//    for (int i = 0; i < NUM_THREADS; ++i) {
//        data[i].id = i;
//    }
//
//    data[0].lowVal = 0;
//    data[0].highVal = NUM_ELEMENTS/2;
//
//    data[1].lowVal = NUM_ELEMENTS/2 + 1;
//    data[1].highVal = NUM_ELEMENTS-1;





//    // create and start the threads
//    for (i=0; i<NUM_THREADS; ++i) {
//        // create and start a child thread
//        pthread_create(&tid[i], NULL, runner, &data[i]);
//    }
//
//    // wait for the child threads to terminate
//    for (i=0; i<NUM_THREADS; ++i) {
//        pthread_join(tid[i], NULL);
//    }

//    // gather data from the individual results
//    maxVal = data[0].maxVal;
//    for (i=0; i<NUM_THREADS; ++i) {
//        if (data[i].maxVal > maxVal)
//            maxVal = data[i].maxVal;
//    }

//    printf("maximum value over the whole array is %d\n", maxVal);
    return 0;
}
