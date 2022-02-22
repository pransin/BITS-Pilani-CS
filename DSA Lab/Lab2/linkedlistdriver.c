#include<stdio.h>
#include "linkedlist.h"
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fileptr = fopen(argv[1], "r");
    struct linkedList *head = (struct linkedList *)malloc(sizeof(struct linkedList));
    
    while(!feof(fileptr)){
        int temp;
        fscanf(fileptr, "%d", &temp);
        insertFirst(head, temp);
    }

    fclose(fileptr);
    printList(head);
    deleteFirst(head);
    printList(head);

}