#include <kern/swap.h>

#include <kern/lz4.h>

#include <inc/lib.h>


#define Test 1

void swap_init()
{
#ifdef Test

    char src[] = "Ветер в поле закружил\n"
                    "Ветер в поле закружил\n"
                    "Ветер в поле закружил\n"
                    "Ветер в поле закружил\n"
                    "\n"
                    "     Лоботомия \n"
                    "\n"
                    "Поздний дождик напугал\n"
                    "Поздний дождик напугал\n"
                    "Поздний дождик напугал\n"
                    "Поздний дождик напугал\n"
                    "\n"
                    "     Лоботомия\n"
                    "\n"
                    "Зацвела в саду сирень\n"
                    "Зацвела в саду сирень\n"
                    "Зацвела в саду сирень\n"
                    "Зацвела в саду сирень\n"
                    "\n"
                    "     Лоботомия\n"
                    "\n";;

    char dst[LZ4_compressBound(321)];
    cprintf("%d\n", LZ4_compressBound(4096));
    int cur_size = LZ4_compress_default(src, dst, 321, LZ4_compressBound(321));
    cprintf("%d\n", LZ4_compressBound(cur_size));
    cprintf("%s\n", dst);
    char final[321];
    LZ4_decompress_safe(dst, final, cur_size, 321);
    cprintf("%s\n", final);
#endif

}

void swap_shift(int k)
{
    char * tmp = swap_info[k].buffer;
    for (int i = k; i < SWAP_AMOUNT - 1; i++) {
        memmove(tmp, swap_info[i + 1].buffer, swap_info[i + 1].size);
        tmp += swap_info[i + 1].size;
        swap_info[i + 1].buffer = tmp;
        swap_info[i].size = swap_info[i + 1].size;
    }
}


void add_to_lru_list(struct PageInfo *pg)
{
    if (lru_list->size) {
        pg->lru_next = lru_list->head;
    }

    if (lru_list->) {
        (lru_list->tail)->lru_next = pg;
    }
    if (lru_list->size == 0) {
        lru_list->head = pg;
    }

    lru_list->tail = pg;
    lru_list->size += 1;
}

void delete_from_lru_list(struct PageInfo *pg)
{
    if (pg->lru_prev != NULL) {
        pg->lru_prev->lru_next = pg->lru_next;
    }
    else {
        lru_list->head = pg->lru_next;
    }

    if (pg->lru_next != NULL) {
        pg->lru_next->lru_prev = pg->lru_prev;
    }
    else {
        lru_list->tail = pg->lru_prev;
    }

    lru_list->size -= 1;

    pg->lru_next = pg->lru_prev = NULL;
}