//
// Created by Damiano on 28/08/2020.
//

#ifndef DAMIANOCACCHIARELLI105101_FILECHANGE_H
#define DAMIANOCACCHIARELLI105101_FILECHANGE_H

#include "stack.h"
/**
 * Permette di modificare <b>filaName</b> seguendo le operazioni di modifica contenute in <b>filem</b> e di salvare
 * il file modificato in <b>outFileName</b>.
 * @param fileName il file da modificare;
 * @param filem il file contenente le operazioni di modifica;
 * @param outFileName il file di output.
 */
void edit_file(char *fileName, char *filem, char *outFileName);
/**
 * Permette di scrivere in <b>outFileName</b> le operazioni di modifica contenute nello Stack <b>stk</b>.
 * @param outNameFile il file dove salvare le operazioni;
 * @param stk lo Stack che contiene le operazioni.
 */
void save_operation(char *outFileName, Stack *stk);

#endif //DAMIANOCACCHIARELLI105101_FILECHANGE_H
