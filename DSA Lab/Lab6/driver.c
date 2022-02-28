#include <stdio.h>
#include "mergeSort.h"

int main(){
    FILE* ptr = fopen("1024.txt", "r");
    if (ptr == NULL){
        printf("File cannot be read.");
        return 1;
    }
    Element records[1025];
    char temp;
    for (int i=0; i < 1024; i++){
        fscanf(ptr, "%[^,],%f\n", records[i].Name, &records[i].CGPA);   
    }
    mergeSort(records, 1024);
    fclose(ptr);
    ptr = fopen("Sorted1024.txt", "w");
    if (ptr == NULL){
        printf("File cannot be read.");
        return 1;
    }
    for (int i=0; i < 1024; i++){
        fprintf(ptr, "%.10s,%f\n", records[i].Name, records[i].CGPA);   
    }
    fclose(ptr);
}