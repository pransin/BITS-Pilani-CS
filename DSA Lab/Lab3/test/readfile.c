#include <stdio.h>
#include<stdlib.h>
struct node{
    struct node *p;
};
int main(void){
    // int i;
    // char c;
    // FILE* f=fopen("testinput.txt", "r");
    // if(f == NULL){
    //     printf("File cannot be opened.");
    //     exit(1);
    // }
    // // int j=20;
    // while(!feof(f)){
    //     fscanf(f, "%d", &i);
    //     printf("%d\n", i);
    //     fscanf(f, "%c", &c);
    //     fscanf(f, "%d", &i);
    //     printf("%d\n", i);

    // }

    
    // fclose(f);
    struct node Node;
    Node.p = NULL;
    printf("%p", Node.p);
}