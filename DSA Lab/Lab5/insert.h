long long unsigned stackTop;

typedef struct CREDIT_CARD
{
    unsigned long long cardno;
    char bankcode[6];
    char expirydate[8];
    char firstname[30];
    char lastname[30];
} CREDIT_CARD;

CREDIT_CARD *readRecords(FILE *records);
void insertInOrder(CREDIT_CARD card, CREDIT_CARD *card_array, int index);
void InsertionSort(CREDIT_CARD *card_array, int size);