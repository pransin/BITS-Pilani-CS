#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct Stack{
    struct node *top;
    int size;
}Stack;
struct node{
    int ele;
    struct node *next;
}node;

typedef struct Employee{
    char name[11];
    int empID;
}Employee;

Stack *newStack()
{
    Stack *temp = (Stack *)malloc(sizeof(Stack));
    temp->size = 0;
    temp->top = NULL;
    return temp;
}

void push(Stack *stack, int ele)
{
    struct node *newtop = (struct node *)malloc(sizeof(struct node));
    if(newtop == NULL){
        printf("Memory cannot be allocated.\n");
        exit(1);
    }
    newtop->next = stack->top;
    newtop->ele = ele;
    stack->top = newtop;
    stack->size++;
}
int pop(Stack *stack)
{
    if (stack->size == 0)
    {
        printf("Stack Empty.");
        exit(1);
        return 0;
    }
    int x;
    if (stack->size > 1)
    {
        struct node *temp = stack->top->next;
        x = stack->top->ele;
        free(stack->top);
        stack->top = temp;
    }
    else
    {
        x = stack->top->ele;
        free(stack->top);
        stack->top = NULL;
    }
    stack->size--;
    return x;
}

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

void swap(Employee *l, Employee *r)
{
    Employee temp = *l;
    *l = *r;
    *r = temp;
}
int partition(Employee empArray[], int l, int r)
{
    int pivot = empArray[r].empID;
    int i = l - 1;
    for (int j = l; j < r; j++)
    {
        if (empArray[j].empID <= pivot)
        {
            i++;
            swap(&empArray[i], &empArray[j]);
        }
    }
    swap(&empArray[i + 1], &empArray[r]);
    return i + 1;
}

void quickSort(Employee empArray[], int size, int S)
{
    int l, r;
    Stack *temp = newStack();
    push(temp, 0);
    push(temp, size - 1);
    while (temp->size > 0)
    {
        r = pop(temp);
        l = pop(temp);
        int p = partition(empArray, l, r);
        if (p - l > S)
        {
            push(temp, l);
            push(temp, p - 1);
        }

        if (r - p > S)
        {
            push(temp, p + 1);
            push(temp, r);
        }
    }
}
void mixedSort(Employee empArr[], int size, int S){
    quickSort(empArr, size, S);
    insertionSort(empArr, size);
}

void testRun(Employee *empArray, int size, double results[]){
    // printf("%d\n", size);
    struct timeval t1, t2;
    Employee empArray1[size];
    Employee empArray2[size];
    for(int i = 0; i < size; i++){
        empArray1[i] = empArray2[i] = empArray[i];
    }

    gettimeofday(&t1, NULL);
    quickSort(empArray1, size, 0);
    gettimeofday(&t2, NULL);
    // results[0] = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
    results[0] = (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0;

    gettimeofday(&t1, NULL);
    insertionSort(empArray2, size);
    gettimeofday(&t2, NULL);
    // results[1] = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
    results[1] = (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0;
}


int estimateCutoff(Employee *empArray, int max){
    double results[2];
    // results[0] -> quickSort
    // results[1] -> insertionsort
    int min = 0;
    // testRun(empArray, min, results);
    testRun(empArray, max, results);

    if(results[0] > results[1]){
        return max;
    }
    // printf("%f %f\n", results[0], results[1]);
    int epsilon = 0;  // Epsilon decides the how close insertionsort can be to quicksort for mid to be a good cutoff size. 
    int mid = (min + max) / 2;
    while(min != max){
        
        if (results[0] - results[1] > epsilon){
            min = mid;
        }
        else if (results[0] - results[1] < -epsilon){
            max = mid;
        }
        else return mid;
        // printf("%f %f\n", results[0], results[1]);
        mid = (min + max) / 2;
        //  printf("%d\n", mid);


        testRun(empArray, mid, results);
    }
    return mid;

}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Please input 1st argument as input file and second argument as output file.\n");
        return 0;
    }

    FILE *inputfile = fopen(argv[1], "r");

    int input_size = atoi(argv[1]);
    if (inputfile == NULL)
    {
        printf("File cannot be opened.\n");
        return 0;
    }

    Employee empArray[input_size];
    for (int i = 0; i < input_size; i++)
        fscanf(inputfile, "%s %d\n", empArray[i].name, &empArray[i].empID);
    fclose(inputfile);
    int cutoff;
    if (input_size > 1000)
        cutoff = estimateCutoff(empArray, 1000);
    else
        cutoff = estimateCutoff(empArray, input_size);

    struct timeval t1, t2;
    double elapsedTime;

    gettimeofday(&t1, NULL);
    mixedSort(empArray, input_size, cutoff);
    gettimeofday(&t2, NULL);

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

    FILE *outputfile = fopen(argv[2], "w");

    fprintf(outputfile, "Time Taken to sort %d elements with mixedSort cutoff %d: %lf milliseconds.\n\n", input_size, cutoff, elapsedTime);

    printf("Time Taken to sort %d elements with mixedSort cutoff %d: %lf milliseconds.\n", input_size, cutoff, elapsedTime);

    for (int i = 0; i < input_size; i++)
    {
        fprintf(outputfile, "%s %d\n", empArray[i].name, empArray[i].empID);
    }
}