#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hash.h"
#define MAXHASHTABLE 100
#define MAXSTRING 20
#define MAXCHARINLINE 80

int main(int argc, char *argv[])
{
	HASHTABLE* myHashTable;
	int result;
	char dataInPtr[MAXSTRING];
	char ch;// dir is direction of DLL
	char Line[80];
	char *token;
	char fname[50];// file name
	FILE *fin;// for word count examples
	char fline[80]; // for string in a file

	while (1) {
		printf("\n Menu...............\n");
		printf("type -> I : create a HASHTABLE\n");
		printf("type -> F : word usage count in a file\n");
		printf("type -> s : show all Node in the Heap\n");
		printf("type -> q : quit program\n");
		switch (ch = getchar())
		{
		case 'I':
			fflush(stdin);
			myHashTable = createHASHTable(100);
			break;
		case 'f':
		case 'F':
			fflush(stdin);
			printf("type file name -> ");
			scanf("%s", fname);
			if ((fin = fopen(fname, "r")) == NULL) {
				printf("fopen error \n");
				break;
			}
			while (fgets(fline, MAXCHARINLINE, fin) != NULL)
			{
				token = strtok(fline, " (){}=!'*/+><%\;,[]:-_.\t\n");
				while (token != NULL)
				{
					result = HASHsearchInsert(myHashTable, token);
					token = strtok(NULL, " (){}=!'*/+><%\;,[]:-_.\t\n");
				}
			}// fgets 
			fclose(fin);
			fflush(stdin);
			break;
		case 's':
		case 'S':
			printf("\n print myHashTable internal \n");
			printHashTable(myHashTable);
			fflush(stdin);
			break;
		case 'q':
		case 'Q':
			return 1;
			break;
		}// end of switch
	}// end of while
	return 1;
}/* end of main */
