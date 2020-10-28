//
// Created by Damiano on 28/08/2020.
//

#include <stdlib.h>
#include <string.h>
#include "filebuffer.h"
#include "distance.h"
#include "tools.h"
/**
 *  Funzione che calcola il minomo di tre valori.
 * @param a valore da confrontare;
 * @param b valore da confrontare;
 * @param c valore da confrontare.
 * @return il minimo trai i tre.
 */
int minimum(int a, int b, int c);
/**
 * Restituisce la matrice generata eseguendo sui due file l'algoritmo per il calcolo della distanza di edit .
 * @param file1 il primo file da confrontare;
 * @param file2 il secondo file.
 * @return la matrice.
 */
int **lev_matrix(File *file1, File *file2);
/**
 * Alloca la memoria necessaria per la matrice.
 * @param dim1 il numero di byte del primo file (numero di righe);
 * @param dim2 il numero di byte del secondo file (numero di colonne).
 * @return l'area di memoria allocata.
 */
int **get_lev_matrix(unsigned int dim1, unsigned int dim2);
/**
 * Inizializza la matrice riempiendo la prima riga e la prima colonna.
 * @param matrix la matrice da inizializzare;
 * @param dim1 il numero di byte del primo file (numero di righe);
 * @param dim2 il numero di byte del secondo file (numero di colonne).
 */
void init_lev_matrix(int **matrix, unsigned int dim1, unsigned int dim2);
/**
 * Riempie la matrice.
 * @param matrix la matrice;
 * @param file1 il primo file;
 * @param file2 il secondo file.
 */
void fill_lev_matrix(int **matrix, File *file1, File *file2);
/**
 * Permette di liberare l'area di memoria allocata per la matrice.
 * @param matrix la matrice di cui liberare l'area di memoria;
 * @param dim1 il numero di righe;
 */
void free_lev_matrix(int **matrix, unsigned int dim1);

int calcolate_distance(char *fileName1, char *fileName2) {

    File *file1 = get_File_Buffer(fileName1);
    File *file2 = get_File_Buffer(fileName2);

    int *prev = calloc((file2->dimFile + 1), sizeof(int));
    int *curr = calloc((file2->dimFile + 1), sizeof(int));
    int *tmp = NULL;

    for (int i = 0; i <= file2->dimFile; i++)
        prev[i] = i;

    for (int i = 1; i <= file1->dimFile; i++) {
        curr[0] = i;
        for (int j = 1; j <= file2->dimFile; j++) {
            if (file1->bufferFile[i - 1] != file2->bufferFile[j - 1]) {
                int k = minimum(curr[j - 1], prev[j - 1], prev[j]);
                curr[j] = k + 1;
            } else {
                curr[j] = prev[j - 1];
            }

        }
        tmp = prev;
        prev = curr;
        curr = tmp;
        memset((void *) curr, 0, sizeof(int) * (file2->dimFile + 1));
    }

    int distance = prev[file2->dimFile];
    free_buffer(prev, curr);
    free_File_Buffer(file1);
    free_File_Buffer(file2);
    return distance;
}

Stack *generate_operation(char *fileName1, char *fileName2) {

    File *file1 = get_File_Buffer(fileName1);
    File *file2 = get_File_Buffer(fileName2);

    int **matrix = lev_matrix(file1, file2);
    unsigned int x = file1->dimFile;
    unsigned int y = file2->dimFile;
    int diagonal, horizontal, vertical, min;
    Stack *stk = new_stack();
    while (x > 0 && y > 0) {
        if (file1->bufferFile[x - 1] == file2->bufferFile[y - 1]) {
            x--;
            y--;
        } else {
            diagonal = matrix[x-1][y-1];
            horizontal = matrix[x][y- 1];
            vertical = matrix[x- 1][y];
            min = minimum(diagonal, horizontal, vertical);
            if (min == diagonal) {
                x--;
                y--;
                push(stk, new_element(file2->bufferFile[y], x, SET));
            } else if (min == horizontal) {
                y--;
                push(stk, new_element(file2->bufferFile[y], x, ADD));
            } else if (min == vertical) {
                x--;
                push(stk, new_element(0, x, DEL));
            } else {
                perror("Backtrack error");
                exit(-1);
            }
        }
    }

    free_lev_matrix(matrix, file1->dimFile);

    if (x != 0) {
        while (x > 0) {
            x--;
            push(stk, new_element(0, x, DEL));
        }
    } else if (y != 0) {
        while (y > 0) {
            y--;
            push(stk, new_element(file2->bufferFile[y], 0, ADD));
        }
    }

    free_File_Buffer(file1);
    free_File_Buffer(file2);

    return stk;
}

int **lev_matrix(File *file1, File *file2) {
    int **matrix = get_lev_matrix(file1->dimFile, file2->dimFile);
    fill_lev_matrix(matrix, file1, file2);
    return matrix;
}

int **get_lev_matrix(unsigned int dim1, unsigned int dim2) {
    int **matrix = calloc(dim1 + 1, sizeof(int *));
    if (isNull(matrix)) {
        perror("Unable to allocate lev_matrix");
        exit(-1);
    }

    for (int i = 0; i <= dim1; i++) {
        matrix[i] = (int *) malloc((dim2 + 1) * sizeof(int));
        if (isNull(matrix[i])) {
            perror("Unable to allocate lev_matrix[i]");
            exit(-1);
        }
    }
    return  matrix;
}

void fill_lev_matrix(int **matrix, File *file1, File *file2) {
    init_lev_matrix(matrix, file1->dimFile, file2->dimFile);
    for (int i = 1; i <= file1->dimFile; i++) {
        for (int j = 1; j <= file2->dimFile; j++) {
            if (file1->bufferFile[i - 1] != file2->bufferFile[j - 1]) {
                int k = minimum(
                        matrix[i][j - 1],
                        matrix[i - 1][j],
                        matrix[i - 1][j - 1]
                );
                matrix[i][j] = k + 1;
            } else {
                matrix[i][j] = matrix[i - 1][j - 1];
            }

        }
    }
}

void init_lev_matrix(int **matrix, unsigned int dim1, unsigned int dim2){
    for (int i = 0; i <= dim1; i++) {
        matrix[i][0] = i;
    }

    for (int j = 1; j <= dim2; j++) {
        matrix[0][j] = j;
    }
}


void free_lev_matrix(int **matrix, unsigned int dim1) {
    for (int i = 0; i <=dim1 ; i++)
        free(matrix[i]);
    free(matrix);
}

int minimum(int a, int b, int c) {
    int min = a;

    if (b < min) min = b;
    if (c < min) min = c;

    return min;
}

