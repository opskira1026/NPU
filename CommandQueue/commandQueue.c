#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct COMMAND
{
	int commandID;
	char operation[32];
	struct COMMAND* pNext;

} COMMAND;

// 해당 방식으로 싱글 링크드리스트를 사용하면, 조건이 많아지는 문제가 있음.
// 따라서 더미 헤드를 사용하여 조건을 줄이는 방향으로 로직을 구성.
//COMMAND* g_pHeadCommand = NULL;
COMMAND g_DummyHead = { 0, "__DUMMY HEAD__" };

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

	//if (g_pHeadCommand == NULL)
	//	g_pHeadCommand = newCommand;
	//else
	//{

	//	// 현재 구현은 Tail을 매번 탐색하므로 enqueue가 O(N) 
	//	// 실제 Runtime에서는 Tail 포인터를 함께 관리하여 O(1)로 구현한다.
	//	COMMAND* pTailCommand = g_pHeadCommand;
	//	while (pTailCommand->pNext != NULL)
	//		pTailCommand = pTailCommand->pNext;
	//	pTailCommand->pNext = newCommand;
	//}

	if (g_DummyHead.pNext == NULL)
		g_DummyHead.pNext = newCommand;
	else
	{
		COMMAND* pTailCommand = g_DummyHead.pNext;
		while (pTailCommand->pNext != NULL)
			pTailCommand = pTailCommand->pNext;
		pTailCommand->pNext = newCommand;
	}
}

COMMAND* dequeueCommand(void)
{
	COMMAND* pHeadCommand = g_DummyHead.pNext;
	COMMAND* pRemoveCommand = NULL;

	if (pHeadCommand == NULL)
		return NULL;
	else
	{
		pRemoveCommand = g_DummyHead.pNext;
		g_DummyHead.pNext = pHeadCommand->pNext;
	}
	//지워질 대상이니 다음 노드를 가리킬 필요없음
	pRemoveCommand->pNext = NULL;
		 
	return pRemoveCommand;
}

void destroyCommand(COMMAND* pRemove)
{
	// 조건 추가
	// input이 NULL일때도 안전하게
	if (pRemove == NULL)
		return;
	
	free(pRemove);
}

void releaseQueue(void)
{
	COMMAND* pTmp = g_DummyHead.pNext;
	COMMAND* pDelete = NULL;

	while (pTmp != NULL)
	{
		pDelete = pTmp;

		printf("release : [%p] %d %s [%p]\n",
			pDelete, pDelete->commandID, pDelete->operation, pDelete->pNext);

		pTmp = pDelete->pNext;
		free(pDelete);
	}

	putchar('\n');
}


void executeCommand(COMMAND* pRemove)
{
	if (pRemove == NULL)
		return;

	putchar('\n');
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
	COMMAND* printCommand = g_DummyHead.pNext;
	
	printf("Current Queue\n");
	printf("------------------------------------------------------\n");

	while (printCommand != NULL)
	{
		printf("create : [%p] %d %s [%p]\n",
			printCommand, printCommand->commandID, printCommand->operation, printCommand->pNext);

		printCommand = printCommand->pNext;
	}

	printf("------------------------------------------------------\n");
	putchar('\n');

	// 반복문이 끝나면 pTmp는 항상 참
	// g_pHeadCommand가 NULL일 경우에 빈 Queue를 출력
	if (g_DummyHead.pNext == NULL)
		printf("Queue Empty\n");
}


int main(void)
{
	// command 입력
	fcreateCommand();
	// command 출력
	printCommand();
	COMMAND* cmd;

	while((cmd = dequeueCommand()) != NULL)
	{
		// command 출력
		printCommand();
		// 제거될 헤드 출력
		executeCommand(cmd);
		// 제거될 헤드 동적할당 해제
		destroyCommand(cmd);
	}
	// 모든 노드 동적할당 해제
	releaseQueue();

	return 0;
}