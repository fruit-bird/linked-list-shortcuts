//
//  functions.h
//  MiniProj
//
//  Created by Hamza Hraiche on 12/17/21.
//

#ifndef functions_h
#define functions_h

#define maxNiveau 4

typedef struct nodeR {
    int valeur;
    int niveau; //nb of shortcuts/next pointers in a node
    struct nodeR *tabPointeurs[maxNiveau];
} nodeR;

typedef nodeR* listR;

void printNode(listR node) {
    if (node == NULL) {
        printf("\nDoesn't exist\n");
    }
    else {
        printf("\nAdress: %p", node);
        printf("\nValeur: %d", node->valeur);
        printf("\nNiveau: %d\n", node->niveau);
    }
}

//prints all levels of given list
void printAll(listR head) {
    printf("\n"); //just for visuals
    listR temp;
    
    if (head == NULL) {
        //printf("\nEmpty list\n");
        for(int i=0; i<maxNiveau; i++) {
            temp = head;
            printf("Level %d:\t", i+1);
            printf("NULL\n");
        }
    }
    else {
        for(int i=0; i<maxNiveau; i++) {
            temp = head;
            printf("Level %d:\t", i+1);
            while(temp != NULL) {
                printf("%d -> ",temp->valeur);
                temp = temp->tabPointeurs[i];
            }
            printf("NULL\n");
        }
    }
}

/*------------------------------------------------------------*/

//creates independant node
listR createNode(int v, int k) {
    listR newnode = (listR)malloc(sizeof(nodeR));
    
    newnode->valeur = v;
    newnode->niveau = k;
    for (int i=0; i<maxNiveau; i++) { //i<k ??, no, possible need for linking new nodes
        newnode->tabPointeurs[i] = NULL;
    }
    return newnode;
}

//creates n new nodes with values of tableauValeurs and tableauNiveaux and links them conventionally
listR buildLevel1(int n, int *tableauValeurs, int *tableauNiveaux) {
    listR head = createNode(tableauValeurs[0], tableauNiveaux[0]);
    listR temp = head;

    for (int i=1; i<n; i++, temp=temp->tabPointeurs[0]) {
        temp->tabPointeurs[0] = createNode(tableauValeurs[i], tableauNiveaux[i]);
    }
    return head;
}


listR buildListR(int n, int *tableauValeurs, int *tableauNiveaux) {
    listR head = buildLevel1(n, tableauValeurs, tableauNiveaux);
    listR lvlStorage[maxNiveau]; //array to store pointers to current last node with corresponding level, works as temp for the array tabPointerus; maxNiveau ≠ tableauNiveaux[0] ??
    
    //lvlStorage[0] takes the tabPointeurs[0] of the head so as to work as storage for the first level, so basically works as temp
    lvlStorage[0] = head->tabPointeurs[0];
    // pointing the other array cells to the head of the list
    for (int i=1; i<maxNiveau; i++) {  // i<tableauNiveaux[0]
        lvlStorage[i] = head;
    }
    
    //lvlStorage[0] traverses the list in a typical fashion
    while (lvlStorage[0] != NULL) {
        //i starts from 1 because first level is already built
        //lvlStorage[0]->niveau instead of maxNiveau because we only want to link the amount of lvls of the current cell
        for (int i=1; i<lvlStorage[0]->niveau; i++) {
            lvlStorage[i]->tabPointeurs[i] = lvlStorage[0]; //lvlStorage[0] is the next cell we need to link to previous one of same lvl0
            lvlStorage[i] = lvlStorage[i]->tabPointeurs[i];
        }
        lvlStorage[0] = lvlStorage[0]->tabPointeurs[0];
    }
    return head;
}

