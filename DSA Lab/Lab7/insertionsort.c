#include "employee.h"


void insertionSort(Employee empArray[], int size){
    for(int i=0; i<size-1; i++){
        int j = i + 1;
        while(j > 0 && empArray[j].empID < empArray[j - 1].empID){
            // swap
            Employee temp = empArray[j];
            empArray[j] = empArray[j-1];
            empArray[j-1] = temp;
            j--;
        }
        
    }
}