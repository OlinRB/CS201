// This program find the maximum value in a global array of integers
// by creating two threads and having each thread look at half of the
// array.  After the two threads are complete and have/ each computed
// the max value in their respective region, the main() thread computes
// the max of the two partial max values.
//
// Compile this on silk this way:
// $ gcc sieveofe.oruppert.c -lpthread
//
// Unfortunately, you won't be able to run this on a Windows computer.
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


#define NUM_THREADS 3
#define NUM_NUMS 10
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
    pthread_mutex_t mutex;
    int lowerBound;
    int upperBound;
    int sVal;
    char arr[NUM_NUMS];
} SieveStruct;


void *threadedSieve(void *param) {
    printf("Thread here\n");
    SieveStruct *sieve;
    sieve = (SieveStruct *) param;
    int done = 0;
    int startingNum = sieve->sVal;
    pthread_mutex_t mutex = sieve->mutex;
    //printf("%d\n", startingNum);
    while (!done) {
        // Set starting num
        while (sieve->arr[startingNum-1] == -1 || sieve->arr[startingNum-1] == 0) {
            ++startingNum;
            if (startingNum > NUM_NUMS-1)
                done = 1;
        }
//        for (int p = 0; p < NUM_NUMS; ++p) {
//            printf("%d ", sieve->arr[p]);
//        }
//        printf("\n");
        // Find multiples of startNum
        //printf("Number: %d, Multiples: ", startingNum);
        int prime = 1;
        for (int i = startingNum * 2; i <= NUM_NUMS; ++i) {
            if (i % startingNum == 0) {
                prime = 0;
                //printf("%d, ", i);
                sieve->arr[i-1] = 0;
            }
        }
        // Set myNumber as completed (Mutex section)

        int val = pthread_mutex_lock(&mutex);
        while (val != 0)
            val = pthread_mutex_trylock(&mutex);
        //printf("%d", val);
        if (sieve->arr[startingNum-1] != 0) {
            sieve->arr[startingNum - 1] = -1;
        }
        pthread_mutex_unlock(&mutex);
        //printf("\n");
        ++startingNum;
        if (startingNum == NUM_NUMS)
            done = 1;
        while (startingNum == 0)
            ++startingNum;
    }


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
}


void *mutexTest(void * param) {
    printf("Boss here\n");
    SieveStruct *sieve;
    sieve = (SieveStruct *) param;
    int done = 0;
    int startingNum = sieve->sVal;
    pthread_mutex_t mutex = sieve->mutex;

    // Lock for 10 seconds and then work
    pthread_mutex_lock(&mutex);

    printf("Waiting for 10 seconds\n");
    sleep(10);

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);

}

int main(int argc, char *argv[]) {
    // Create Struct
    SieveStruct sieve;
    // Create Mutex
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    // Add mutex to sieve
    sieve.mutex = mutex;
    // Create an array of char of size m
    char numberArr[NUM_NUMS];
    // Populate array with 1s
    for (int i = 0; i < NUM_NUMS; ++i) {
        sieve.arr[i] = 1;
    }
    sieve.sVal = 2;
    //nonThreaded(&sieve);

    // Create array of threads

    pthread_t boss;
    pthread_create(&boss, NULL, mutexTest, &sieve);
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, threadedSieve, &sieve);
    }
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Print out primes
    printf("\n");
    for (int i = 1; i <= NUM_NUMS; ++i) {
        if (sieve.arr[i] == -1) {
            printf("%d = ", i+1);
            printf("Prime | ");
        }
    }

    return 0;
}
