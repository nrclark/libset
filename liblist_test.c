#include <stdio.h>
#include "liblist.h"

int main(void) {
    node_t *top = NULL;
    //list_print(top);

    top = list_create_top((void *)48);

    list_insert_after(top, (void *)49);
    list_insert_before(top, (void *)46);
    top = top->prev;
    list_insert_after(top, (void *)47);
    list_print(top);

    list_destroy_after(top->next->next);
    list_print(top);
    
    list_destroy(top);
    return 0;
}
