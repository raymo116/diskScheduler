/*
* @name: diskScheduler.c
* @author: Matt Raymond
* @email: raymo116@mail.chapman.edu
* @id: 2270559
* @date: 05/02/2020
* @version: 1.0
*/

#ifndef DEBUGGING_CODE
#define DEBUGGING_CODE

#include "algorithms.h"

/* prints the contents of a given array */
void print_int_array(int_array* ia) {
    int n;
    for (n = 0; n < ia->tail; n++) {
        printf("%d, ", ia->content[n]);
    }
    printf("\n");
}

#endif
