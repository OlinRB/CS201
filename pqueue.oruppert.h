//
// Created by olinr on 1/22/2022.
//

#ifndef LINKEDLIST_LISTS_ORUPPERT_H
#define LINKEDLIST_LISTS_ORUPPERT_H

#define PARTNAME_LEN 32

#define MAX_NAME_LENGTH 64
typedef struct {
    char title[MAX_NAME_LENGTH];
    char artist[MAX_NAME_LENGTH];
} Song;
typedef struct PQueueStruct {
    int priority;
    void *data;
    struct PQueueStruct *next;
} PQueueNode;

int enqueue(PQueueNode **pqueue, int priority, void *data);

void *dequeue(PQueueNode **pqueue);

void *peek(PQueueNode *pqueue);

void printQueue(PQueueNode *pqueue, void (printFunction)(void*));

int getMinPriority(PQueueNode *pqueue);

int queueLength(PQueueNode *pqueue);

void printSong(void *data);


#endif //LINKEDLIST_LISTS_ORUPPERT_H
