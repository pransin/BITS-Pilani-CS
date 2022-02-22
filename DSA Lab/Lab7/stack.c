#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *newStack()
{
    Stack *temp = (Stack *)malloc(sizeof(Stack));
    temp->size = 0;
    temp->top = NULL;
    return temp;
}
void push(Stack *stack, int ele)
{
    struct node *newtop = (struct node *)malloc(sizeof(struct node));
    if(newtop == NULL){
        printf("Memory cannot be allocated.\n");
        exit(1);
    }
    newtop->next = stack->top;
    newtop->ele = ele;
    stack->top = newtop;
    stack->size++;
}
int pop(Stack *stack)
{
    if (stack->size == 0)
    {
        printf("Stack Empty.");
        exit(1);
        return 0;
    }
    int x;
    if (stack->size > 1)
    {
        struct node *temp = stack->top->next;
        x = stack->top->ele;
        free(stack->top);
        stack->top = temp;
    }
    else
    {
        x = stack->top->ele;
        free(stack->top);
        stack->top = NULL;
    }
    stack->size--;
    return x;
}