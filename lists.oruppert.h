//
// Created by olinr on 1/22/2022.
//

#ifndef LINKEDLIST_LISTS_ORUPPERT_H
#define LINKEDLIST_LISTS_ORUPPERT_H

#define PARTNAME_LEN 32
typedef struct PartRecordStruct {
    int partNumber;
    int quantity;
    char partName[PARTNAME_LEN];
    struct PartRecordStruct *next;
} PartRecord;

int insertPart(PartRecord **theList, int partNumber, int quantity, char *partName);

int deletePart(PartRecord **theList, int partNumber);

PartRecord *findPart(PartRecord *theList, int partNumber);

void printParts(PartRecord *theList);

int freeMem(PartRecord *theList);

#endif //LINKEDLIST_LISTS_ORUPPERT_H
