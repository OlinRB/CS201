//
// Created by olinr on 1/22/2022.
//

#include "lists.oruppert.h"
#include "includes.h"

int insertPart(PartRecord **theList, int partNumber, int quantity, char *partName){
    PartRecord *curr = *theList;
    PartRecord *prev = curr;

    int start;
    if (theList != NULL)
        start = 0;
    else {
        return 1;
    }
    while (curr != NULL || start == 0) {
        start = 1;
        // Look for items location
        // Return if duplicate
        if (curr->partNumber == partNumber)
            return 1;
        if (curr->partNumber < partNumber && curr->next->partNumber > partNumber) {
            PartRecord *newRecord = malloc(sizeof(PartRecord));
            newRecord->partNumber = partNumber;
            newRecord->quantity = quantity;
            strcpy(curr->partName, partName);
            prev->next = newRecord;
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }

    return 1;

}

int deletePart(PartRecord **theList, int partNumber){
    PartRecord *curr = *theList;
    PartRecord *prev;
    PartRecord *next;
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
        while (curr->next != NULL) {
            printf("Number = %d, quantity = %d, name = |%s|\n", curr->partNumber, curr->quantity, curr->partName);
            curr = curr->next;
        }
    }
}