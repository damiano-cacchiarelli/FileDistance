//
// Created by Damiano on 01/09/2020.
//

#ifndef DAMIANOCACCHIARELLI105101_SORTEDLIST_H
#define DAMIANOCACCHIARELLI105101_SORTEDLIST_H

/**
 * struct Element_List o Element_List è una struttura che rappesenta un nodo di una lista
 * che consente di memorizzare la distanza di edit di un file.
 * Un Element_List è costituito da 4 elementi: <br>
 * > <b>fileName</b> -> il nome oprDel file; <br>
 * > <b>path</b> -> rappresenta il path assoluto oprDel file; <br>
 * > <b>editDistance</b> -> rappresenta la distanza di edit che si ha tra fileName e un altro file; <br>
 * > <b>next</b> -> puntatore al prossimo elemento della lista.
 */

typedef struct Element_List Element_List;
struct Element_List {
    char *fileName;
    char *path;
    int editDistance;
    Element_List *next;
};

/**
 * struct Sorted_List o Sorted_List è una struttura che rappesenta una lista ordinata. Gli Element_List
 * aggiunti tramite add() vengono automaticamente ordinati secondo il valore della distanza di edit
 * in ordine crescende. Non è prevista una funzione che permette di ordinare una lista creata precedentemente.
 * Una Sorted_List è costituita da un puntatore al primo elemento della lista (<b>firstElement</b>).
 */

typedef struct Sorted_List Sorted_List;
struct Sorted_List {
    Element_List *firstElement;
};


/**
 * Consente di aggiungere un elemento alla lista. Questo verrà inserito nella posizione corretta
 * seguendo le regole della Sorted_List.
 * @param sl la lista in cui aggiungere l'elemento;
 * @param el l'elemento da aggiungere alla lista.
 */
void add(Sorted_List *sl, Element_List *el);

/**
 * Consente di ottenere un nuovo Element_List. Viene allocata la memoria necessaria e vengono
 * memorizzati i vari valori.
 * Nel caso di errori durante l'allocazione, il programma termina, stampando l'errore.
 *
 * @param fileName il nome oprDel file;
 * @param path il path assoluto oprDel file;
 * @param distance la distanza di edit che si ha tra fileName e un altro file;
 * @return un puntatore a un nuovo Element_list.
 */
Element_List *new_element_list(char *fileName, char *path, int distance);

/**
 * Viene allocata la memoria necessaria per una Sorted_List vuota;
 * @return il puntatore alla Sorted_List.
 */
Sorted_List *new_list();

/**
 * Peremtte di rimuovere da una Sorted_List tutti gli Element_list che hanno una distanza di edit
 * maggiure di <b>distance</b>.
 * @param sl la lista da cui rimuovere gli elementi;
 * @param distance la distanza di edit.
 */
void remove_element_list(Sorted_List *sl, int distance);

/**
 * Permette di eliminare tutti gli elementi e viene liberata l'area di memoria sia della
 * lista sia di ogi elemento.
 * @param ls la lista da eliminare.
 */
void clear_list(Sorted_List *ls);

#endif //DAMIANOCACCHIARELLI105101_SORTEDLIST_H
