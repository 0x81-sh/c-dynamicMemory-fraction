#include <stdio.h>
#include <stdlib.h>

//----------------- structs

typedef struct {
    int val;
    int denom;
} Fraction;

typedef Fraction* PFraction;

typedef struct {
    PFraction *list;
    int noe;
} PFractionList;

typedef PFractionList* PPFractionList;

//----------------- prototypes

PFraction createFraction (int v, int d);
void printFraction (PFraction f);
void deleteFraction (PFraction f);
void readFraction (PFraction f);

PPFractionList createFractionList (int initialNoe);
void printFractionList (PPFractionList ppFractionList);
void readFractionList (PPFractionList ppFractionList);
void deleteFractionList (PPFractionList ppFractionList);

void reAllocList(PPFractionList ppFractionList);
double getActualValue (PPFractionList ppFractionList, int index);

void listAddFraction (PPFractionList ppFractionList, PFraction pFraction);
void listInsertFraction (PPFractionList ppFractionList, PFraction pFraction, int index);
void listDeleteFraction (PPFractionList ppFractionList, int index);
void listSortFraction (PPFractionList ppFractionList);

//-----------------

int main() {
    //Test initializing a new list
    printf("------------- Creation test\n");
    printf("Enter size of list: ");
    int size;
    scanf("%d", &size);

    //Test filling the struct with user data
    printf("\n------------- User input test\n");
    PPFractionList test = createFractionList(size);
    readFractionList(test);

    printf("\n>>>>");
    printFractionList(test);

    //Test adding a new item to the structure and removing one
    printf("\n\n------------- Insertion and deletion test\n");

    printf("Enter index to insert at: ");
    int index;
    PFraction insertValue = createFraction(0, 1);
    scanf("%d", &index);
    readFraction(insertValue);
    listInsertFraction(test, insertValue, index);

    printf("Enter index to delete at: ");
    int delIndex;
    scanf("%d", &delIndex);
    listDeleteFraction(test, delIndex);

    printf("\n>>>>");
    printFractionList(test);

    //Test sorting the structure by values
    printf("\n\n------------- Sorting test\n");

    listSortFraction(test);
    printf("\n>>>>");
    printFractionList(test);

    //Cleanup and exit
    deleteFractionList(test);
    return 0;
}

//----------------- 6.1

PFraction createFraction (int v, int d) {
    PFraction ret = NULL;

    ret = (PFraction) malloc(sizeof (Fraction));
    ret->val = v;
    ret->denom = d;

    return ret;
}

void printFraction (PFraction f) {
    printf("%d/%d", f->val, f->denom);
}

void deleteFraction(PFraction f) {
    free(f);
}

void readFraction (PFraction f) {
    printf("Enter value: ");
    scanf("%d", &f->val);
    printf("Enter denom: ");
    scanf("%d", &f->denom);

    if (f->denom == 0) {
        printf("Cannot divide by zero.");
        exit(1);
    }
}

//----------------- 6.2

PPFractionList createFractionList (int initialNoe) {
    PPFractionList newList = NULL;

    newList = (PPFractionList) malloc(sizeof(PPFractionList));
    newList->noe = initialNoe;
    newList->list = (PFraction*) malloc(sizeof(PFraction) * initialNoe);

    for (int i = 0; i < initialNoe; i++) {
        *(newList->list + i) = createFraction(0, 1);
    }

    return newList;
}

void printFractionList (PPFractionList ppFractionList) {
    for (int i = 0; i < ppFractionList->noe; i++) {
        printf("\nFraction %d: ", i);
        printFraction(*(ppFractionList->list + i));
    }
}

void readFractionList (PPFractionList ppFractionList) {
    for (int i = 0; i < ppFractionList->noe; i++) {
        printf("Fraction %d: \n", i);
        readFraction(*(ppFractionList->list + i));
    }
}

void deleteFractionList (PPFractionList ppFractionList) {
    for (int i = 0; i < ppFractionList->noe; i++) {
        deleteFraction(*(ppFractionList->list + i));
    }

    free(ppFractionList);
}

//----------------- 6.3

void reAllocList(PPFractionList ppFractionList) {
    ppFractionList->list = (PFraction*) realloc(ppFractionList->list, sizeof(PFraction) * ppFractionList->noe);
}

void listAddFraction (PPFractionList ppFractionList, PFraction pFraction) {
    ppFractionList->noe++;
    reAllocList(ppFractionList);

    *(ppFractionList->list + (ppFractionList->noe - 1)) = pFraction;
}

void listInsertFraction (PPFractionList ppFractionList, PFraction pFraction, int index) {
    if (index > ppFractionList->noe || index < 0) {
        printf("\nCannot insert a fraction outside of list");
        exit(1);
    }

    ppFractionList->noe++;
    reAllocList(ppFractionList);

    for (int i = ppFractionList->noe - 1; i >= index; i--) {
        *(ppFractionList->list + i + 1) = *(ppFractionList-> list + i);
    }

    *(ppFractionList->list + index) = pFraction;
}

void listDeleteFraction (PPFractionList ppFractionList, int index) {
    if (index > ppFractionList->noe - 1 || index < 0) {
        printf("\nCannot remove a fraction outside of list");
        exit(1);
    }

    deleteFraction(*(ppFractionList->list + index));
    for (int i = index; i < ppFractionList->noe; i++) {
        *(ppFractionList->list + i) = *(ppFractionList-> list + i + 1);
    }

    ppFractionList->noe--;
    reAllocList(ppFractionList);
}

double getActualValue (PPFractionList ppFractionList, int index) {
    return (double) (*(ppFractionList->list + index)) -> val / (double) (*(ppFractionList->list + index)) -> denom;
}

void listSortFraction (PPFractionList ppFractionList) {
    while (1) {
        int changes = 0;

        for (int i = 0; i < ppFractionList->noe - 1; i++) {
            if (getActualValue(ppFractionList, i) > getActualValue(ppFractionList, i + 1)) {
                changes = 1;

                PFraction TEMP = *(ppFractionList->list + i);
                *(ppFractionList->list + i) = *(ppFractionList->list + i + 1);
                *(ppFractionList->list + i + 1) = TEMP;
            }
        }

        if (!changes) break;
    }
}