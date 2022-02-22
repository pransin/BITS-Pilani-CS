#include "merge.h"

void merge(Element Ls1[], int sz1, Element Ls2[], int sz2, Element Ls[])
{
    int i = 0, j = 0;
    while (i < sz1, j < sz2)
    {
        if (Ls1[i].CGPA >= Ls2[j].CGPA)
        {
            Ls[i + j] = Ls2[j];
            j++;
        }
        else
        {
            Ls[i + j] = Ls1[i];
            i++;
        }
    }
    if (i == sz1)
    {
        while (j < sz2)
        {
            Ls[i + j] = Ls2[j];
            j++;
        }
    }
    else
    {
        while (i < sz1)
        {
            Ls[i + j] = Ls1[i];
            i++;
        }
    }
}