#include <stdio.h>
#include <stdlib.h>
#include "2.h"

int main(){
    while(1){
        int m = (rand() % (25000 - 10000 + 1)) + 10000;
        int *ptr = myalloc(m * sizeof(int));
        if (ptr == NULL)
        break;
        printf("%p %p\n",ptr, ptr + m - 1);
        myfree(ptr);
    }
}