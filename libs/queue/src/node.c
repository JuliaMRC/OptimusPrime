//
// Created by dodev on 28/10/2019.
//

#include "../include/node.h"

#include <malloc.h>
#include <stddef.h>

struct node {
    int *value;
    Node *top;
};

/* Getters */
int *node_getValue(Node *element) {
    return element->value;
}

Node *node_getTopNode(Node *element) {
    return element->top;
}
/* Getters */

/* Setters */
void node_setTopNode(Node *element, Node *topElement) {
    element->top = topElement;
}
/* Setters */

/* Methods */
Node *node_new(int *value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->value = value;
    node->top = NULL;

    return node;
}

void node_destroy(Node *element) {
    free(element);
}
/* Methods */
