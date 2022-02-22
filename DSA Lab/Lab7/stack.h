typedef struct Stack{
    struct node *top;
    int size;
}Stack;
struct node{
    int ele;
    struct node *next;
}node;

void push(Stack *stack, int ele);
int pop(Stack *stack);
Stack* newStack();