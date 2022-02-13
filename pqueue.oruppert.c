//
// Created by olinr on 1/22/2022.
//

#include "pqueue.oruppert.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int enqueue(PQueueNode **pqueue, int priority, void *data) {
    if (pqueue == NULL)
        return 1;
    PQueueNode *curr = *pqueue;
    PQueueNode *prev = NULL;
    PQueueNode *next;
    if (curr == NULL) {
        curr = malloc(sizeof(PQueueNode));
        curr->priority = priority;
        curr->data = data;
        curr->next = NULL;
        *pqueue = (PQueueNode *)curr;
        return 0;
    }
    else {
        bool head = false;
        bool foundPlacement = false;
        if (curr->priority > priority) {
            next = curr;
            head = true;
        } else {
            while (curr != NULL && !foundPlacement) {
                if (curr->priority > priority) {
                    foundPlacement = true;
                    next = curr;
                } else {
                    prev = curr;
                    next = NULL;
                }
                curr = curr->next;
            }
        }
        PQueueNode *newQueue = malloc(sizeof(PQueueNode));
        newQueue->priority = priority;
        newQueue->data = data;
        newQueue->next = next;
        if (!head)
            prev->next = newQueue;
        else {
            // Assign new node to head of queue
            *pqueue = (PQueueNode *) newQueue;
        }
        return 0;
    }
    return 1;
}

void *dequeue(PQueueNode **pqueue) {
    if (pqueue == NULL)
        return NULL;
    PQueueNode *curr = *pqueue;
    Song *song = curr->data;
    *pqueue = curr->next;
    //free(pqueue);
    return song;


}

void *peek(PQueueNode *pqueue) {
    if (pqueue == NULL)
        return NULL;
    PQueueNode *curr = pqueue;
    Song *song = curr->data;
    return song;
}

void printSong(void *data) {
    Song *song;
    song = (Song *) data;
    printf("\"");
    printf("%s", song->title);
    printf("\"");
    printf(" (");
    printf("%s", song->artist);
    printf(")");
    printf("\n");
}

//-------------------------------------------------------

void printQueue(PQueueNode *pqueue, void (printFunction)(void *)) {
    PQueueNode *qnode;

    qnode = pqueue;
    while (qnode != NULL) {
        printf("Priority = ");
        printf("%d",qnode->priority);
        printf(" Data = ");
        printFunction(qnode->data);
        qnode = qnode->next;
    }
}


int getMinPriority(PQueueNode *pqueue) {
    if (pqueue == NULL)
        return -1;
    return pqueue->priority;
}

int queueLength(PQueueNode *pqueue) {
    PQueueNode *curr = pqueue;
    int cnt = 0;
    while (curr != NULL) {
        ++cnt;
        curr = curr->next;
    }
    return cnt;
}

