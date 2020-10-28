#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filedistance.h"

/**
 * Stampa la lista dei comandi.
 */
void print_help();

int main(int argc, char *argv[]) {
    if (argc == 1) {
        print_help();
        return 0;
    } else if (strcmp(argv[1], "distance") == 0 && (argc == 4 || argc == 5)) {
        if (argc == 4) {
            distance(argv[2], argv[3]);
        } else {
            out_distance(argv[2], argv[3], argv[4]);
        }
    } else if (strcmp(argv[1], "apply") == 0 && argc == 5) {
        apply_changes(argv[2], argv[3], argv[4]);
    } else if (strcmp(argv[1], "search") == 0 && argc == 4) {
        search(argv[2], argv[3]);
    } else if (strcmp(argv[1], "searchall") == 0 && argc == 5) {
        search_all(argv[2], argv[3], strtol(argv[4], NULL, 10));
    } else {
        perror("Unknow command.\n");
        return -1;
    }

    return 0;
}

void print_help() {
    printf("\nList of commands:\n");
    printf("1) distance <file1> <file2>\n");
    printf("2) distance <file1> <file2> <outputFile>\n");
    printf("3) apply <inputFile> <filem> <outputFile>\n");
    printf("4) search <inputFile> <directory> \n");
    printf("5) searchall <inputFile> <directory> <limit>\n");
}

