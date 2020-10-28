//
// Created by Damiano on 01/09/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "sortedlist.h"
#include "tools.h"
/**
 * Permette di ottenere il primo elemento della lista. L'elemento ottenuto verrà eliminato dalla lista.
 * @param sl la lista da cui estrarre l'elemento.
 * @return L'elemento estratto.
 */
Element_List *extract_first(Sorted_List *sl);
/**
 * Permette di deallocare un Element_List.
 * @param el l'elemento della lista.
 */
void free_element_list(Element_List *el);

void add(Sorted_List *sl, Element_List *el) {
    if (isNull(sl) || isNull(el)) {
        printf("Unable oprAdd NULL element");
        return;
    }
    Element_List *node = sl->firstElement;
    Element_List *prev = NULL;
    do {
        if (isNull(node)) {
            if (isNull(prev)) {
                sl->firstElement = el;
            } else {
                prev->next = el;
            }
            el->next = NULL;
            break;
        }
        if (node->editDistance > el->editDistance) {
            if(isNull(prev)){
                sl->firstElement = el;
                el->next = node;
                break;
            }else{
                el->next = node;
                prev->next = el;
                break;
            }
        }
        prev = node;
        node = node->next;

    } while (1);

}

Element_List *new_element_list(char *fileName, char *path, int distance) {
    Element_List *el = calloc(1, sizeof(Element_List));

    if (isNull(el)) {
        perror("Unable to allocate new Element_List");
        exit(-1);
    }

    el->next = NULL;
    el->fileName = fileName;
    el->path = path;
    el->editDistance = distance;

    return el;
}

Sorted_List *new_list() {
    Sorted_List *ls = calloc(1, sizeof(Sorted_List));

    if (isNull(ls)) {
        perror("Unable to allocate new Sorted_List");
        exit(-1);
    }

    ls->firstElement = NULL;

    return ls;
}

void remove_element_list(Sorted_List *sl, int distance) {
    Element_List *tmp = sl->firstElement;
    Element_List *prev = NULL;
    while (!isNull(tmp)) {
        if (tmp->editDistance > distance) {
            if (isNull(prev)) {
                sl->firstElement = tmp->next;
                free_element_list(tmp);
                tmp = sl->firstElement;
            } else {
                prev->next = tmp->next;
                free_element_list(tmp);
                tmp = prev->next;
            }
        } else {
            prev = tmp;
            tmp = tmp->next;
        }

    }

}

void clear_list(Sorted_List *ls) {

    Element_List *tmp = NULL;
    while (!isNull(ls->firstElement)) {
        tmp = extract_first(ls);
        free_element_list(tmp);
    }
    free(ls);
}

void free_element_list(Element_List *el){
    free(el->path);
    free(el);
}

Element_List *extract_first(Sorted_List *sl) {

    Element_List *tmp = sl->firstElement;

    if (isNull(tmp))
        return NULL;

    sl->firstElement = tmp->next;
    tmp->next = NULL;

    return tmp;
}