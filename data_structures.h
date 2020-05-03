/*
* @name: diskScheduler.c
* @author: Matt Raymond
* @email: raymo116@mail.chapman.edu
* @id: 2270559
* @date: 05/02/2020
* @version: 1.0
*/

#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

#include <stdlib.h>

/* a sort-of vector */
typedef struct{
    int* content;
    int len;
    int tail;
} int_array;

/* A function to duplicate an int array */
int_array* duplicate_int_array(int_array* b) {
    /* allocates memory */
    int_array* a = malloc(sizeof(int_array));
    a->content = malloc(sizeof(int)*b->len);

    /* copies the primitives */
    a->len = b->len;
    a->tail = b->tail;

    /* copies the array */
    int i;
    for (i = 0; i < a->len; ++i)
        a->content[i] = b->content[i];

    return a;
}

/* frees the memory held in an int array */
void delete_int_array(int_array* arr) {
    free(arr->content);
}

/* appends a value to the 'vector' */
void pushback(int i, int_array* ia) {
    /* checks to see if the array is full */
    if(ia->tail == ia->len) {

        /* allocates new memory */
        int* temp = malloc(sizeof(int)*(ia->len+10));

        /* copies the contents */
        int i;
        for(i = 0; i < ia->len; i++)
            temp[i] = ia->content[i];

        /* frees the old memory */
        free(ia->content);

        /* updates the values */
        ia->content = temp;
        ia->len+=10;
    }

    /* inserts a new element */
    ia->content[ia->tail++] = i;
}

#endif
