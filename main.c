#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, const char * argv[]) {
    int tabValeurs[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32};
    int tabNiveaux[] = {maxNiveau, 2, 1, 1, 3, 1, 2, 4, 1, 1, 1, 3, 1, 2, 1, 1};
    listR list;
    
    
    printf("\tQUESTION 2:");
    printNode(createNode(99, 5));
    
    
    printf("\tQUESTION 3:");
    list = buildLevel1(sizeof(tabValeurs)/sizeof(tabValeurs[0]), tabValeurs, tabNiveaux);
    printAll(list);
    
    
    printf("\tQUESTION 4:");
    list = buildListR(16, tabValeurs, tabNiveaux);
    printAll(list);

    
    printf("\tQUESTION 5:");
    printNode(findNode(list, 1)); //finding a non-existing node
    for (int i=0; i<16; i++) {
        printNode(findNode(list, tabValeurs[i])); //finding every node in the list
    }

    
    printf("\tQUESTION 6:");
    printAll(insertNode(NULL, 17, maxNiveau)); //if list is empty
    
    insertNode(list, 16, 4); //if value exists
    printAll(list);
    
    insertNode(list, 1, 3); //if value is lower than the first node
    printAll(list);
    
    insertNode(list, 33, 3); //if value doesn't exist
    insertNode(list, 13, 4);
    printAll(list);
    
    
    printf("\tQUESTION 7:");
    printAll(deleteNode(NULL, 4)); //empty list, works
    
    printAll(deleteNode(createNode(5, maxNiveau), 5)); //list contains single node to be deleted
    
    printAll(deleteNode(list, 3)); //list contains no node to be deleted
    
    deleteNode(list, 1); //first node to be deleted
    deleteNode(list, 2);
    deleteNode(list, 4);
    printAll(list);
    
    deleteNode(list, 28); //delete in middle
    deleteNode(list, 13);
    printAll(list);
    
    printAll(deleteNode(list, 33)); //delete in end

    
    //extreme testing
    for (int i=12; i<28; i=i+2) {
        deleteNode(list, i);
    }
    printAll(list);

    printf("\n");
    return 0;
}

