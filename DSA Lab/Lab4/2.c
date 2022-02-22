#include <stdlib.h>
#include "2.h"
void *myalloc(unsigned int m){
    void *ptr = malloc(m);
    if (ptr == NULL)
        return NULL;
    spaceInHeap += m;
    return ptr;
}
void *myfree(void *ptr, int size){
    spaceInHeap -= size;
    free(ptr);    
}
