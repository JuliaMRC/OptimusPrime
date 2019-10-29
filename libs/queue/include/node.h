//
// Created by dodev on 28/10/2019.
//

#ifndef MATRIZ_ESPARSA_NODE_H
#define MATRIZ_ESPARSA_NODE_H

typedef struct node Node;

/* Getters */
int *node_getValue(Node *element);
Node *node_getTopNode(Node *element);
/* Getters */

/* Setters */
void node_setTopNode(Node *element, Node *topElement);
/* Setters */

/* Methods */
Node *node_new(int *value);
void node_destroy(Node *element);
/* Methods */

#endif //MATRIZ_ESPARSA_NODE_H
