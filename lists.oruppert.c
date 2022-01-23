//
// Created by olinr on 1/22/2022.
//

#include "lists.oruppert.h"
#include "includes.h"

int insertPart(PartRecord **theList, int partNumber, int quantity, char *partName){
    if (theList == NULL)
        return 1;

    PartRecord *curr = *theList;
    PartRecord *prev;

    if (curr == NULL) {
        curr = malloc(sizeof(PartRecord));
        curr->partNumber = partNumber;
        curr->quantity = quantity;
        strcpy(curr->partName, partName);
        curr->next = NULL;
        *theList = (PartRecord *)curr;
    }
    else {
        bool addPart = false;

        while (curr != NULL) {
            prev = curr;
            if (curr->partNumber < partNumber && curr->next == NULL)
                addPart = true;
            else {
                if (curr->partNumber < partNumber && curr->next->partNumber > partNumber)
                    curr->partNumber;
                    addPart = true;
            }
            curr = curr->next;
            if (addPart) {
                PartRecord *newPart = malloc(sizeof (PartRecord));
                newPart->partNumber = partNumber;
                newPart->quantity = quantity;
                strcpy(newPart->partName, partName);
                newPart->next = NULL;
                prev->next = newPart;
            }
        }
    }


//    PartRecord *curr = *theList;
//    bool addPart;
//    // If theList points to nothing assign starting node
//    if (curr == NULL) {
//        curr = malloc(sizeof(PartRecord));
//        curr->next = NULL;
//        addPart = true;
//        *theList = curr;
//    }
//
//    PartRecord *prev = curr;
//
//    while (curr != NULL) {
//        // Look for items location
//        // Return if duplicate
//        if (curr->partNumber == partNumber)
//            return 1;
//        if (curr->partNumber < partNumber) {
//            if (!(curr->next == NULL))
//                if (curr->next->partNumber > partNumber)
//                    addPart = true;
//            else {
//                addPart = true;
//            }
//            if (addPart) {
//                PartRecord *newRecord = malloc(sizeof(PartRecord));
//                newRecord->partNumber = partNumber;
//                newRecord->quantity = quantity;
//                strcpy(curr->partName, partName);
//                prev->next = newRecord;
//                newRecord->next = curr;
//                //printParts(theList);
//                return 0;
//            }
//        }
//        prev = curr;
//        curr = curr->next;
//    }
//
//    return 1;

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