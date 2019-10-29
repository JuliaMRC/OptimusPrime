//
// Created by dodev on 28/10/2019.
//

#include <stddef.h>
#include <malloc.h>
#include "../include/queue.h"


struct queue {
    Node *first;
    Node *last;
    int length;
};

/* Getters */
Node *queue_getFirst(Queue *queue) {
    return queue->first;
}
Node *queue_getLast(Queue *queue) {
    return queue->last;
}
int queue_getLength(Queue *queue) {
    return queue->length;
}
/* Getters */

/* Setters */
void queue_setLength(Queue *queue, int num) {
    queue->length = num;
}
/* Setters */

/* Methods */
void queue_push(Queue *queue, int *value) {
    Node *elem = node_new(value);
    if(queue_getLength(queue) == 0) {
        queue->first = elem;
        queue->last = elem;
        queue_setLength(queue, 1);
    } else {
        node_setTopNode(queue->last, elem);
        queue->last = elem;
        queue->length++;
    }
}

int *queue_pop(Queue *queue) {
    if(queue->length == 0) {
        return NULL;
    } else {
        Node *elem = queue->first;
        queue->first = node_getTopNode(elem);
        queue->length--;

        return node_getValue(elem);
    }
}

Queue *queue_new() {
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->first = (Node *)malloc(sizeof(Node*));
    queue->length = 0;

    return queue;
}

void queue_destroy(Queue *queue) {
    Node *elem = queue->first;
    while(elem != NULL) {
        Node *top = node_getTopNode(elem);
        node_destroy(elem);
        elem = top;
    }

    free(queue);
}
/* Methods */

void queue_print(Queue* queue) {
    Node *elem = queue->first;
    while(elem != NULL) {
        printf("%d ", *node_getValue(elem));
        elem = node_getTopNode(elem);
    }
    printf("%s", "\n");
}