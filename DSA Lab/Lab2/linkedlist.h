#include<stdio.h>
struct node{
    int element;
    struct node *next;
};
struct linkedList{
    int count;
    struct node *first;
};
void insertFirst(struct linkedList *head, int ele);
int deleteFirst(struct linkedList *head);
void printList(struct linkedList *head, FILE *fileptr);
int search(struct linkedList *head, int ele);
int delete(struct linkedList *head, int ele);

