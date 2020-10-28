//
// Created by Damiano on 28/08/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "filedistance.h"
#include "tools.h"
#include "distance.h"
#include "filechange.h"
#include "search.h"

void distance(char *fileName1, char *fileName2){
    start_timer();
    printf("Calculating ... ");
    int distance = calcolate_distance(fileName1, fileName2);
    printf("OK! \n");
    printf("EDIT DISTANCE : %i\n", distance);
    print_time();
}

void out_distance(char *fileName1, char *fileName2, char *outFileName){
    start_timer();
    printf("Calculating ... ");
    Stack *stk = generate_operation(fileName1, fileName2);
    save_operation(outFileName, stk);
    printf("OK! \n");
    clear_stack(stk);
    free(stk);
    print_time();
}

void apply_changes(char *fileName, char *filem, char *outFileName){
    start_timer();
    printf("Calculating ... ");
    edit_file(fileName, filem, outFileName);
    printf("OK! \n");
    print_time();
}

void search(char *fileName, char *dir){
    search_all(fileName, dir, -1);
}

void search_all(char *fileName, char *dir, int distance){
    start_timer();
    search_files_and_print(fileName,dir,distance);
    print_time();
}

