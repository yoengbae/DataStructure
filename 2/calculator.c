#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

int main()
{
	stack* pstack = CreateStack();
	char arr[100];
	printf("수식 입력: ");
	postfix(pstack, arr);
	printf("%s \n", arr);
	printf("%d \n", calculate(pstack, arr));

	getchar();
	return 0;
}

stack *CreateStack()
{
	stack *pStack = (stack *)malloc(sizeof(stack));
	if (pStack == NULL)
		return NULL;

	pStack->size = 100;
	pStack->top = -1;

	pStack->stack = (int *)malloc((pStack->size) * sizeof(int));
	if (pStack->stack == NULL) {
		free(pStack);
		return NULL;
	}

	return pStack;
}

void postfix(stack* st, char* arr)
{
	char token;
	char arr2[100];
	int i;
	scanf("%s", arr2);
	getchar();

	for(i=0; arr2[i]; i++)
	{
		token = arr2[i];
		if (token == '(') {
			Push(st, '(');
		}
		else if (token == ')') {
			while (st->stack[st->top] != '(') {
				*arr++ = Pop(st);
			}
			Pop(st);
		}
		else if(is_oper(token)){
			while (!is_empty(st) && pri(st->stack[st->top]) >= pri(token)) {
				*arr++ = Pop(st);
			}
			Push(st, token);
		}
		else {
			*arr++ = token;
			if (is_oper(arr2[i+1]))
				*arr++ = ' ';
		}
	}
	while(!is_empty(st))
		*arr++ = Pop(st);
	*arr = 0;
}

int pri(char i) {
	if (i == '+' || i == '-')
		return 1;
	else if (i == '*' || i == '/')
		return 2;
	else
		return 0;
}

int is_oper(char i) {
	return i == '+' || i == '-' || i == '*' || i == '/';
}

int calculate(stack* st, char* arr)
{
	int i, op1, op2;
	while (*arr) {
		if (*arr >= '0'&&*arr <= '9') {
			i = 0;
			while (*arr >= '0'&&*arr <= '9') {
				i = 10 * i + *arr - '0';
				arr++;
			}
			Push(st, i);
		}
		if (is_oper(*arr)) {
			op2 = Pop(st);
			op1 = Pop(st);
			if (*arr == '+')
				Push(st, op1 + op2);
			else if (*arr == '-')
				Push(st, op1 - op2);
			else if (*arr == '/')
				Push(st, op1 / op2);
			else if (*arr == '*') {
				Push(st, op1 * op2);
				
			}
		}
		arr++;
	}
	return Pop(st);
}