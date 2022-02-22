#include <stdbool.h>
#include "linkedlist.h"


bool testCyclic(node *Ls){
    node *prev = Ls;
    if (prev == NULL)
    return false;
    node *curr = Ls->next;
    node *nex = curr;
    while(nex != Ls)
    {
        if(nex == NULL)
        return false;
        nex = nex->next;
        curr->next = prev;
        prev = curr;
        curr = nex;
    }
    return true;
}