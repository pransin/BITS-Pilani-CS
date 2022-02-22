#include "que.h"
#include<stdlib.h>

Queue* newQ(){
    return malloc(sizeof(Queue));
}

bool isEmptyQ(Queue *q){
    if (q->count == 0)
    return true;
    else 
    return false;
}

Queue* delQ(Queue *q){
    if(isEmptyQ(q))
    return q;
    node *temp = (q->front)->next;
    free(q->front);
    q->front = temp;
    // If q has only one element, then after deletion q->rear will also be NULL.
    if(isEmptyQ(q))
    q->rear = NULL;
    q->count--;
    return q;
}

Element front(Queue *q){
    if(!isEmptyQ(q))
    return (q->front)->ele;
    else return -1;
}

Queue* addQ(Queue *q, int e){
    node *newnode = malloc(sizeof(node));
    newnode->ele = e;
    newnode->next = NULL;
    if(!isEmptyQ(q)){
        (q->rear)->next = newnode;
        q->rear = newnode;
    }
    else{
        q->front = q->rear = newnode;
    }
    q->count++;
    return q; 
}

int lengthQ(Queue *q){
    return q->count;
}

