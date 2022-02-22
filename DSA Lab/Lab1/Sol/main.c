/***********file:   main.c *********/
#include <stdio.h>
#include "seqListOps.h"

int main(void)
{
 int i; int size;
 seqarr seq;
 JobList list;
 size = initialize_elements (list);
 printf("The Jobs waiting on CPU are:\n");
 printJobList(list, size);
 insertelements (list, size, seq);
 printf("The Jobs after sorting are:\n");
 printJobList(list, size);
 return 0;
}
 
