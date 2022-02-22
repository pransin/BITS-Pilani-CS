#include <stdbool.h>
#include "linkedlist.h"

bool testCyclic(node *Ls)
{
    if (Ls->next == NULL || Ls->next->next == NULL)
        return false;
    node *tort = Ls;
    node *hare = tort->next;
    while (tort != hare)
    {
        tort = tort->next;
        if (hare != NULL && (hare = hare->next) != NULL)
            hare = hare->next;
        else
            return false;
    }
    return true;

}