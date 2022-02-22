#include<stdio.h>
#include<stdlib.h>
int main(int argc, char* argv[]){
    FILE* readptr = fopen(argv[1], "r");
    FILE* writeptr = fopen(argv[2], "w");
    char temp[500];
    if (readptr == NULL){
        printf("File cannot be opened.");
        exit(1);
        }
    if (writeptr == NULL){
        printf("Writing file cannot be opened.");
        exit(2);
        }    
    while(!feof(readptr)){
        fgets(temp, 10, readptr);
        fprintf(writeptr, "%s", temp);
    }
    fclose(readptr);
    fclose(writeptr);
    return 0;
    
}