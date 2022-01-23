#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "lists.oruppert.h" // replace this with your own header file

int checkList(PartRecord *theList, PartRecord *expected, int numExpected) {
  int idx, partCount, numFails;
  PartRecord *curr;

  numFails = 0;

  idx = 0;
  partCount = 0;
  curr = theList;
  while (idx < numExpected && curr != NULL) {
    if (curr->partNumber != expected[idx].partNumber) {
      printf("error: mismatch in position %d: expect partNumber %d; got %d\n",
             idx, expected[idx].partNumber, curr->partNumber);
      ++numFails;
    }
    if (curr->quantity != expected[idx].quantity) {
      printf("error: mismatch in position %d: expect quantity %d; got %d\n",
             idx, expected[idx].quantity, curr->quantity);
      ++numFails;
    }
    if ( strcmp(curr->partName, expected[idx].partName) ) {
      printf("error: mismatch in position %d: expect partName '%s'; got '%s'\n",
             idx, expected[idx].partName, curr->partName);
      ++numFails;
    }

    curr = curr->next;
    ++partCount;
    ++idx;
  }

  if (curr == NULL && idx < numExpected) {
    printf("error: list too short: expect %d items in list; found %d\n",
           numExpected, partCount);
    ++numFails;
  } else {
    if (curr != NULL && idx == numExpected) {
      printf("error: list too long: expect %d items in list; found %d\n",
             numExpected, partCount);
      ++numFails;
    }
  }

  if (numFails == 0)
    printf("ok: checkList() passed\n");

  return numFails;
}

//--------------------------------------------------------------

int testOne() {
  char *testName = "testOne";
  int i, rc, numFails;
  PartRecord *theList = NULL;
  PartRecord expected[8];

  printf("*** running %s ***\n", testName);

  numFails = 0;

  expected[0].partNumber = 5;
  expected[0].quantity = 2;
  strcpy(expected[0].partName, "clutch");

  expected[1].partNumber = 11;
  expected[1].quantity = 3;
  strcpy(expected[1].partName, "gas cap");

  expected[2].partNumber = 12;
  expected[2].quantity = 1;
  strcpy(expected[2].partName, "headlight");

  expected[3].partNumber = 20;
  expected[3].quantity = 3;
  strcpy(expected[3].partName, "radiator");

  expected[4].partNumber = 23;
  expected[4].quantity = 1;
  strcpy(expected[4].partName, "windshield");


  printParts(theList);

  rc = insertPart(&theList, expected[2].partNumber, expected[2].quantity, expected[2].partName);
  if (rc != 0) {
    printf("ERROR from %s: expected rc=0 from insertPart(); got %d\n", testName, rc);
    ++numFails;
  }


  rc = checkList(theList, &expected[2], 1);
  if (rc != 0) {
    printf("ERROR from %s: checkList() failed\n", testName);
    ++numFails;
  }

  rc = insertPart(&theList, expected[1].partNumber, expected[1].quantity, expected[1].partName);
  if (rc != 0) {
    printf("ERROR from %s: expected rc=0 from insertPart(); got %d\n", testName, rc);
    ++numFails;
  }

  //printPartList(theList);

  rc = checkList(theList, &expected[1], 2);
  if (rc != 0) {
    printf("ERROR from %s: checkList() failed\n", testName);
    ++numFails;
  }

  rc = insertPart(&theList, expected[3].partNumber, expected[3].quantity, expected[3].partName);
  if (rc != 0) {
    printf("ERROR from %s: expected rc=0 from insertPart(); got %d\n", testName, rc);
    ++numFails;
  }

  //printPartList(theList);

  rc = checkList(theList, &expected[1], 3);
  if (rc != 0) {
    printf("ERROR from %s: checkList() failed\n", testName);
    ++numFails;
  }

  rc = insertPart(&theList, expected[0].partNumber, expected[0].quantity, expected[0].partName);
  if (rc != 0) {
    printf("ERROR from %s: expected rc=0 from insertPart(); got %d\n", testName, rc);
    ++numFails;
  }

  //printPartList(theList);

  rc = checkList(theList, expected, 4);
  if (rc != 0) {
    printf("ERROR from %s: checkList() failed\n", testName);
    ++numFails;
  }

  rc = insertPart(&theList, expected[4].partNumber, expected[4].quantity, expected[4].partName);
  if (rc != 0) {
    printf("ERROR from %s: expected rc=0 from insertPart(); got %d\n", testName, rc);
    ++numFails;
  }

  //printPartList(theList);

  rc = checkList(theList, expected, 5);
  if (rc != 0) {
    printf("ERROR from %s: checkList() failed\n", testName);
    ++numFails;
  }

  // this should fail
  rc = insertPart(&theList, expected[1].partNumber, expected[1].quantity, expected[1].partName);
  if (rc == 0) {
    printf("ERROR from %s: expected rc !=0 from insertPart(); got %d\n", testName, rc);
    ++numFails;
  }

  //printPartList(theList);

  rc = checkList(theList, expected, 5);
  if (rc != 0) {
    printf("ERROR from %s: checkList() failed\n", testName);
    ++numFails;
  }

  // now delete the third item
  rc = deletePart(&theList, expected[2].partNumber);
  if (rc != 0) {
    printf("ERROR from %s: expected rc=0 from deletePart(); got %d\n", testName, rc);
    ++numFails;
  }

  for (i=2; i<4; ++i)
    memcpy(&expected[i], &expected[i+1], sizeof(PartRecord));

  rc = checkList(theList, expected, 4);
  if (rc != 0) {
    printf("ERROR from %s: checkList() failed\n", testName);
    ++numFails;
  }

  // now delete the first item
  rc = deletePart(&theList, expected[0].partNumber);
  if (rc != 0) {
    printf("ERROR from %s: expected rc=0 from deletePart(); got %d\n", testName, rc);
    ++numFails;
  }

  for (i=0; i<3; ++i)
    memcpy(&expected[i], &expected[i+1], sizeof(PartRecord));

  rc = checkList(theList, expected, 3);
  if (rc != 0) {
    printf("ERROR from %s: checkList() failed\n", testName);
    ++numFails;
  }

  // try to delete a nonexistent part number: should fail
  rc = deletePart(&theList, 99);
  if (rc == 0) {
    printf("ERROR from %s: expected rc !=0 from deletePart(); got %d\n", testName, rc);
    ++numFails;
  }

  //printPartList(theList);

  // now delete the last item
  rc = deletePart(&theList, expected[2].partNumber);
  if (rc != 0) {
    printf("ERROR from %s: expected rc=0 from deletePart(); got %d\n", testName, rc);
    ++numFails;
  }

  rc = checkList(theList, expected, 2);
  if (rc != 0) {
    printf("ERROR from %s: checkList() failed\n", testName);
    ++numFails;
  }

  // now delete the first item
  rc = deletePart(&theList, expected[0].partNumber);
  if (rc != 0) {
    printf("ERROR from %s: expected rc=0 from deletePart(); got %d\n", testName, rc);
    ++numFails;
  }

  memcpy(&expected[0], &expected[1], sizeof(PartRecord));

  rc = checkList(theList, expected, 1);
  if (rc != 0) {
    printf("ERROR from %s: checkList() failed\n", testName);
    ++numFails;
  }

  // now delete the first item
  rc = deletePart(&theList, expected[0].partNumber);
  if (rc != 0) {
    printf("ERROR from %s: expected rc=0 from deletePart(); got %d\n", testName, rc);
    ++numFails;
  }

  rc = checkList(theList, expected, 0);
  if (rc != 0) {
    printf("ERROR from %s: checkList() failed\n", testName);
    ++numFails;
  }

  if (numFails == 0)
    printf("PASS from %s\n", testName);
  else
    printf("FAIL from %s\n", testName);

  return numFails;
}

