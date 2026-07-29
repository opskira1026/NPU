#include <stdio.h>

#define HEAP_SIZE 1024

typedef enum BLOCK_STATE
{
	FREE,
	USER

} BLOCK_STATE;

typedef struct BLOCK
{
	size_t size;
	BLOCK_STATE state;

	struct BLOCK* pPrev;
	struct BLOCK* pNext;
} BLOCK;

unsigned char g_heap[HEAP_SIZE];
BLOCK g_TailDummyNode = { 0 };
BLOCK* g_pFirstBlock = NULL;

const char* getStateString(BLOCK_STATE state)
{
	switch (state)
	{
	case FREE:
		return "FREE";
	case USER:
		return "USER";
	default:
		return "UNKNOWN";
	}
}

void Init(void)
{
	BLOCK* InitBlock = (BLOCK*)g_heap;

	// 메모리의 실제 값은 1024가 아닌 BLOCK 값을 빼줘야 함
	// header 정보 또한 메모리에 저장되므로 그 값을 빼줘야 
	// 오버플로우가 발생하지 않음
	InitBlock->size = HEAP_SIZE - sizeof(BLOCK);
	InitBlock->state = FREE;
	InitBlock->pPrev = NULL;
	InitBlock->pNext = NULL;

	g_pFirstBlock = InitBlock;

	printf("---------------------------------\n");
	printf("|\t\t%s\t\t|\n", getStateString(InitBlock->state));
	printf("---------------------------------\n\n");

}

void myMalloc(BLOCK* header)
{
	BLOCK* newBlock = (BLOCK*)(char*)header + sizeof(header) + 

}

void printHeap(BLOCK* blk)
{
	int i = 0;
	BLOCK* pTmp = g_pFirstBlock;
	
	//printf("%zu\n", sizeof(BLOCK));
	//printf("Address : %p", (char*)blk + sizeof(BLOCK));

	while (pTmp != NULL)
	{
		printf("------------------------------\n");
		printf("block : %d\n", i++);
		printf("block size : %zu\n", sizeof(BLOCK));
		printf("address : %p\n", (char*)blk + sizeof(blk));
		printf("size : %zd\n", blk->size);
		printf("state : %s\n", getStateString(blk->state));
		printf("------------------------------\n\n");
		break;
		
	
	}


	//while (g_pFirstBlock != NULL)
	//{

	//	g_pFirstBlock = g_pFirstBlock->pNext;
	//}
}

int main(void)
{
	Init();
	printHeap(g_pFirstBlock);
	/*printf("%d %s %p %p",
		g_pFirstBlock->size, getStateString(g_pFirstBlock->state),
		g_pFirstBlock->pPrev, g_pFirstBlock->pNext);*/



	return 0;
}