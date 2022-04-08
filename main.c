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
#define NUM_ELEMENTS 1000
#define RANGE 1000000

void *runner(void *param);

typedef struct {
    int id;
    int lowVal;
    int highVal;
    int maxVal;
} SumStruct;

int A[NUM_ELEMENTS];

//-----------------------------------------------------------------
// This is the function that computers the max over a range of the
// global array A[]. The SumStruct passed through param tells this
// function over which values to do the max.

void *runner(void *param) {
    SumStruct *data;
    int i, maxVal;

    data = (SumStruct *) param;

//    printf("(R) I am runner; will do max for the range %d to %d\n",
//           data->lowVal, data->highVal);
//
//    maxVal = A[data->lowVal];
//    for (i=data->lowVal; i<=data->highVal; ++i) {
//        if (A[i] > maxVal)
//            maxVal = A[i];
//    }
//
//    data->maxVal = maxVal;
//
//    printf("(R) max is %d\n", data->maxVal);
    printf("Thread number: %d\n", data->id);

    pthread_exit(NULL);
}

//--------------------------------------------------------------

int main(int argc, char *argv[]) {
    SumStruct data[NUM_THREADS];   // holds data we want to give to child thread
    pthread_t tid[NUM_THREADS];    // thread identifier
    int maxVal;
    int i;

    // initialize the array with random integers in the range 0..NUM_ELEMENTS
    for (i=0; i<NUM_ELEMENTS; ++i)
        A[i] = (int) RANGE * drand48();

    // set up bounds for the threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        data[i].id = i;
    }

    data[0].lowVal = 0;
    data[0].highVal = NUM_ELEMENTS/2;

    data[1].lowVal = NUM_ELEMENTS/2 + 1;
    data[1].highVal = NUM_ELEMENTS-1;

    // create and start the threads
    for (i=0; i<NUM_THREADS; ++i) {
        // create and start a child thread
        pthread_create(&tid[i], NULL, runner, &data[i]);
    }

    // wait for the child threads to terminate
    for (i=0; i<NUM_THREADS; ++i) {
        pthread_join(tid[i], NULL);
    }

    // gather data from the individual results
    maxVal = data[0].maxVal;
    for (i=0; i<NUM_THREADS; ++i) {
        if (data[i].maxVal > maxVal)
            maxVal = data[i].maxVal;
    }

//    printf("maximum value over the whole array is %d\n", maxVal);
    return 0;
}