//--------------------------------------------------------------

int testTwo() {
  char *testName = "testTwo";

  int i, rc, numFails;
  PartRecord *theList, *curr, *newRecord, *rec;
  PartRecord expected[4];

  printf("*** running %s ***\n", testName);

  numFails = 0;

  expected[0].partNumber = 5;
  expected[0].quantity = 2;
  strcpy(expected[0].partName, "clutch");

  expected[1].partNumber = 11;
  expected[1].quantity = 3;
  strcpy(expected[1].partName, "gas cap");

  expected[2].partNumber = 12;
  expected[2].quantity = 1;
  strcpy(expected[2].partName, "headlight");

  curr = NULL;
  theList = NULL;
  for (i=0; i<3; ++i) {
    newRecord = malloc(sizeof(PartRecord));
    newRecord->partNumber = expected[i].partNumber;
    newRecord->quantity = expected[i].quantity;
    strcpy(newRecord->partName, expected[i].partName);
    newRecord->next = NULL;
    if (curr != NULL) {
      curr->next = newRecord;
    } else {
      theList = newRecord;
    }
    curr = newRecord;
  }

  // now try to find each part
  for (i=0; i<3; ++i) {
    rec = findPart(theList, expected[i].partNumber);
    if (rec == NULL) {
      printf("ERROR from %s: findPart(%d) failed\n", testName, expected[i].partNumber);
      ++numFails;
    } else {
      if (rec->partNumber != expected[i].partNumber ||
          rec->quantity != expected[i].quantity ||
          strcmp(rec->partName, expected[i].partName)) {
        printf("ERROR from %s: findPart(%d) returned the wrong value (%d, %d, %s); expected (%d, %d, %s)\n", testName, expected[i].partNumber,
               rec->partNumber, rec->quantity, rec->partName,
               expected[i].partNumber, expected[i].quantity, expected[i].partName);
        ++numFails;
      }
    }
  }

  // now find a nonexistent part: should fail
  rec = findPart(theList, 89);
  if (rec != NULL) {
    printf("ERROR from %s: expected NULL from findPart(); got non-NULL\n", testName);
    ++numFails;
  }

  if (numFails == 0)
    printf("PASS from %s\n", testName);
  else
    printf("FAIL from %s\n", testName);

  return numFails;
}

//--------------------------------------------------------------

int testThree() {
  char *testName = "testThree";
  int rc, numFails;

  printf("*** running %s ***\n", testName);

  numFails = 0;

  rc = insertPart(NULL, 1, 2, "dummy");
  if (rc == 0) {
    printf("ERROR from %s: expected rc !=0 from insertPart(); got %d\n", testName, rc);
    ++numFails;
  }

  if (numFails == 0)
    printf("PASS from %s\n", testName);
  else
    printf("FAIL from %s\n", testName);

  return numFails;
}

//---------------------------------------

int main() {
  int rc;
  int numFails = 0;

  PartRecord *theList;
  theList->partNumber = 5;
  theList-> quantity = 3;
  theList->next = NULL;

  rc = insertPart(&theList, 1, 1, "expected[2].partName");
  printParts(theList);


//
//  rc = testOne();
//  if (rc != 0)
//    ++numFails;
//
//  rc = testTwo();
//  if (rc != 0)
//    ++numFails;
//
//  rc = testThree();
//  if (rc != 0)
//    ++numFails;
//
//  if (numFails == 0)
//    printf("all tests pass\n");
//  else
//    printf("some tests fail\n");
//
//  return numFails;
}
