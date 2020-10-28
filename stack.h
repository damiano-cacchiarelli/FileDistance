//
// Created by Damiano on 28/08/2020.
//

#ifndef DAMIANOCACCHIARELLI105101_STACK_H
#define DAMIANOCACCHIARELLI105101_STACK_H
/**
 * Rappresenta le possibili operazioni che possono essere fatte durante il calcolo
 * della distanza di edit: <br>
 * > <b>SET</b> -> sostituzione di un carattere; <br>
 * > <b>ADD</b> -> inserimento di un carattere; <br>
 * > <b>DEL</b> -> eliminazione di un carattere. <br>
 */
typedef enum {
    SET,
    ADD,
    DEL
} Opr;

/**
 * Un struct Element_Stack o Element_Stack è una struttura che rappresenta i dati contenuti
 * da un nodo di uno Stack. Viene utilizzato per memorizzare un'operazione di modifica da
 * effettuare su un particolare file. <br>
 * Un Element_Stack è costituito da 3 elementi: <br>
 * > <b>position</b> -> la posizione oprDel byte nel file su cui eseguire l'operzione; <br>
 * > <b>operation</b> -> l'operazione da eseguire; <br>
 * > <b>byte</b> -> rappresenta il byte a cui fa riferimento il nodo.
 */

    typedef struct Element_Stack{
        char byte;
        unsigned int position;
        Opr operation;
    }Element_Stack;

/**
 * struct Stack_Node o Node è una struttura che rappresenta un nodo di uno Stack.
 * Un Node è costituito da un puntatore a un Element_Stack (<b>data</b>) e da un puntatore
 * al nodo successivo (<b>next</b>).
 */
    typedef struct Stack_Node{
        Element_Stack *data;
        struct Stack_Node *next;
    }Node;

/**
 * struct Stack o Stack è una struttura che rappresenta uno stack con algoritmo LIFO.
 * è costituito da un puntatore al Node (<b>firstNode</b>) in cima alla pila.
 */
    typedef struct Stack{
        Node *firstNode;
    }Stack;
/**
 * Permette di creare uno Element_Stack. Viene allocata la memoria necessaria e memorizzati i
 * vari elementi.
 * Nel caso di errori durante l'allocazione, il programma termina, stampando l'errore.
 * @param byte il byte a cui fa riferimento il nodo;
 * @param position la posizione oprDel byte nel file su cui eseguire l'operzione;
 * @param operation l'operazione da eseguire.
 * @return il puntatore a un Element_Stack che descrive una determinata operazione.
 */
Element_Stack *new_element(char byte, unsigned int position, Opr operation);

/**
 * Crea uno Stack che non contiene alcun elemento.
 * Nel caso di errori durante l'allocazione, il programma termina, stampando l'errore.
 * @return il puntatore allo Stack.
 */
Stack *new_stack();

/**
 * Permette di ottenere l'Element_Stack che si trova nel Node in cima allo Stack senza
 * che il nodo venga eliminato.
 * @param stk lo Stack su cui eseguire la peek.
 * @return il puntatore all'Element_Stack; NULL nel caso in cui lo Stack sia vuoto.
 */
Element_Stack *peek(Stack *stk);

/**
 * Permette di ottenere l'Element_Stack che si trova nel Node in cima allo Stack. Il nodo
 * viene eliminato dalla pila e viene liberata l'area di memoria.
 * @param stk lo Stack su cui eseguire la pop.
 * @return il puntatore all'Element_Stack; NULL nel caso in cui lo Stack sia vuoto.
 */
Element_Stack *pop(Stack *stk);

/**
 * Permette di inserire un Element_Stack in cima allo Stack.
 * @param stk lo Stack in cui inserire l'elemento;
 * @param el l'Element_Stack da inserire.
 */
void push(Stack *stk, Element_Stack *el);

/**
 * Vengono eliminati tutti gli elementi dello Stack e viene liberata l'area di memoria.
 * @param stk lo Stack da eliminare.
 */
void clear_stack(Stack *stk);
/**
 * Definisce se lo Stack passato è vuoto.
 * @param stk lo Stack da controllare;
 * @return 1 se è vuoto; 0 altrimenti.
 */
int isEmpty(Stack *stk);

/**
 * Permette di visualizzare tutte le operazioni contenute in uno Stack.
 * @param pStack lo Stack.
 */
void print_stk(Stack *pStack);

#endif //DAMIANOCACCHIARELLI105101_STACK_H
