//
// Created by olinr on 1/22/2022.
//

#include "lists.oruppert.h"
#include "includes.h"

int insertPart(PartRecord **theList, int partNumber, int quantity, char *partName){
    bool duplicate = false;
    PartRecord *curr = *theList;
    PartRecord *prev = curr;
    if (curr != NULL) {
        while (curr != NULL) {
            if (curr->partNumber == partNumber)
                duplicate = true;
            prev = curr;
            curr = curr->next;

        }

        if (!duplicate) {
            PartRecord *newRecord = malloc(sizeof(PartRecord));
            newRecord->partNumber = partNumber;
            newRecord->quantity = quantity;

            prev->next = newRecord;
            return 0;
        }
        return 1;
    }
    else {
        return 1;
    }
}

int deletePart(PartRecord **theList, int partNumber){
    PartRecord *curr = *theList;
    PartRecord *prev = curr;
    if (curr != NULL) {
        while (curr != NULL) {
            if (curr->partNumber == partNumber) {

            }
            curr = curr->next();
        }



}

PartRecord *findPart(PartRecord *theList, int partNumber){

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