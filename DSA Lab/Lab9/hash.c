#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int hash(char* str, int base, int tableSize){
	int sum = 0;
    // int size = sizeof(str)/sizeof(char);
	for(int i=0;i<strlen(str);i++)
	{
		sum+=((int)str[i]);
	}
	int hashVal = (sum%base)%tableSize;
	return hashVal;
}

int collision_count(char** stringArr, int base, int tableSize){
	int ht[tableSize];
	for(int i=0;i<tableSize;i++){
		ht[i] = 0;
	}
	int count = 0;
	for(int i=0;stringArr[i]!=NULL;i++){ // stringArr[i] corresponds to pointer to the string. 
	 	int index = hash(stringArr[i],base,tableSize);
	 	if(ht[index] == 1)
	 		count++;
	 	else {
	 		ht[index] = 1;
	 	}
	}	
	return count;
}

char **parse()
{
    FILE *ptr = fopen("aliceinwonderland.txt", "r");
    if (ptr == NULL)
    {
        printf("Unable to open file\n");
        exit(1);
    }
    int num = 0; //Number of words stored
    int size = 10000;
    char **book = (char **)malloc(sizeof(char *) * size);

    char temp[200];
    char t = ' ';
    for (int i = 0; feof(ptr) == 0 && t != EOF;)
    {

        int res = fscanf(ptr, "%[a-zA-Z]s", temp);
        t = fgetc(ptr);
        if (res <= 0)
            continue;
        if (!isalpha(t) && !isspace(t) && t != EOF)
        {
            ungetc(t, ptr);
            fscanf(ptr, "%s", temp);
            // printf("helllo\n");
            continue;
        }

        if (i == size)
        {
            size = (4 * size) / 3;
            book = (char **)realloc(book, sizeof(char *) * size);
        }

        book[i] = (char *)malloc(sizeof(char) * 50);
        strcpy(book[i], temp);
        num++;
        i++;
    }
    printf("Number of words = %d\n", num);
    return book;
}

int isPrime(int x)
{
	for(int i=2;i*i<=x;i++)
	{
		if(x%i==0)
			return 0;
	}
	return 1;
}

void profiling(char **stringArr)
{
	int table = 5000;
	char **tracker;
	tracker = stringArr;
	int minCollisions=100000;
	for(int t = 0;t<3;t++){
	    int count = 0, temp;
		for(int i = table;i<=2*table && count <3;i++){
	
			if(isPrime(i)){
				count++;
				temp =  collision_count(stringArr, i, table);
				printf("Collision count - %d, Base - %d, TableSize - %d\n",temp,i,table);
	
				if(temp < minCollisions) minCollisions = temp;
			}
		}
		count = 0;
		int x = 1000*table; 
		while(count<3){
			if(isPrime(x)){
				temp =  collision_count(stringArr,  x, table);
				printf("Collision count - %d, Base - %d, TableSize - %d\n",temp,x,table);
				if(temp < minCollisions) minCollisions = temp;
                count++;
			}
			x++;
		}
		table *= 10;
	}
    printf("Minimum collision count - %d\n", minCollisions);
}

typedef struct node Node;
struct node {
	int startIndex;
	int count;
	Node* next;
};

typedef struct HashTable {
	int tableSize;
	int base;
	Node** table;
	int elementCount;
	int insertionCost;
	int queryingCost;
} HashTable;

Node* newNode(){
	Node* temp = malloc(sizeof(Node));
	temp->startIndex=0;
	temp->count=0;
	temp->next = NULL;
	return temp;
}

HashTable* createHashTable(int tableSize,int base){
	HashTable* tempTable = malloc(sizeof(HashTable));
	tempTable->tableSize = tableSize;
	tempTable->base = base;
	tempTable->table = (Node**)malloc(sizeof(Node*)*tableSize);
	for(int i=0;i<tableSize;i++){
		tempTable->table[i] = NULL;
	}
	tempTable->elementCount = 0;
	tempTable->insertionCost = 0;
	tempTable->queryingCost = 0;
	return tempTable;
}

void insert(char** stringArr, int index, HashTable* hashTable){
	int hashedVal = hash(stringArr[index],hashTable->base,hashTable->tableSize);

	if(hashTable->table[hashedVal] == NULL){
		hashTable->table[hashedVal] = newNode();
		hashTable->table[hashedVal]->count = 1;
		hashTable->table[hashedVal]->startIndex = index;
		hashTable->table[hashedVal]->next = NULL;
		hashTable->elementCount++;
	}
	else{
		Node* curr = hashTable->table[hashedVal];
		while(curr->next!=NULL && (strcmp(stringArr[index], stringArr[curr->startIndex]))){
			hashTable->insertionCost++;
			curr=curr->next;
		}
		if(!(strcmp(stringArr[index], stringArr[curr->startIndex]))){
			curr->count++;
		}
		else{
			Node* temp = newNode();
			temp->startIndex = index;
			temp->count = 1;
			temp->next = NULL;
			curr->next = temp;
		}
	}
}

int insertAll(char** stringArr, int size, HashTable* hashTable){
	for(int i=0;i<size;i++){
		insert(stringArr, i, hashTable);
	}
	return hashTable->insertionCost;
}

Node* lookup(char** stringArr, int index, HashTable* hashTable){
	int hashedVal = hash(stringArr[index], hashTable->base, hashTable->tableSize);
	Node* curr = hashTable->table[hashedVal];
	while(curr != NULL && strcmp(stringArr[index], stringArr[curr->startIndex])){
		hashTable->queryingCost++;
		curr=curr->next;
	} 

	return curr;
}

int lookupAll(char** stringArr, int size, HashTable* hashTable, double m){
	hashTable->queryingCost=0;

	for(int i=0;i<(int)(m*size);i++){
		lookup(stringArr,i, hashTable);
	}
	return hashTable->queryingCost;
}



int main(){
	char ** books;
	int size = 22698; //Number of words.
	books = parse();
	profiling(books);
	int base = 50033;
	int tableSize = 50000;

	HashTable* hashTable = createHashTable(base, tableSize);
	insertAll(books, size, hashTable);
	return 0;
}