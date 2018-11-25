#define MAXSTRING 20

typedef struct hnode 
{
	void * dataPtr;
	int freq;
	struct hnode *next;
} HNODE;

typedef struct {
  	HNODE* hTable;
  	int (*compare) (void * argu1, void * argu2);
  	int (*hf) (void * argu1, int);
  	int maxSize;
} HASHTABLE;

HASHTABLE* createHASHTable(int maxSize);
int HASHsearchInsert(HASHTABLE * hash,void * dataInPtr);
void printHashTable(HASHTABLE* hash);
int _compareString(void* argu1, void* argu2);
int _hfString(char* key,int max);
void* _makeDataNode(void *data);
int _search(HNODE * pList,HNODE** pPre,HNODE** pLoc,void* data,
		int(*compare) (void* argu1,void* argu2));
int _insert(HNODE** pList,HNODE * pPre,void* data);
