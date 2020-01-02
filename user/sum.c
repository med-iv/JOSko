#include <inc/lib.h>

void
umain(int argc, char **argv)
{
    char *end;
    cprintf("%ld\n", strtol(argv[1], &end, 10) + strtol(argv[2], &end, 10));
}