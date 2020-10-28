//
// Created by Damiano on 01/09/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include "filebuffer.h"
#include "search.h"
#include "sortedlist.h"
#include "tools.h"
#include "distance.h"

typedef struct dirent Dirent;

/**
 * Permette di popolare la lista con i file presenti in una directory.
 * @param sList la lista;
 * @param file il file con cui calcolare la distanza di edit;
 * @param dir la directory dove ricercare i file.
 */
void get_list_file(Sorted_List *sList, File *file, char *dir);

/**
 * Permette di distinguere se un path rappresenta una directory o un file. In caso fosse un file
 * verrà aggiunto alla lista; Nel caso fosse una directory verrà richiamata la funzione <i>get_list_file</i>.
 * @param sList la lista;
 * @param file il file con cui calcolare la distanza di edit;
 * @param dir la directory dove ricercare i file;
 * @param dp la struttura dirent.
 */
void search_file(Sorted_List *sList, File *file, char *dir, Dirent *dp);

/**
 * Stampa tutti i file conenuti nella lista list, che hanno minima distanza di edit.
 * @param list la lista contenente i vari file_name - absolute_path - edit_distance
 */
void print_min_distance(Sorted_List *sl, int limit);

/**
 * Permette di visualizzare la distanza di edit e la directory assoluta di un file.
 * @param distance la distanza di edit;
 * @param path la directory assoluta del file.
 */
void print_distance(int distance, char *path);

void search_files_and_print(char *inFile, char *directory, int limit) {

    File *file = get_File_Buffer(inFile);
    Sorted_List *list = new_list();
    get_list_file(list, file, directory);

    if (list == NULL) return;
    print_min_distance(list, limit);
    clear_list(list);

}

void get_list_file(Sorted_List *sList, File *file, char *dir) {
    DIR *dirp = NULL;
    struct dirent *dp;

    dirp = opendir(dir);
    while (!isNull(dp = readdir(dirp))) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            search_file(sList, file, dir, dp);
        }
    }
    closedir(dirp);
}


void search_file(Sorted_List *sList, File *file, char *dir, Dirent *dp) {

    struct stat stats;
    //char path[strlen(dir) + 256 + 2];
    char path[PATH_MAX];

    strcpy(path, dir);
    strcat(path, "/");
    strcat(path, dp->d_name);

    if (stat(path, &stats) != 0) {
        perror("stat error");
        exit(-1);
    }

    if (!S_ISDIR(stats.st_mode)) {
        int distance = calcolate_distance(file->nameFile, path);
        char *full = calloc(sizeof(char), PATH_MAX);
        //realpath(path, full);
        _fullpath(full, path, PATH_MAX);
        add(sList, new_element_list(dp->d_name, full, distance));
    } else {
        get_list_file(sList, file, path);
    }
}

void print_min_distance(Sorted_List *sl, int limit) {
    Element_List *node = sl->firstElement;
    if (isNull(node)) return;
    if (limit < 0) {
        limit = node->editDistance;
    }
    printf("\n");
    while (!isNull(node)) {
        if (node->editDistance <= limit) {
            print_distance(node->editDistance, node->path);
        }
        node = node->next;
    }
}

void print_distance(int distance, char *path) {
    printf("%i %s\n", distance, path);
}


