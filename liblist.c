#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "liblist.h"

listnode_t *list_create(void)
{
    listnode_t *node = (listnode_t *) malloc(sizeof(listnode_t));

    if (node != NULL) {
        node->next = NULL;
        node->prev = NULL;
        node->data = NULL;
        node->top = node;
    }

    return node;
}

int list_insert_after(listnode_t *node, void *data)
{
    listnode_t *new_node;

    if (node == NULL) {
        return list_enullptr;
    }

    new_node = (listnode_t *) malloc(sizeof(listnode_t));

    if (new_node == NULL) {
        return list_enomem;
    }

    new_node->data = (void *) data;
    new_node->next = node->next;
    new_node->prev = node;
    new_node->top = node->top;

    if (node->next != NULL) {
        node->next->prev = new_node;
    }

    node->next = new_node;
    return list_eok;
}

int list_insert_before(listnode_t *node, void *data)
{
    listnode_t *new_node;

    if (node == NULL) {
        return list_enullptr;
    }

    if (node == node->top) {
        return list_insert_after(node, data);
    }

    new_node = (listnode_t *) malloc(sizeof(listnode_t));

    if (new_node == NULL) {
        return list_enomem;
    }

    new_node->data = (void *) data;
    new_node->next = node;
    new_node->prev = node->prev;
    new_node->top = node->top;

    if (node->prev != NULL) {
        node->prev->next = new_node;
    }

    node->prev = new_node;
    return list_eok;
}

int list_pop(listnode_t *node)
{
    if (node == NULL) {
        return list_enullptr;
    }

    if (node == node->top) {
        return list_eempty;
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    free(node);
    return list_eok;
}

int list_destroy_after(listnode_t *node)
{
    if (node == NULL) {
        return list_enullptr;
    }

    while (node->next != NULL) {
        list_pop(node->next);
    }

    return list_eok;
}

int list_destroy_before(listnode_t *node)
{
    if (node == NULL) {
        return list_enullptr;
    }

    if (node == node->top) {
        return list_eempty;
    }

    while (node->prev != node->top) {
        list_pop(node->prev);
    }

    return list_eok;
}

int list_destroy(listnode_t *node)
{
    if (node == NULL) {
        return list_enullptr;
    }

    list_destroy_after(node->top);
    free(node->top);
    return list_eok;
}

void list_print(const listnode_t *node)
{
    if (node == NULL) {
        fprintf(stderr, "(empty)\n");
        return;
    }

    if (node == node->top) {
        node = node->next;
    }

    while (node != NULL) {
        fprintf(stderr, "0x%" PRIXPTR, (uintptr_t) node->data);

        if ((node->prev == NULL) || (node->prev == node->top)) {
            fprintf(stderr, " (HEAD)");
        }

        if (node->next == NULL) {
            fprintf(stderr, " (TAIL)");
        }

        fprintf(stderr, "\n");
        node = node->next;
    }
}

listnode_t *list_index(listnode_t *node, unsigned int index)
{
    if (node == NULL) {
        return NULL;
    }

    if ((node == node->top) && (node->next != NULL)) {
        node = node->next;
    }

    for (unsigned int x = 0; (x < index) && (node->next != NULL); x++) {
        node = node->next;
    }

    return (listnode_t *)(node);
}
