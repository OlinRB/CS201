//
// Created by olinr on 1/22/2022.
//

#include "lists.oruppert.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int insertPart(PartRecord **theList, int partNumber, int quantity, char *partName){
    if (theList == NULL)
        return 1;
    PartRecord *curr = *theList;
    PartRecord *prev;
    PartRecord *next;
    if (curr == NULL) {
        curr = malloc(sizeof(PartRecord));
        curr->partNumber = partNumber;
        curr->quantity = quantity;
        strcpy(curr->partName, partName);
        curr->next = NULL;
        *theList = (PartRecord *)curr;
        return 0;
    }
    else {
        bool head = false;
        bool duplicate = false;
        if (curr->partNumber > partNumber) {
            next = curr;
            head = true;
        } else {
            while (curr != NULL) {
                // Append to the end of list and Middle
                if (curr->partNumber == partNumber) {
                    duplicate = true;
                    return 1;
                }
                if (curr->partNumber > partNumber) {
                    next = curr;
                }
                else {
                    prev = curr;
                    next = NULL;
                }
                curr = curr->next;
            }
        }
        if (!duplicate) {
            PartRecord *newPart = malloc(sizeof(PartRecord));
            newPart->partNumber = partNumber;
            newPart->quantity = quantity;
            strcpy(newPart->partName, partName);
            newPart->next = next;
            if (!head)
                prev->next = newPart;
            else {
                // Assign new node to start of list
                *theList = (PartRecord *) newPart;
            }
        }
        return 0;
    }
    return 1;

}

int deletePart(PartRecord **theList, int partNumber){
    if (theList == NULL)
        return 1;
    PartRecord *curr = *theList;
    PartRecord *prev;
    PartRecord *next;
    // If first item to be deleted
    if (curr->partNumber == partNumber) {
        *theList = (PartRecord *) curr->next;
        free(curr);
        return 0;
    }
    if (curr != NULL) {
        while (curr != NULL) {
            if (curr->partNumber == partNumber) {
                prev->next = curr->next;
                free(curr);
                return 0;
            }
            prev = curr;
            curr = curr->next;
        }
    }
    return 1;



}

PartRecord *findPart(PartRecord *theList, int partNumber){
    PartRecord *curr = theList;
    if (curr != NULL) {
        while (curr != NULL) {
            if (curr->partNumber == partNumber) {
                return curr;
            }
            curr = curr->next;
        }
    }
    return NULL;
}

void printParts(PartRecord *theList) {
    if (theList != NULL) {
        PartRecord *curr = theList;
        while (curr != NULL) {
            printf("Number = %d, quantity = %d, name = |%s|\n", curr->partNumber, curr->quantity, curr->partName);
            curr = curr->next;
        }
    }
}

int freeMem(PartRecord *theList) {
    if (theList == NULL)
        return 0;
    PartRecord *temp;
    while (theList != NULL) {
        temp = theList;
        theList = theList->next;
        free(temp);
    }
    free(theList);
    return 0;
}