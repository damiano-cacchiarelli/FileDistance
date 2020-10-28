//
// Created by Damiano on 31/08/2020.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"

/**
 * Indica il numero di clock di quando viene avviato il timer.
 */
clock_t timer = 0;

/**
 * Determina i secondi passati tra startTime specificato in clock ed ora.
 * @param startTime il tempo di inizio
 * @return i secondi che sono passati tra startTime e ora
 */
double get_time(clock_t startTime);


void start_timer() {
    timer = clock();
}

double get_time(clock_t startTime) {
    return (double) (clock() - startTime) / CLOCKS_PER_SEC;
}

void reset_timer() {
    timer = 0;
}

void print_time() {
    printf("TIME : %lf",  get_time(timer) );
}

int isNull(void *p) {

    if (p == NULL) {
        return 1;
    }
    return 0;
}

FILE *open_file(char *file, char *modes){
    FILE *f = fopen(file, modes);
    if(isNull(f)){
        perror("Error opening file");
        exit(-1);
    }
    return f;
}

void free_buffer(void *b1, void *b2) {
    if (!isNull(b1)) free(b1);
    if (!isNull(b2)) free(b2);
}

char *get_name_operation(Opr opr) {
    switch (opr) {
        case SET:
            return "SET";
        case DEL:
            return "DEL";
        case ADD:
            return "ADD";
        default: {
            perror("Operation not recognized");
            exit(-1);
        }
    }
}


