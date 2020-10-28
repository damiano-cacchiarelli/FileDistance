//
// Created by Damiano on 28/08/2020.
//

#ifndef DAMIANOCACCHIARELLI105101_FILEDISTANCE_H
#define DAMIANOCACCHIARELLI105101_FILEDISTANCE_H

/**
 * Calcola la distanza di edit tra il fileName1 e fileName2. La distanza calcolata è il minimo numero di operazioni
 * necessarie per trasformare il <b>fileName1</b> nel file <b>fileName2</b>.
 *
 * @param fileName1 il nome del primo file;
 * @param fileName2 il nome del secondo file.
 */
void distance(char *fileName1, char *fileName2);

/**
 * Crea un file binario (outFileName) in cui sono inseriti le varie operazioni
 * da effettuare per trasformare il file <b>fileName1</b> nel file <b>fileName2</b>.
 *
 * @param fileName1 il nome del primo file;
 * @param fileName2 il nome del secondo file;
 * @param outFileName il nome del file di output, in cui verranno salvate le operazioni.
 */
void out_distance(char *fileName1, char *fileName2, char *outFileName);

/**
 * Utilizza il contenuto di fileName e le operazioni memorizzate in <b>filem</b> per
 * creare il file <b>outputFile</b>.
 *
 * @param inputFile il nome del file su cui effettuare le modifiche;
 * @param filem il nome file da cui importare le operazioni da effettuare;
 * @param outFileName il nome del file in cui è salvato il risultato della transarmazione.
 */
void apply_changes(char *fileName, char *filem, char *outFileName);

/**
 * Resistuisce tutti i file contenuti nella directory dir (e sottodirectory),
 * che hanno distanza minima dal file <b>fileName</b>.
 *
 * @param fileName il nome del file su cui verificare la minima distanza di edit;
 * @param dir la directory su cui controllare la distanza dei vari file.
 */
void search(char *fileName, char *dir);

/**
 * Resistuisce tutti i file contenuti nella directory dir (e sottodirectory),
 * che hanno distanza di edit, rispetto al file <b>fileName</b>, minore di distance.
 *
 * @param fileName il nome del file su cui verificare la minima distanza di edit;
 * @param dir la directory su cui controllare la distanza dei vari file;
 * @param distance la minima distanza di edit.
 */
void search_all(char *fileName, char *dir, int distance);


#endif //DAMIANOCACCHIARELLI105101_FILEDISTANCE_H
