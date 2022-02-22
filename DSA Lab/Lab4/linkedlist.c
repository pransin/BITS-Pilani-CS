#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "2.h"

node *createList(int N)
{
    if (N == 0)
        return NULL;
    node *head = myalloc(sizeof(node));
    head->element = rand();
    node *temp = head;

    for (int i = 0; i < N-1; i++)
    {
        node *newnode = myalloc(sizeof(node));
        newnode->element = rand();
        newnode->next = NULL;
        temp->next = newnode;
        temp = temp->next;
    }
    spaceInHeap += N *sizeof(node);
    FILE *tofile = fopen("heapAllocated.txt", "w");
    fprintf(tofile, "%u Bytes", spaceInHeap);
    fclose(tofile);
    return head;
}

void createCycle(node *head)
{
    srand(time(0));
    int toss = rand() % 2;
    if (toss == 1)
    {
        int r_node_pos = rand();
        node *r_node = head;
        while (r_node_pos--)
        {
            r_node = r_node->next;
            if (r_node == NULL)
                r_node = head;
        }
        node *last;
        for (last = r_node; last->next != NULL; last = last->next);
        last->next = r_node;
    }
}
