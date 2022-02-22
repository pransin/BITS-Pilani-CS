#include <stdio.h>

typedef struct node{
    int element;
    struct node *next;
}node;

node* createList(int N);
void createCycle(node *head);

