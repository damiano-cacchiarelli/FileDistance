//
// Created by Damiano on 28/08/2020.
//

#ifndef DAMIANOCACCHIARELLI105101_DISTANCE_H
#define DAMIANOCACCHIARELLI105101_DISTANCE_H

#include <stdio.h>
#include "stack.h"

/**
 * Permette di calcolare la distanza di edit tra <b>FileName1</b> e <b>FileName2</b>.
 * @param fileName1 il nome del primo file;
 * @param fileName2 il nome del secondo file;
 * @return la distanza di edit tra i due file: ovvero il minimo numero di operazioni
 * da eseguire per traformare <b>FileName1</b> in <b>FileName2</b>.
 */
int calcolate_distance(char *fileName1, char *fileName2);

/**
 * Permette di ottenere le operazioni da eseguire per trasformare <b>FileName1</b> in <b>FileName2</b>.
 * @param fileName1 il nome del primo file;
 * @param fileName2 il nome del secondo file;
 * @return lo <i>Stack</i> contenente le operazioni da eseguire.
 */
Stack *generate_operation(char *fileName1, char *fileName2);


#endif //DAMIANOCACCHIARELLI105101_DISTANCE_H
