#include "multiq.h"
#include <stdio.h>
#include <stdlib.h>


MultiQ* loadData(FILE* f){
    Task t; char c;
    
    MultiQ* mq = createMQ(10);
    
    while(!feof(f)){
    fscanf(f, "%d", &t.tid);
    fscanf(f, "%c", &c);
    fscanf(f, "%d", &t.p);
    addMQ(mq, t);
    }
    return mq;
}

void testDel(MultiQ* mq, int num){
    while(num--){
        delNextMQ(mq);
    }
}


int main(void){
    FILE* f = fopen("input10000.txt", "r");
    if(f == NULL){
        printf("File cannot be opened.");
        exit(1);
    }
    MultiQ* mq = loadData(f);   
    testDel(mq, 50);
    testDel(mq, 5);
    

}