#ifndef _LIBLIST_H_
#define _LIBLIST_H_

enum {
    list_eok = 0,
    list_enullptr = -1,
    list_enomem = -2,
    list_eempty = -3,
};

typedef struct listnode_t {
    void *data;
    struct listnode_t *next;
    struct listnode_t *prev;
    struct listnode_t *top;
} listnode_t;

listnode_t *list_create(void);
listnode_t *list_index(listnode_t *node, unsigned int index);

int list_insert_after(listnode_t *node, void *data);
int list_insert_before(listnode_t *node, void *data);

int list_pop(listnode_t *node);

int list_destroy_after(listnode_t *node);
int list_destroy_before(listnode_t *node);
int list_destroy(listnode_t *node);

void list_print(const listnode_t *node);

#endif
