#include <stdio.h>

// Allan Jean-Jacuqes 

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
    struct RecordType* recordsList;
};

// Compute the hash function
int hash(int x, int hashSz)
{
    return x % hashSz;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		
        // Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
    {
        struct RecordType* record = pHashArray[i].recordsList;
        if (record != NULL)
        {
            printf("index %d ->", i);
            while (record != NULL)
            {
                printf(" %d, %c, %d ->", record->id, record->name, record->order);
                record = record->next;
            }
            printf(" NULL\n");
        }
    }
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);

	// Hash Table implentation

    struct HashType* pHashArray = (struct HashType*)malloc(sizeof(struct HashType) * hashSz);
    
    if (pHashArray == NULL)
    {
        printf("Cannot allocate memory for the hash table\n");
        return -1;
    }

    // Initialize the hash table
    int i;
    for (i = 0; i < hashSz; ++i)
    {
        pHashArray[i].recordsList = NULL;
    }

    // Insert records into the hash table
    for (i = 0; i < recordSz; ++i)
    {
        int index = hash(pRecords[i].id, hashSz);
        pRecords[i].next = pHashArray[index].recordsList;
        pHashArray[index].recordsList = &pRecords[i];
    }

    displayRecordsInHash(pHashArray, hashSz);

    free(pHashArray);

    return 0;

}