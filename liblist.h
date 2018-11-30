#ifndef _LIBLIST_H_
#define _LIBLIST_H_

enum {
    list_eok = 0,
    list_enullptr = -1,
    list_enomem = -2,
};

typedef struct node_t {
    void *data;
    struct node_t *next;
    struct node_t *prev;
} node_t;

node_t *list_create_top(const void *data);
int list_insert_after(node_t *node, const void *data);
int list_insert_before(node_t *node, const void *data);
int list_pop(node_t *node);
int list_destroy(node_t *node);
int list_destroy_after(node_t *node);
int list_destroy_before(node_t *node);

void list_print(const node_t *node);

#endif
