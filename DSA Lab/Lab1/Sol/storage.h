/***********file:   storage.h *********/
#include "job.h"

typedef struct
{
 Job ele;
 int next;
} Location;

typedef Location Store[MAX];  // MAX already defined in job.h

typedef struct
{
 int size;
 int head;
} SeqList;
typedef SeqList seqarr[MAX_SEQ_LIST];


