#include "que.h"

typedef int Priority;

typedef struct {
    Queue** qArray;
    int size;
    
}MultiQ;

typedef struct {
    int tid;
    Priority p;
}Task;

MultiQ* createMQ (int num);
void addMQ(MultiQ* mq, Task t);
Task nextMQ(MultiQ* mq);
void delNextMQ(MultiQ* mq);
bool isEmptyMQ(MultiQ* mq);
int sizeMQ(MultiQ* mq);
int sizeMQbyPriority(MultiQ* mq, Priority p);
Queue* getQueueFromMQ(MultiQ* mq, Priority p);