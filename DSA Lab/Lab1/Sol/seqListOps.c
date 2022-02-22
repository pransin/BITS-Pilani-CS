/***********file:   Ops.c *********/
#include <stdio.h>
#include "storage.h"
#include "compare.h"
int nextfreeloc = 0;
Store st;
void copy_sorted_ele(seqarr s, JobList ele);
SeqList createlist()
{
 SeqList sl;
 sl.head = nextfreeloc++;
 sl.size = 0;
 st[sl.head].next = -1;
 return (sl);
}

void printJob (Job j)
{
printf ("JOB ID = %d, Priority = %d, Execution time = %d, Arrival time = %d \n",j.id,j.pri,j.et,j.at);
}


int initialize_elements (JobList list)
{
 int i; int size;

 printf("\n Enter the Number of Jobs :");
 scanf("%d", &size);

 for (i=0;i<size;i++)
 {
  printf ("\nEnter job ID: ");
  scanf ("%d",&list[i].id);
  printf ("Enter Priority (from 0 - 2): ");
  scanf ("%d",&list[i].pri);
  printf ("Execution Time: ");
  scanf ("%d",&list[i].et);
  printf ("Arrival Time: ");
  scanf ("%d",&list[i].at);
 }
 return size;
}

SeqList insert(Job j , SeqList sl)
{
    int i, temp;
// if and else if blocks ensure that the head location also stores a job
    if(sl.size == 0){
        st[sl.head].ele = j;
        sl.size++;
    }
    else if(compare(st[sl.head].ele, j) == GREATER){
        st[nextfreeloc].ele = j;
        st[nextfreeloc].next = sl.head;
        sl.head = nextfreeloc++;
        sl.size++;
    }
    else{
    for(i = sl.head; st[i].next != -1 ;i = st[i].next){
        if(compare(st[st[i].next].ele, j) == GREATER)
        break; 
    }
    temp = nextfreeloc++;
    st[temp].next = st[i].next;
    st[temp].ele = j;
    st[i].next = temp;
    sl.size++;
    // printf("\n%d", sl.size);
    }
    return sl;
 }
  
void insertelements (JobList list , int size, seqarr s)
{
    // Implement this function
    for (int i=2; i>=0; i--){
        s[i] = createlist();
        for(int j=0; j<size;j++){
            if(list[j].pri == i)
            s[i] = insert(list[j], s[i]);
        }
        
    }
    copy_sorted_ele(s, list);
}

void copy_sorted_ele(seqarr s, JobList list)
{
    int index=0;
    int j;
// Implement this function
    for(int i=2; i>=0; i--){
        for(j=s[i].head;st[j].next!=-1; j = st[j].next){
            list[index] = st[j].ele;
            index++;
        }
        list[index] = st[j].ele;
        index++;
    }

}

void printseqlist(SeqList sl)
{

// Implement this function
for(int i=sl.head; st[i].next!=-1; i = st[i].next)
    printJob(st[st[i].next].ele);
}

void printJobList(JobList list, int size)
{

// Implement this function
    for(int i=0; i<size; i++){
        printJob(list[i]);
    }

}
