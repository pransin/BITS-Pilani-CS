// Table Size = 5000, Base Number = 5003, Collision count = 22820
// All table sizes and base number give the same collision count because the way to calculate count given in the sheet is not very good. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int tableSize = 5000;
int baseNumber = 5003;

int hash(char str[], int baseNumber, int tableSize)
{
    int sum = 0;
    int len = strlen(str);
    while (len--)
        sum += str[len];
    return (sum % baseNumber) % tableSize;
}

int collisionCount(char *strArray[], int baseNumber, int tableSize)
{
    int count = 0;
    int cArr[tableSize];
    for (int i = 0; i < tableSize; i++)
        cArr[i] = 0;

    // int numStr = strlen(strArray);
    for (int i = 0; strArray[i] != NULL; i++)
    {
        int h = hash(strArray[i], baseNumber, tableSize);
        if (cArr[h] == 1)
            count++;
        else
            cArr[h] = 1;
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

int profiler()
{
    int bestBN;
    int bestTS;
    int bestCC = 500000;
    int tableSizes[] = {5000,50000,500000};
	int baseNumbers[3][6] = {{5003,5009,5011,5000011,5000077,5000081},{50021,50023,50033,50000017,50000021,50000047},{500009,500029,500041,500000003,500000009,500000041}};
    char **book = parse();
    for (int i = 0; i < 3; i++)
    {
        int c = 0;
        for (int j = 0; j < 6; j++)
        {

                int cc = collisionCount(book, baseNumbers[i][j], tableSizes[i]);
                if (cc < bestCC)
                {
                    bestCC = cc;
                    bestBN = baseNumbers[i][j];
                    bestTS = tableSizes[i];
                }
                printf("Table Size = %d, Base Number = %d, Collision count = %d\n", tableSizes[i],baseNumbers[i][j], cc);

        }
    }
    printf("Best Table Size = %d, Best Base Number = %d, Minimum Collision count = %d\n", bestTS, bestBN, bestCC);
    return bestTS;
}

typedef struct node
{
    int first;
    int count;
    struct node *next;
} node;

typedef struct hashTable
{
    int elementCount;
    int insertionCost;
    int queryingCost;
    node **table;
} hashTable;

hashTable *createHashTable()
{
    // int tableSize = profiler();
    hashTable *ht = (hashTable *)malloc(sizeof(hashTable));
    ht->table = (node **)malloc(sizeof(node *) * tableSize);
    for (int i = 0; i < tableSize; i++)
        ht->table[i] = NULL;

    ht->elementCount = 0;
    ht->insertionCost = 0;
    ht->queryingCost = 0;
}


void insert(hashTable *ht, char *strArray[], int j)
{
    int h = hash(strArray[j], baseNumber, tableSize);

    if (ht->table[h] == NULL)
    {
        node *newNode = (node *)malloc(sizeof(node));
        ht->table[h] = newNode;
        newNode->count = 1;
        newNode->first = j;
        newNode->next = NULL;
        ht->elementCount++;
    }
    else
    {
        node *curr = ht->table[h];
        while (curr->next != NULL && strcmp(strArray[curr->first], strArray[j]) != 0)
        {
            curr = curr->next;
            ht->insertionCost++;
        }
        if (!strcmp(strArray[curr->first], strArray[j]))
        {
            curr->count++;
        }
        else
        {
            node *newNode = (node *)malloc(sizeof(node));
            newNode->next = NULL;
            newNode->first = j;
            newNode->count = 1;
            curr->next = newNode;
            ht->elementCount++;
        }
    }
}

int insertAll(hashTable *ht, char *book[], int size)
{
    for (int i = 0; i < size; i++)
    {
        insert(ht, book, i);
    }
    return ht->insertionCost;
}

node *lookup(hashTable *ht, char *books[], char str[])
{
    int h = hash(str, baseNumber, tableSize); 
    node *curr = ht->table[h];
    while (curr != NULL && strcmp(books[curr->first], str) != 0)
    {
        curr = curr->next;
        ht->queryingCost++;
    }
    return curr;
}

int lookupAll(hashTable *ht, char *books[], int size, float m)
{
    int max = m * size;
    ht->queryingCost = 0;
    for (int i = 0; i < max; i++)
    {
        lookup(ht, books, books[i]);
    }
    return ht->queryingCost;
}

// int main()
// {
//     char **book = parse();
//     profiler();
//     hashTable *myTable = createHashTable();
//     printf("%d\n", insertAll(myTable, book, 23606)); //23606 Number of valid strings
//     printf("%d\n", lookupAll(myTable, book, 23606, 0.05));
// }