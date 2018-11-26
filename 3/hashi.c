#define _CRT_SECURE_NO_WARNINGS
#include "hash.h"
#include<stdlib.h>
#include<string.h>

HASHTABLE* createHASHTable(int maxSize)
{
	HASHTABLE* hash;
	int i;

	hash = (HASHTABLE*)malloc(sizeof(HASHTABLE));
	if (!hash)
		return NULL;

	hash->compare = _compareString;
	hash->hf = _hfString;
	hash->maxSize = maxSize;
	hash->hTable = (HNODE*)calloc(hash->maxSize, sizeof(HNODE));

	for (i = 0; i<maxSize; i++) {
		hash->hTable[i].dataPtr = NULL;
		hash->hTable[i].freq = 0;// for word count example
		hash->hTable[i].next = NULL;
	}

	return hash;
}

int _hfString(char* Key, int max)
{
	int addr, i;
	int keyLen;

	keyLen = strlen(Key);
	addr = 0;

	for (i = 0; i < keyLen; i++)
		if (Key[i] != ' ')
			addr += Key[i];
	return(addr % max);
}

int _hfInt(int Key, int max)
{
	return(Key % max);
}


void printLink(HNODE* pList)
{
	HNODE* cPtr;
	cPtr = pList;
	while (cPtr) {
		printf("-> ");
		printf("%s(%d)\t", (char*)cPtr->dataPtr, cPtr->freq);
		cPtr = cPtr->next;
	}
	return;
}
void printHashTable(HASHTABLE* hash)
{
	int i;
	for (i = 0; i < hash->maxSize; i++) {
		printf("%s(%d) ", (char*)hash->hTable[i].dataPtr, hash->hTable[i].freq);
		printLink(hash->hTable[i].next);
		printf("\n");
	}
	printf("\n");
	return;

}

int HASHsearchInsert(HASHTABLE * hash, void * dataInPtr)
{
	int addr;
	int found;
	int success;
	HNODE* pPre, *pLoc;

	addr = hash->hf(dataInPtr, hash->maxSize);
	if (hash->hTable[addr].dataPtr == NULL)
	{
		hash->hTable[addr].dataPtr = _makeDataNode(dataInPtr);
		hash->hTable[addr].freq = 1;
		hash->hTable[addr].next = NULL;
		return 1;
	}
	else // collision
	{
		if (hash->compare(hash->hTable[addr].dataPtr, dataInPtr) == 0)
		{// already existed key value
			++(hash->hTable[addr].freq);
			return 0;

		}
		else {
			found = _search(hash->hTable[addr].next, &pPre, &pLoc, dataInPtr, hash->compare);
			if (found) // arleady existed 

				return 0;
			else {
				success = _insert(&(hash->hTable[addr].next), pPre, dataInPtr);
				return 1;
			}

		}//else

	}// else collision
}//HASHsersch&insert

int _search(HNODE * pList, HNODE** pPre, HNODE** pLoc, void* data,
	int(*compare) (void* argu1, void* argu2))
{
	int found;

	*pPre = NULL;
	*pLoc = pList;

	if (pList == NULL)  return 0;
	while (*pLoc != NULL)
	{
		found = compare(data, ((*pLoc)->dataPtr));
		if (!found) // founded
		{
			++((*pLoc)->freq);
			return 1;
		}
		if (found >= 1)
		{// new data is grater that current node
			*pPre = *pLoc;
			if ((*pLoc) == NULL)
				break;// last node
			*pLoc = (*pLoc)->next;
		}
		else break;

	}
	return 0;
}

int _insert(HNODE** pList, HNODE * pPre, void* data)
{
	HNODE * pNew;

	if (!(pNew = (HNODE*)malloc(sizeof(HNODE))))
		return 0;

	pNew->dataPtr = _makeDataNode(data);
	pNew->freq = 1;
	pNew->next = NULL;

	if (pPre == NULL) // adding to empty list or before first node 
	{
		pNew->next = (*pList);
		*pList = pNew;
	}
	else {// adding in middle or at end
		pNew->next = pPre->next;
		pPre->next = pNew;
	}
	return 1;
}

void* _makeDataNode(void *data)
{
	void *dataInPtr;

	dataInPtr = (char *)malloc(MAXSTRING * sizeof(char));
	if (dataInPtr == NULL) {
		printf("malloc fail\n");
		return NULL;
	}
	strcpy((char*)dataInPtr, (char *)data);
	return dataInPtr;
}

int _compareString(void* argu1, void* argu2)
{
	return strcmp((char*)argu1, (char*)argu2);
}