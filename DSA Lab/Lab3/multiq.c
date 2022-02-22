#include "multiq.h"
#include <stdlib.h>
#include<stdio.h>
// Higher value of Priority p corresponds to higher priority.
// Priority p corresponds to the (p-1)th queue of qArray in MultiQ.
MultiQ* createMQ (int num){
    MultiQ *mq = (MultiQ *)malloc(sizeof(MultiQ));
    if(mq == NULL){
        printf("Unable to allocate memory.");
        exit(1);
            }
    mq->size = num;
    mq->qArray = (Queue **)malloc(num * sizeof(Queue *));
    for(int i=0; i<num; i++)
        (mq->qArray)[i] = newQ();
    return mq;
}

void addMQ(MultiQ* mq, Task t){
    addQ(mq->qArray[t.p - 1], t.tid); 
}

Task nextMQ(MultiQ* mq){
    if(!isEmptyMQ(mq)){
        Task task;
        int i;
        for (i=mq->size - 1;i>=0;i--){
            if (!isEmptyQ(mq->qArray[i]))
            break;
        }
        task.p = i + 1;
        task.tid = front(mq->qArray[i]);
        return task;    
    }
    else {
        printf("MQ empty.");
        exit(1);
    }
}

void delNextMQ(MultiQ* mq){
    for (int i=mq->size - 1;i>=0;i--){
        if (!isEmptyQ(mq->qArray[i])){
        delQ(mq->qArray[i]);
        return;
        }
    }
}

bool isEmptyMQ(MultiQ* mq){
    for (int i=mq->size - 1;i>=0;i--){
        if (!isEmptyQ(mq->qArray[i]))
        return false;
    }
    return true;
    
}
int sizeMQ(MultiQ* mq){
    int size=0;
    for(int i=0;i<mq->size;i++){
        size += (mq->qArray[i])->count;
    }
    return size;
}
int sizeMQbyPriority(MultiQ* mq, Priority p){
    return (mq->qArray[p - 1])->count;
}

Queue* getQueueFromMQ(MultiQ* mq, Priority p){
    return mq->qArray[p - 1];
}