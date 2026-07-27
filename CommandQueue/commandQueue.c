#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct COMMAND
{
	int commandID;
	char operation[32];
	struct COMMAND* pNext;

} COMMAND;

COMMAND* g_pHeadCommand = NULL;

void enqueue(int i, const char* op)
{
	COMMAND* newCommand = (COMMAND*)malloc(sizeof(COMMAND));

	if (newCommand == NULL)
	{
		printf("동적할당 받지 못했습니다.");
		exit(1);
	}

	newCommand->commandID = i;
	strcpy_s(newCommand->operation, sizeof(newCommand->operation), op);
	newCommand->pNext = NULL;

	if (g_pHeadCommand == NULL)
		g_pHeadCommand = newCommand;
	else
	{
		COMMAND* pTailCommand = g_pHeadCommand;
		while (pTailCommand->pNext != NULL)
			pTailCommand = pTailCommand->pNext;
		pTailCommand->pNext = newCommand;
	}
}

COMMAND* dequeueCommand(void)
{
	COMMAND* pHeadCommand = g_pHeadCommand;
	COMMAND* pRemoveCommand = NULL;

	if (pHeadCommand == NULL)
		return NULL;
	else
	{
		pRemoveCommand = g_pHeadCommand;
		g_pHeadCommand = pHeadCommand->pNext;
	}
		 
	return pRemoveCommand;
}

void destroyCommand(COMMAND* pRemove)
{
	free(pRemove);
}

void releaseQueue(void)
{
	COMMAND* pTmp = g_pHeadCommand;
	COMMAND* pDelete = NULL;

	while (pTmp != NULL)
	{
		pDelete = pTmp;

		printf("release : [%p] %d %s [%p]\n",
			pDelete, pDelete->commandID, pDelete->operation, pDelete->pNext);

		pTmp = pDelete->pNext;
		free(pDelete);
	}

	if (pTmp == NULL)
		printf("Queue Empty");
}


void executeCommand(COMMAND* pRemove)
{
	printf("[NPU]\n");
	printf("EXECUTE Command\n");
	printf("ID : %d\n", pRemove->commandID);
	printf("Operation : %s\n", pRemove->operation);
	putchar('\n');
}

void fcreateCommand(void)
{
	enqueue(1, "CONV");
	enqueue(2, "ReLU");
	enqueue(3, "POOL");
	enqueue(4, "SOFTMAX");
}

void printCommand(void)
{
	COMMAND* printCommand = g_pHeadCommand;
	
	printf("Current Queue\n");

	while (printCommand != NULL)
	{
		printf("create : [%p] %d %s [%p]\n",
			printCommand, printCommand->commandID, printCommand->operation, printCommand->pNext);

		printCommand = printCommand->pNext;
	}

	putchar('\n');
}


int main(void)
{
	// command 입력
	fcreateCommand();
	// command 출력
	printCommand();
	// head 제거
	for (int i = 0; i < 4; i++)
	{
		COMMAND* removeHead = dequeueCommand();
		printCommand();
		// 제거될 헤드 출력
		executeCommand(removeHead);
		// 제거될 헤드 동적할당 해제
		destroyCommand(removeHead);
	}
	// 모든 노드 동적할당 해제
	releaseQueue();

	return 0;
}