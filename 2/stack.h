typedef struct stack {
	int* stack;
	int size;
	int top;
}stack;

void Push(stack *pStack, int item)
{
	if (pStack->top == pStack->size - 1)
		return;
	pStack->stack[++pStack->top] = item;
}

int Pop(stack *pStack)
{
	// check if stack is empty
	if (pStack->top < 0)
		return 0;
	return pStack->stack[pStack->top--];
}

int is_empty(stack *pStack)
{
	if (pStack->top < 0)
		return 1;
	else
		return 0;
}

stack *CreateStack();
void postfix(stack* st, char* arr);
int is_oper(char);
int pri(char);
int calculate(stack*, char*);