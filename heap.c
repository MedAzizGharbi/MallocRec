#include <stdio.h>
#include <unistd.h>

typedef struct block_meta {
    int size;
    int is_free;
    struct block_meta *next;
} block_meta;

#define BLOCK_SIZE sizeof(block_meta)

block_meta *free_list = NULL;

void *my_malloc(size_t size){
    if(size <= 0) return NULL;
    size_t total_size = size + BLOCK_SIZE;
    block_meta *block = sbrk(total_size);
    if(block == (block_meta *)-1){
        printf("allocation failed");
        return NULL;
    }
    block->size = size;
    block->is_free = 0;
    block->next = NULL;
    return (void *)(block + 1);
}

void myfree(void *ptr){
    if(!ptr) return;
    block_meta *block = (block_meta *)ptr - 1;
    block->is_free = 1;
}

int main(int argc, char *argv[])
{
    int *arr = (int *)my_malloc(5 * sizeof(int));
    for(int i = 0 ; i < 5 ; i++){
        arr[i] = i;
    }
    for(int i = 0 ; i < 5 ; i++){
        printf("%p\n" , &arr[i]);
        printf("%d\n", arr[i]);
    }
    myfree(arr);
    return 0;
}
