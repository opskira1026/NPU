#include <stdio.h>

#define HEAP_SIZE 1024

typedef enum BLOCK_STATE
{
    FREE,
    USED

}BLOCK_STATE;

typedef struct BLOCK
{
    size_t size;

    BLOCK_STATE state;

    struct BLOCK* pPrev;
    struct BLOCK* pNext;

}BLOCK;

unsigned char g_heap[HEAP_SIZE];

BLOCK* g_pFirstBlock = NULL;

const char* getStateString(BLOCK_STATE state)
{
    switch (state)
    {
    case FREE:
        return "FREE";

    case USED:
        return "USED";

    default:
        return "UNKNOWN";
    }
}

void initAllocator(void)
{
    BLOCK* pBlock = (BLOCK*)g_heap;

    pBlock->size = HEAP_SIZE - sizeof(BLOCK);
    pBlock->state = FREE;

    pBlock->pPrev = NULL;
    pBlock->pNext = NULL;

    g_pFirstBlock = pBlock;
}

void* myMalloc(size_t size)
{
    BLOCK* current = g_pFirstBlock;

    while (current != NULL)
    {
        // 사용 가능한 Block인가?
        if (current->state == FREE && current->size >= size)
        {
            size_t remain = current->size - size;

            if (remain > sizeof(BLOCK))
            {
                BLOCK* newBlock = (BLOCK*)((char*)current + sizeof(BLOCK) + size);

                newBlock->size = remain - sizeof(BLOCK);
                newBlock->state = FREE;

                newBlock->pPrev = current;
                newBlock->pNext = current->pNext;

                if (current->pNext != NULL)
                {
                    current->pNext->pPrev = newBlock;
                }
                current->pNext = newBlock;
                current->size = size;
            }
            current->state = USED;

            return (void*)((char*)current + sizeof(BLOCK));
        }
        current = current->pNext;
    }
    return NULL;
}
void mergeBlock(BLOCK* current)
{
    if (current == NULL)
        return;

    BLOCK* next = current->pNext;

    if (next == NULL)
        return;

    if (current->state == FREE &&
        next->state == FREE)
    {
        current->size = current->size + sizeof(BLOCK) + next->size;
        current->pNext = next->pNext;

        if (next->pNext != NULL)
        {
            next->pNext->pPrev = current;
        }
    }
}

void myFree(void* ptr)
{
    if (ptr == NULL)
        return;

    BLOCK* current = (BLOCK*)((char*)ptr - sizeof(BLOCK));

    current->state = FREE;

    if (current->pPrev != NULL)
    {
        mergeBlock(current->pPrev);
    }
    mergeBlock(current);
}

void printHeap(void)
{
    BLOCK* pCurrent = g_pFirstBlock;

    int index = 0;

    printf("\n========== Heap ==========\n\n");

    while (pCurrent != NULL)
    {
        printf("Block #%d\n", index++);
        printf("Header Address : %p\n", (void*)pCurrent);
        printf("User Address   : %p\n",
            (void*)((char*)pCurrent + sizeof(BLOCK)));
        printf("Size           : %zu\n", pCurrent->size);
        printf("State          : %s\n",
            getStateString(pCurrent->state));
        printf("Prev           : %p\n",
            (void*)pCurrent->pPrev);
        printf("Next           : %p\n",
            (void*)pCurrent->pNext);
        printf("\n");

        pCurrent = pCurrent->pNext;
    }

    printf("==========================\n");
}

int main(void)
{
    initAllocator();
    printf("초기 Heap\n");
    printHeap();

    void* p1 = myMalloc(100);

    printf("100Byte 할당\n");
    printHeap();

    void* p2 = myMalloc(200);

    printf("200Byte 할당\n");
    printHeap();

    void* p3 = myMalloc(150);

    printf("150Byte 할당\n");
    printHeap();


    printf("첫 번째 Block 해제\n");
    myFree(p1);
    printHeap();


    printf("두 번째 Block 해제\n");
    myFree(p2);
    printHeap();


    printf("세 번째 Block 해제\n");
    myFree(p3);
    printHeap();

    return 0;


}