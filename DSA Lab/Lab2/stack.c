#include "stack.h"
void push(struct linkedList *head, int ele)
{
    insertFirst(head, ele);
}
int pop(struct linkedList *head){
    return deleteFirst(head);
}