#include <stdbool.h>
typedef int Element;

typedef struct node{
    int ele;
    struct node *next;
}node;

typedef struct {
    node *front;
    node *rear;
    int count;
}Queue;
Queue* newQ();
bool isEmptyQ(Queue *q);
Queue* delQ(Queue *q);
Element front(Queue *q);
Queue* addQ(Queue *q, int e);
int lengthQ(Queue *q);