listR findNode(listR head, int x) {
    if (head->valeur == x) {
        return head;
    }
    listR lvlStorage[maxNiveau];
    int i;
    
    for (i=0; i<maxNiveau; i++) {
        lvlStorage[i] = head->tabPointeurs[i]; // point each element in the array to the corresponding pointer in head
    }
    
    // i starts from [3] down to [0] until the node is found or list is finished
    for (i=maxNiveau-1; i>=0; i--) {
        while (lvlStorage[i] != NULL) {
            if (lvlStorage[i]->valeur == x) { //lvlStorage[i] is the next of the current cell, so it can never check for first value #1:
                return lvlStorage[i];
            }
            lvlStorage[i] = lvlStorage[i]->tabPointeurs[i]; //when reaching end of lvl i (lvlStorage[i] = NULL) => leaving while and going up a lvl
        }
    }
    return NULL; //default when node with x doesn't exist
}

listR insertNode(listR head, int x, int k) {
    //empty list
    if (head == NULL) {
        return createNode(x, k);
    }
    //node exists
    if (findNode(head, x) != NULL) {
        return head;
    }
    //inverts values of x and head->valeur so as x is inserted in a new node that will be placed second
    listR newnode;
    if (head->valeur > x) {
        newnode = createNode(head->valeur, k);
        head->valeur = x;
        for (int i=0; i<k; i++) {
            newnode->tabPointeurs[i] = head->tabPointeurs[i];
            head->tabPointeurs[i] = newnode;
        }
        return head;
    }
    //normal insertion
    newnode = createNode(x, k);
    listR lvlStorage[maxNiveau];
    for (int i=0; i<maxNiveau; i++) {
        lvlStorage[i] = head; // point each element in the array to the head
    }
    
    for (int i=0; i<k; i++) { //check why is i<maxNiveau not optimal??
        //lvlStorage[] stores pointers to last node with a valeur < x, so  lvlStorage[] holds all the pointers to be connected to newnode
        while (lvlStorage[i]->tabPointeurs[i] != NULL && lvlStorage[i]->tabPointeurs[i]->valeur < x) {
            lvlStorage[i] = lvlStorage[i]->tabPointeurs[i];
        }
    }
    //all that is left is to connect the lvlStorage[i]->tabPointerurs[i] to tabPointeurs of newnode
    for (int i=0; i<k; i++) {
        newnode->tabPointeurs[i] = lvlStorage[i]->tabPointeurs[i]; //prof forgot this!!!!
        lvlStorage[i]->tabPointeurs[i] = newnode;
    }
    
    return head;
}

listR deleteNode(listR head, int x) {
    //is empty list
    if (head == NULL) {
        return head;
    }
    //is only node, slight issue
    if (head->tabPointeurs[0] == NULL && head->valeur == x) {
        free(head); //check comment above the main function
        return NULL;
    }
    //no such node
    if (findNode(head, x) == NULL) {
        return head;
    }
    
    //VARIABLES!!
    listR temp = head; //initialised with head for different cases of use
    listR lvlStorage[maxNiveau];
    for (int i=0; i<maxNiveau; i++) {
        lvlStorage[i]= head;
    }
    
    //is first node
    if (head->valeur == x) {
        //give first node valeur of second node, second node gets freed after
        head->valeur = head->tabPointeurs[0]->valeur;
        
        //i<maxNiveau because first node is of lvl maxNiveau
        temp = head->tabPointeurs[0]; //save a pointer the node to be freed
        for (int i=0; i<temp->niveau; i++) {
            head->tabPointeurs[i] = head->tabPointeurs[i]->tabPointeurs[i];
        }
        free(temp);
        return head;
    }
    
    //normal deletion
    for (int i=0; i<findNode(head, x)->niveau; i++) {
        while (lvlStorage[i]->tabPointeurs[i] != NULL && lvlStorage[i]->tabPointeurs[i]->valeur != x) {
            lvlStorage[i] = lvlStorage[i]->tabPointeurs[i];
            //printf("%d, %d\n", i, lvlStorage[i]->valeur); //debugging
        }
    }
   
    temp = lvlStorage[0]->tabPointeurs[0]; // point to node to be freed
    for (int i=0; i<temp->niveau; i++) {
        lvlStorage[i]->tabPointeurs[i] = lvlStorage[i]->tabPointeurs[i]->tabPointeurs[i];
    }
    free(temp);
    return head;
}

#endif /* functions_h */
