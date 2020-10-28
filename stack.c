//
// Created by Damiano on 28/08/2020.
//
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "stack.h"
#include "tools.h"
/**
 * Permette di creare un nuovo nodo per lo Stack. Nel caso di errori durante l'allocazione,
 * il programma termina, stampando l'errore.
 * @param e l'elemento da inserire nel nodo;
 * @param next il nodo successivo.
 * @return il nodo creato.
 */
Node *new_Node(Element_Stack *e, Node *next);

void push(Stack *stk, Element_Stack *el) {
    stk->firstNode = new_Node(el, stk->firstNode);
}

Element_Stack *pop(Stack *stk) {

    if (isEmpty(stk)) {
        return NULL;
    }

    Node *n = stk->firstNode;
    Element_Stack *e = n->data;
    stk->firstNode = n->next;

    free(n);
    return e;
}

Element_Stack *peek(Stack *stk) {

    if (isEmpty(stk)) {
        return NULL;
    }
    return stk->firstNode->data;
}

void clear_stack(Stack *stk) {

    while (!isEmpty(stk)) {
        free(pop(stk));
    }
}

int isEmpty(Stack *stk) {

    if (isNull(stk->firstNode)) {
        return 1;
    }
    return 0;
}

Element_Stack *new_element(char byte, unsigned int position, Opr operation) {

    Element_Stack *el = calloc(1, sizeof(Element_Stack));
    if (isNull(el)) {
        perror("Unable to allocate new Element_Stack");
        exit(-1);
    }

    el->operation = operation;
    el->byte = byte;
    el->position = position;

    return el;
}

Node *new_Node(Element_Stack *e, Node *next) {

    Node *n = calloc(1, sizeof(Node));
    if (isNull(n)) {
        perror("Unable to allocate new Node");
        exit(-1);
    }

    n->data = e;
    n->next = next;

    return n;
}

Stack *new_stack() {

    Stack *stk = calloc(1, sizeof(Stack));
    if (isNull(stk)) {
        perror("Unable to allocate new Stack");
        exit(-1);
    }

    stk->firstNode = NULL;

    return stk;
}

void print_stk(Stack *pStack) {
    Node *n = pStack->firstNode;
    while(!isNull(n)){
        Opr o = n->data->operation;
        if(o == ADD) printf(" ADD : ");
        else if (o == DEL) printf(" DEL : ");
        else printf(" SET : ");
        printf("%i",n->data->position);
        if(o!= DEL) printf(" - Byte: %c", n->data->byte);
        printf("\n");
        n = n->next;
    }
}

