//
// Created by Damiano on 28/08/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filechange.h"
#include "tools.h"
#include "filebuffer.h"
/**
 * Permette di generare uno <i>Stack</i> di operazioni contenute nel file <b>filem</b>.
 * @param stk lo <i>Stack</i> in cui inserire le operazioni;
 * @param filem il file da cui leggere le operazioni.
 */
void create_stack_operation(Stack *stk, char *filem);
/**
 * Inserisce nell'area di memoria puntata da <b>position</b> <i>l'unsigned int</i> letto dal file <b>filem</b>.
 * Tale numero rappresenta la posizione in cui verrà effettuara la modifica.
 * @param position l'area di memoria dove inserire il valore;
 * @param filem il file da cui leggere il numero.
 */
void get_position(unsigned int *position, FILE *filem);
/**
 * Inserisce nell'area di memoria puntata da <b>byte</b> il bye letto dal file <b>filem</b>.
 * Tale valore rappresenta il byte che verrà aggiunto o insrerito durante la modifica.
 * @param byte l'area di memoria dove inserire il valore;
 * @param filem il file da cui leggere il byte.
 */
void get_byte(char *byte, FILE *filem);
/**
 * Inserisce nell'area di memoria puntata da <b>opr</b> il primo carattere dell'operazione. Il puntatore
 * di lettura viene successivamente spostato di due posizioni.
 * Tale valore rappresenta l'operazione che deve essere effettuata durante la modifica.
 * @param opr l'area di memoria dove inserire il valore;
 * @param filem il file da cui leggere il carattere.
 */
void get_operation(char *opr, FILE *filem);
/**
 * Permette di applicare le modifiche contenute nello <i>Stack</i> al vettore.
 * @param file puntatore al vettore su cui applicare le modifiche;
 * @param dimFile la dimensione del vettore;
 * @param stk lo <i>Stack</i> che contiene le operazioni di modifica.
 * @return la nuova dimensione del vettore.
 */
unsigned int apply_to_file(char **file, unsigned int dimFile, Stack *stk);
/**
 * Esegue l'operazione SET: viene sostituito in una determinata bosizione un byte con un altro.
 * @param file il vettore in cui effettuare la modifica;
 * @param position la posizione in cui sostituire il byte;
 * @param byte il byte da inserire.
 */
void oprSet(char *file, unsigned int position, char byte);
/**
 * Esegue l'operazione DEL: viene eliminato un byte in una determinata bosizione.
 * @param file il vettore in cui effettuare la modifica;
 * @param dimFile la dimensione del vettore;
 * @param position la posizione in cui eliminare il byte.
 */
void oprDel(char *file, unsigned int dimFile, unsigned int position);
/**
 * Esegue l'operazione ADD: viene aggiunto un byte in una determinata posizione.
 * @param file il vettore in cui effettuare la modifica;
 * @param dimFile la dimensione del vettore;
 * @param position la posizione in cui aggiungere il byte;
 * @param byte il byte da aggiungere.
 * @return il vettore modificato.
 */
char *oprAdd(char **file, unsigned int dimFile, unsigned int position, char byte);

void edit_file(char *fileName, char *filem, char *outFileName) {

    Stack *stk = calloc(1, sizeof(Stack));
    create_stack_operation(stk, filem);

    File *inFile = get_File_Buffer(fileName);

    inFile->dimFile = apply_to_file(&(inFile->bufferFile), inFile->dimFile, stk);

    FILE *outFile = open_file(outFileName, "wb");
    if(isNull(outFile)){
        perror("Unable to open outFile");
        exit(-1);
    }
    fwrite(inFile->bufferFile, sizeof(char ), inFile->dimFile, outFile);
    free_File_Buffer(inFile);
    rewind(outFile);
    fclose(outFile);
}


void create_stack_operation(Stack *stk, char *filem) {
    FILE *changes = open_file(filem, "rb");
    if(isNull(changes)){
        perror("Unable to open filem");
        exit(-1);
    }
    char operation;
    char byte;
    unsigned int position = 0;
    while (!feof(changes)) {
        get_operation(&operation,changes);
        get_position(&position, changes);
        if (operation != 'D') get_byte(&byte, changes);
        if (operation == 'S') push(stk, new_element(byte, position, SET));
        else if (operation == 'A') push(stk, new_element(byte, position, ADD));
        else if (operation == 'D') push(stk, new_element(' ', position, DEL));
        else break;
        operation = ' ';
    }
    fclose(changes);
}

void save_operation(char *outFileName, Stack *stk) {

    FILE *outFile = open_file(outFileName, "wb");
    if(isNull(outFile)){
        perror("Unable to write outFile");
        exit(-1);
    }

    Element_Stack *tmpEl = NULL;
    while (!isEmpty(stk)) {
        tmpEl = pop(stk);
        fwrite(get_name_operation(tmpEl->operation), sizeof(char) * 3, 1, outFile);
        fwrite(&(tmpEl->position), sizeof(unsigned int), 1, outFile);
        if (tmpEl->operation != DEL) fwrite(&(tmpEl->byte), sizeof(char), 1, outFile);
        free(tmpEl);
    }
    fclose(outFile);
}

unsigned int apply_to_file(char **file, unsigned int dimFile, Stack *stk) {
    Element_Stack *el = NULL;
    while (!isEmpty(stk)) {
        el = pop(stk);
        Opr operation = el->operation;
        if (operation == SET) {
            oprSet(*file, el->position, el->byte);
        } else if (operation == DEL) {
            oprDel(*file, dimFile, el->position);
            dimFile--;
        } else if (operation == ADD) {
            *file = oprAdd(file, dimFile, el->position, el->byte);
            dimFile++;
        }
        free(el);
    }
    return dimFile;
}

void oprSet(char *file, unsigned int position, char byte) {
    file[position] = byte;
}

char *oprAdd(char **file, unsigned int dimFile, unsigned int position, char byte) {
    unsigned int dim = dimFile +1;
    char *tmp = calloc(dim, sizeof(char ));
    if(isNull(tmp)){
        perror("Unable allocate new buffer");
        exit(-1);
    }
    for (int i = 0; i < position; ++i) {
        tmp[i] = (*file)[i];
    }
    tmp[position] = byte;
    for (unsigned int i = position+1; i < dim; ++i) {
        tmp[i] = (*file)[i-1];
    }
    free(*file);
    return tmp;
}

void oprDel(char *file, unsigned int dimFile, unsigned int position) {
    memmove(&(file[position]), &(file[position + 1]), (dimFile - position));
}

void get_operation(char *opr, FILE *filem){
    fread(opr, sizeof(char), 1, filem);
    fseek(filem, 2, SEEK_CUR);
}

void get_byte(char *byte, FILE *filem) {
    fread(byte, sizeof(char), 1, filem);
}

void get_position(unsigned int *position, FILE *filem) {
    fread(position, sizeof(unsigned int), 1, filem);
}

