#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int baseNumber,tableSize;
struct read
{
	char ** book;
	int size;
};

typedef struct read Book;

struct node
{
	int index;
	int count;
	char * str;
	struct node * next;
};

typedef struct node Node;

struct hash
{
	int elementCount;
	int insertionCost;
	int queryingCost;
	Node ** arrLink;
};

typedef struct hash hashtable;

int hashFunction(char * str)
{
	int i,hash,sum = 0;
	for(i = 0; i < strlen(str); i++)
	{
		sum += str[i];
	}
	hash = sum % baseNumber;
	return (hash%tableSize);
}

int collisionCount(char ** arr,int size)
{
	int i,index,count = 0;
	int temp[tableSize];
	for(i = 0; i < tableSize; i++)
	{
		temp[i] = -1;
	}
	for(i = 0; i < size; i++)
	{
		index = hashFunction(arr[i]);
		if(temp[index] == -1)
			temp[index] = 1;
		else
			count ++;
	}
	return count;
}


Book* parsing(FILE * fp)
{
	char temp[100000][15];
	char str;
	int z,x;
	char c;
	x=0;
	int count;
	while(1)
	{
		z = 0;
		count = 0;
		c = fgetc(fp);
		if(feof(fp))
			break;
		while((c>='a' && c<='z') || (c>='A' && c<='Z'))
		{
			count = 1;
			temp[x][z] = c;
			z++;
			c = fgetc(fp);
			if(feof(fp))
				break;
		}
		if(count == 1)
		{
			temp[x][z] = '\0';
			x++;
		}
		if(feof(fp))
			break;
	}

	Book* new = (Book *)malloc(sizeof(Book));
	new -> book = (char **)malloc(x*sizeof(char *));
	for(int j = 0; j < x; j++)
	{
		new->book[j] = (char *)malloc((strlen(temp[j])+1)*sizeof(char));
		strcpy(new->book[j],temp[j]);
	}
	new -> size = x;
	return new;
}

void profiling(char ** book, int size)
{
	int baseNumber1[3][6];
	int tableSize1[3];
	tableSize1[0] = 5000;
	tableSize1[1] = 50000;
	tableSize1[2] = 500000;
	int baseindexmin;
	int tableindexmin;
	int count;
	int countmin = 1000000;
	int basenumin,tablemin;
	for(int i = 0; i < 3; i++)
	{
		int basecount = 0;
		for(int z = tableSize1[i]; z < 2*tableSize1[i];z++)
		{
			int flag = 0;
			for(int j = 2; j < z/2; j++)
			{
				if(z%j == 0)
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				baseNumber1[i][basecount] = z;
				basecount++;
			}
			if(basecount >= 3)
				break;
		}
		for(int z = 1000*tableSize1[i];;z++)
		{
			int flag = 0;
			for(int j = 2; j < z/2; j++)
			{
				if(z%j == 0)
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				baseNumber1[i][basecount] = z;
				basecount++;
			}
			if(basecount >= 6)
				break;
		}
	}
	int i = 0;
	while(i < 3)
	{
		tableSize = tableSize1[i];
		for(int z = 0; z < 6; z++)
		{
			baseNumber = baseNumber1[i][z];
			count = collisionCount(book,size);

			if(count < countmin)
			{
				countmin = count;
				basenumin = baseNumber1[i][z];
				tablemin = tableSize1[i];
				baseindexmin = z+1;
				tableindexmin = i+1;
			}
		}
		i++;
	}
	baseNumber = basenumin;
	tableSize = tablemin;
	printf("best choice of basenumber is %d index is %d and for tableSize is %d index is %d which gives count %d \n",basenumin,baseindexmin,tablemin,tableindexmin,countmin);
}

int main (){
    
}