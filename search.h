//
// Created by Damiano on 01/09/2020.
//

#ifndef DAMIANOCACCHIARELLI105101_SEARCH_H
#define DAMIANOCACCHIARELLI105101_SEARCH_H
/**
 * Permette di analizzare tutti i file presenti nella directory (o sotto-directory)
 * e di visualizzare in output la distanza e il path assoluto di quei file che hanno distanza di edit
 * minore di limit.
 * @param inFile il file con cui avverrà il confronto;
 * @param directory la directory in cui cercare i file;
 * @param limit la distanza minima.
 */
void search_files_and_print(char *inFile, char *directory, int limit);


#endif //DAMIANOCACCHIARELLI105101_SEARCH_H
