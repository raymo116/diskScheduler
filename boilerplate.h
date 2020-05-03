/*
* @name: diskScheduler.c
* @author: Matt Raymond
* @email: raymo116@mail.chapman.edu
* @id: 2270559
* @date: 05/02/2020
* @version: 1.0
*/

#ifndef BOILERPLATE
#define BOILERPLATE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "data_structures.h"

/* reads the contents of a file into a vector */
void read_file(FILE* fptr, int_array *requests) {
    int ret, val;
    requests->len = 0;

    /* gets the length of the file */
    while(1) {
        ret = fscanf(fptr, "%d", &val);

        if(ret == 1) ++requests->len;
        else if(errno != 0) {
            perror("Error reading file:");
            exit(-1);
        } else if(ret == EOF) break;
    }

    rewind(fptr);

    /* allocate memory */
    requests->content = malloc(sizeof(int)*requests->len);
    requests->len=0;

    while(1) {
        ret = fscanf(fptr, "%d", &val);

        /* save file data this time */
        if(ret == 1)
            requests->content[requests->len++] = val;
        else if(errno != 0) {
            perror("Error reading file:");
            exit(-1);
        } else if(ret == EOF) break;
    }

    /* update the tail */
    requests->tail = requests->len;
}

/* sorts an array numerically (1), or reverse-numerically (-1) */
void sort_int_array(int_array* ia, int direction) {
    /* sort the list */
    int i, j;

    /* simple bubble sort */
    for (i = 0; i < ia->tail-1; i++) {
        for (j = 0; j < ia->tail-i-1; j++) {
            if(direction == 1) {
                if (ia->content[j] > ia->content[j+1]) {
                    int p = ia->content[j];
                    ia->content[j] = ia->content[j+1];
                    ia->content[j+1] = p;
                }
            }
            else {
                if (ia->content[j] < ia->content[j+1]) {
                    int p = ia->content[j];
                    ia->content[j] = ia->content[j+1];
                    ia->content[j+1] = p;
                }
            }

        }
    }
}

#endif
