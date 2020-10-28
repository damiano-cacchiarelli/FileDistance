//
// Created by Damiano on 22/09/2020.
//

#ifndef DAMIANOCACCHIARELLI105101_FILEBUFFER_H
#define DAMIANOCACCHIARELLI105101_FILEBUFFER_H
/**
 * Struttura che rappresenta un file.
 * Un File_Buffer è costituito da tre elementi: <br>
 * > <b>nameFile</b> -> il nome del file; <br>
 * > <b>dimFile</b> -> la dimensione del file; <br>
 * > <b>bufferFile</b> -> il vetore che conterrà i byte del file.
 */

    typedef struct File_Buffer {
        char *nameFile;
        unsigned int dimFile;
        char *bufferFile;
    } File;

/**
 * Alloca la memoria necessaria per un File_Buffer e inserisce i vari valori.
 * @param fileName il nome del file da cui recuperare le informazioni per generare il File_Buffer.
 * @return il puntatore al File_Buffer.
 */
File *get_File_Buffer(char *fileName);
/**
 * Libera l'area di memoria allocata per quel File_Buffer.
 * @param fBuffer il File_Buffer da eliminare
 */
void free_File_Buffer(File *fBuffer);

#endif //DAMIANOCACCHIARELLI105101_FILEBUFFER_H
