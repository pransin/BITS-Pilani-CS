#include "stack.h"
#include <stdlib.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        printf("Usage: ./exe stackInput.txt\n");
        exit(1);
    }
      FILE *fileptr = fopen(argv[1], "r");
    struct linkedList *head = (struct linkedList *)malloc(sizeof(struct linkedList));
    
    while(!feof(fileptr)){
        int ele;
        fscanf(fileptr, "%d", &ele);
        push(head, ele);
    }
    fclose(fileptr);

    while(head->first != NULL){
        printf("\n%d", pop(head)); // prints the popped element
        printList(head, NULL);  // prints entire stack. Pass a file ptr instead of NULL to write to a file
    }
    return 0;
    
}