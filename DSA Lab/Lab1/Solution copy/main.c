#include <stdio.h>
#include "seqListOps.h"

int main(void)
{
 int i;
 seqarr seq;
 joblist arr;
 int size = initialize_elements (arr);
 //printjoblist(arr);
 insertelements (arr,size,seq);
//  printstore(size);
// printseqlist (seq[0]);
// printseqlist (seq[1]);
// printseqlist (seq[2]);
 copy_sorted_ele (seq , arr); 
 //printf ("Sorted List\n");
 printjoblist(arr);
}
 
