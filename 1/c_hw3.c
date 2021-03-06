#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"header.h"

int main()
{
	char name[10][20];
	int i;
	FILE* fp = fopen("student.txt", "rt");
	node* n=NULL;
	srand(time(NULL));

	for (i = 0; i < 10; i++) {//이름을 배열에 저장
		fscanf(fp, "%s", name[i]);
	}
	fclose(fp);
	
	list* l = createlist();

	for (i = 0; i < 10; i++)//게임 10번 진행
	{
		int j = rand() % 10;
		if (name[j][0] == NULL) {
			i--;
			continue;
		}
		n = play(l, n, name[j], i + 1, j%(10-i));
		printf("dead No.%d  %s  Bullet No.%d \n", n->deathNo, n->stu_name, n->bullNo);
		name[j][0] = NULL;
	}

	delete(l);
	scanf("%d", &i);
	return 0;
}

list* createlist()//리스트 생성
{
	list* l = (list*)malloc(sizeof(list));
	l->count = 0;
	l->link = NULL;
	l->rear = NULL;
	return l;
}

node* play(list* l, node* n, char* name, int num, int num2)//노드 생성
{
	node* ptr = (node*)malloc(sizeof(node));
	strcpy(ptr->stu_name, name);//데이터 저장
	ptr->deathNo = num;
	ptr->bullNo = num2;
	if (n == NULL) {//링크 설정
		l->link = ptr;
		l->count++;
		ptr->link = ptr;
	}
	else {
		n->link = ptr;
		ptr->link = l->link;
		l->rear = ptr;
		l->count++;
	}

	return ptr;
}

void delete(list* l)//메모리 해제
{
	node* n1, *n2;
	n1 = l->link;
	while (l->count) {
		n2 = n1->link;
		free(n1);
		n1 = n2;
		l->count--;
	}
	free(l);
}