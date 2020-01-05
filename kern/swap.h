#ifndef LAB_SWAP_H
#define LAB_SWAP_H


#include <inc/memlayout.h>
//#include <kern/env.h>
#include <kern/lz4.h>

//uint32_t swap_bitmap[];

char *SwapBuffer;

char *SwapShift;

char *CompressionBuffer;

struct lru_list1 {
    struct PageInfo *head;
    struct PageInfo *tail;
    char *buffer;
    int size;
};

struct lru_list1 *lru_list;

void swap_init();

void add_to_lru_list(struct PageInfo *pg);
void delete_from_lru_list(struct PageInfo *pg);


#endif //LAB_SWAP_H
