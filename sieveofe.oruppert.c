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
#define NUM_NUMS 20
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

int A[NUM_ELEMENTS];

//-----------------------------------------------------------------
// This is the function that computers the max over a range of the
// global array A[]. The SumStruct passed through param tells this
// function over which values to do the max.

void *runner(void *param) {
    SumStruct *data;
    int i, maxVal;

    data = (SumStruct *) param;

    printf("Thread number: %d\n", data->id);

    pthread_exit(NULL);
}

//--------------------------------------------------------------


// Non threaded implementation
void nonThreaded(char *numArr) {
    char arr[NUM_NUMS];
    arr = (char[] *) numArr;
    for (int i = 0; i < NUM_NUMS; ++i) {
        printf("%d ", arr[i]);
    }
}


int main(int argc, char *argv[]) {
    SumStruct data[NUM_THREADS];   // holds data we want to give to child thread
    pthread_t tid[NUM_THREADS];    // thread identifier
    int maxVal;
    int i;

    // Create an array of char of size m
    char numberArr[NUM_NUMS];
    // Populate array with 1s
    for (int i = 0; i < NUM_NUMS; ++i) {
        numberArr[i] = 1;
    }
    nonThreaded(numberArr);
    // set up bounds for the threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        data[i].id = i;
    }

    data[0].lowVal = 0;
    data[0].highVal = NUM_ELEMENTS/2;

    data[1].lowVal = NUM_ELEMENTS/2 + 1;
    data[1].highVal = NUM_ELEMENTS-1;





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

    // gather data from the individual results
    maxVal = data[0].maxVal;
    for (i=0; i<NUM_THREADS; ++i) {
        if (data[i].maxVal > maxVal)
            maxVal = data[i].maxVal;
    }

//    printf("maximum value over the whole array is %d\n", maxVal);
    return 0;
}
