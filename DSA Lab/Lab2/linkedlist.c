#include "linkedlist.h"
#include<stdlib.h>
#include<stdio.h>

void insertFirst(struct linkedList *head, int ele){
    struct node *link = (struct node*)malloc(sizeof(struct node));
    link->element = ele;
    link->next = head->first;
    head->first  = link;
    head->count++;

}

int deleteFirst(struct linkedList *head){
    struct node *temp = head->first;
    int temp_ele = (head->first)->element;
    head->first = (head->first)->next;
    free(temp);
    head->count--;
    return temp_ele;
}
void printList(struct linkedList *head, FILE *fileptr){ // if block writes on console and else block in file according to the fileptr received.
    struct node *ptr = head->first;
    if(fileptr == NULL){
        printf("\n[");
        while(ptr != NULL){
            printf("%d, ", ptr->element);
            ptr = ptr->next;
            }
        printf("]");
    }
    else
    {
        fprintf(fileptr,"\n[");
        while(ptr != NULL){
            fprintf(fileptr, "%d, ", ptr->element);
            ptr = ptr->next;
            }
        fprintf(fileptr, "]");
    }
    
}

int search(struct linkedList *head, int ele){
    struct node *ptr = head->first;
    while(ptr != NULL){
        if(ptr->element == ele)
        return 1;
        ptr = ptr->next;
    }
    return 0;
}

int delete(struct linkedList *head, int ele){
    struct node *prev = head->first;
    struct node *ptr = NULL;
    // Checks if the first element is the element to be deleted.
    if(prev == NULL){
        printf("Stack empty.\n");
        return -1;
    }
    if(prev->element == ele)
        return deleteFirst(head);

    if(head->count > 1)
        ptr = prev->next;

    while(ptr != NULL){
        if(ptr->element == ele){
            prev->next = ptr->next;
            int temp = ptr->element;
            free(ptr);
            head->count--;
            return temp;
        }
        prev = ptr;
        ptr = ptr->next;
    }
    printf("Element not Found.\n");
    return -1; //returns -1 if the passed element is not found.
}