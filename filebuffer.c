//
// Created by Damiano on 22/09/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include "filebuffer.h"
#include "tools.h"
/**
 * Restituisce il numero di byte del file.
 * @param file il file di cui calcolare la dimensione.
 * @return la dimensione del file.
 */
unsigned int get_dim_file(FILE *file);
/**
 * Permette di restituire il contenuto in byte del file.
 * @param dimFile la dimensione in byte del file;
 * @param file il file da leggere.
 * @return il vettore contenente i byte del file.
 */
char *read_from_file(unsigned int dimFile, FILE *file);

File *get_File_Buffer(char *fileName) {

    File *fileBuffer = calloc(1, sizeof(File));
    if (isNull(fileBuffer)) {
        perror("Unable to allocate File_Buffer");
        exit(-1);
    }
    FILE *f = open_file(fileName, "rb");
    if (isNull(fileBuffer)) {
        perror("Unable to open file.");
        exit(-1);
    }

    fileBuffer->nameFile = fileName;
    fileBuffer->dimFile = get_dim_file(f);
    fileBuffer->bufferFile = read_from_file(fileBuffer->dimFile, f);

    fclose(f);

    return fileBuffer;
}

void free_File_Buffer(File *fBuffer) {
    free(fBuffer->bufferFile);
    free(fBuffer);
}

unsigned int get_dim_file(FILE *file) {
    fseek(file, 0, SEEK_END);
    unsigned int size = ftell(file);
    rewind(file);
    return size;
}

char *read_from_file(unsigned int dimFile, FILE *file) {
    unsigned long long elementsRead;
    char *buffer = (char *) calloc(dimFile, sizeof(char));

    if (isNull(buffer)) {
        perror("Unable to read file!");
        exit(-1);
    }

    elementsRead = fread(buffer, sizeof(char), dimFile, file);

    if (elementsRead != dimFile) {
        perror("Unable to read the entire file!");
        exit(-1);
    }
    return buffer;
}