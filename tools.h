//
// Created by Damiano on 31/08/2020.
//

#ifndef DAMIANOCACCHIARELLI105101_TOOLS_H
#define DAMIANOCACCHIARELLI105101_TOOLS_H


#include "stack.h"
/**
 * Permette di determinare se un puntatore è NULL.
 * @param p il puntatore.
 * @return 1 se il puntatore è NULL; 0 altrimenti.
 */
int isNull(void *p);

/**
 * Permette di avviare il timer. Imposta timer al numero di clock attuali.
 */
void start_timer();
/**
 * Stampa il tempo trascorso da quando è stato avviato il timer.
 */
void print_time();
/**
 * Resetta il timer e lo riporta a zero.
 */
void reset_timer();
/**
 * Permette di apreire un file.
 * @param file il nome del file da aprire;
 * @param modes il mode con cui aprire il file.
 * @return il file aperto nella modalità richiesta.
 */
FILE *open_file(char *file, char *modes);
/**
 * Permette di deallocare due aree di memoria.
 * @param b1 l'area di memoria da deallocare;
 * @param b2 l'area di memoria da deallocare;
 */
void free_buffer(void *b1, void *b2);
/**
 * Permette di ottenere la stringa corrispondente all'operazione.
 * @param opr l'operazione di cui si vuole ottenere la stringa.
 * @return la stringa che rappresenta l'operazione.
 */
char *get_name_operation(Opr opr);



#endif //DAMIANOCACCHIARELLI105101_TOOLS_H
