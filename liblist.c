#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "liblist.h"

node_t *list_create_top(const void *data)
{
    node_t *node = malloc(sizeof(node_t));

    if (node != NULL) {
        node->next = NULL;
        node->prev = NULL;
        node->data = (void *) data;
    }

    return node;
}

int list_insert_after(node_t * node, const void * data)
{
    node_t *new_node;

    if (node == NULL) {
        return list_enullptr;
    }

    new_node = malloc(sizeof(node_t));

    if (new_node == NULL) {
        return list_enomem;
    }

    new_node->data = (void *) data;
    new_node->next = node->next;
    new_node->prev = node;

    if (node->next != NULL) {
        node->next->prev = new_node;
    }

    node->next = new_node;
    return list_eok;
}

int list_insert_before(node_t * node, const void * data)
{
    node_t *new_node;

    if (node == NULL) {
        return list_enullptr;
    }

    new_node = malloc(sizeof(node_t));

    if (new_node == NULL) {
        return list_enomem;
    }

    new_node->data = (void *) data;
    new_node->next = node;
    new_node->prev = node->prev;

    if (node->prev != NULL) {
        node->prev->next = new_node;
    }

    node->prev = new_node;
    return list_eok;
}

int list_pop(node_t *node)
{
    if (node == NULL) {
        return list_enullptr;
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

int list_destroy_after(node_t *node)
{
    if (node == NULL) {
        return list_enullptr;
    }

    while (node->next != NULL) {
        list_pop(node->next);
    }

    return list_eok;
}

int list_destroy_before(node_t *node)
{
    if (node == NULL) {
        return list_enullptr;
    }

    while (node->prev != NULL) {
        list_pop(node->prev);
    }

    return list_eok;
}

int list_destroy(node_t *node)
{
    list_destroy_after(node);
    list_pop(node);
    return list_eok;
}

void list_print(const node_t *node)
{
    if (node == NULL) {
        fprintf(stderr, "(empty)\n");
    }

    while (node != NULL) {
        fprintf(stderr, "0x%" PRIXPTR, (uintptr_t) node->data);
        if (node->prev == NULL) {
            fprintf(stderr, " (HEAD)");
        }

        if (node->next == NULL) {
            fprintf(stderr, " (TAIL)");
        }
        fprintf(stderr, "\n");
        node = node->next;
    }
}
