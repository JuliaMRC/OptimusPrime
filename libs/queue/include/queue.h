//
// Created by dodev on 28/10/2019.
//

#ifndef MATRIZ_ESPARSA_QUEUE_H
#define MATRIZ_ESPARSA_QUEUE_H

#include "node.h"

typedef struct queue Queue;

/* Getters */
Node *queue_getFirst(Queue *queue);
Node *queue_getLast(Queue *queue);
int queue_getLength(Queue *queue);
/* Getters */

/* Setters */
void queue_setLength(Queue *queue, int num);
/* Setters */

/* Methods */
Queue *queue_new();
void queue_push(Queue *queue, int *value);
int *queue_pop(Queue *queue);
void queue_destroy(Queue *queue);
void queue_print(Queue* queue);
/* Methods */

#endif //MATRIZ_ESPARSA_QUEUE_H
