#include <stdio.h>

#define HEAP_SIZE 1024

typedef enum BLOCKSTATE
{
	FREE,
	USER

} BLOCKSTATE;

typedef struct BLOCK
{
	int size;
	BLOCKSTATE state;

	struct BLOCK* pPrev;
	struct BLOCK* pNext;
} BLOCK;

unsigned char g_heap[HEAP_SIZE];
BLOCK* g_pFirstBlock = NULL;

const char* getStateString(int state)
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
	BLOCK* firstBlock = (BLOCK*)g_heap;

	firstBlock->size = HEAP_SIZE;
	firstBlock->state = 0;
	firstBlock->pPrev = NULL;
	firstBlock->pNext = NULL;

	g_pFirstBlock = firstBlock;
}

int main(void)
{
	Init();

	/*printf("%d %s %p %p",
		g_pFirstBlock->size, getStateString(g_pFirstBlock->state),
		g_pFirstBlock->pPrev, g_pFirstBlock->pNext);*/



	return 0;
}