#include <stdio.h>
#include "liblist.h"

int main(void)
{
    listnode_t *top = NULL;
    //list_print(top);

    top = list_create();

    list_insert_after(top, (void *)0xE0);
    list_insert_after(top, (void *)0xD0);
    list_insert_after(top, (void *)0xC0);
    list_insert_after(top, (void *)0xB0);
    list_insert_after(top, (void *)0xA0);

    list_insert_before(list_index(top, 5), (void *)0x77);

    list_print(top);

    list_destroy(top);
    return 0;
}
