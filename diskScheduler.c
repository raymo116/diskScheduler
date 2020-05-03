#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "algorithms.h"


#define BUFFER_LEN 64

void read_file(FILE*, int_array*);
void run_given_algorithm(int_array* requests, int, int (*algorithm)(int, int_array*));
void print_int_array(int_array*);

/* disk scheduling algorithms */
int SCAN(int, int_array*);

int main(int argc, char const *argv[]) {
    /* initial cylinder position */
    int cyl_position = 4;
    /* cylinder request file */
    char* file = "test_cyl.txt";

    FILE* fptr = fopen(file, "r");

    int_array requests;
    read_file(fptr, &requests);

    run_given_algorithm(&requests, cyl_position, SCAN);

    delete_int_array(&requests);
    return 0;
}

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

    requests->content = malloc(sizeof(int)*requests->len);
    requests->len=0;

    while(1) {
        ret = fscanf(fptr, "%d", &val);

        if(ret == 1)
            requests->content[requests->len++] = val;
        else if(errno != 0) {
            perror("Error reading file:");
            exit(-1);
        } else if(ret == EOF) break;
    }
    requests->tail = requests->len;
}

void run_given_algorithm(int_array* requests, int init_pos, int (*algorithm)(int, int_array*)) {
    printf("%d\n", algorithm(init_pos, requests));
}

void print_int_array(int_array* ia) {
    int n;
    for (n = 0; n < ia->tail; n++) {
        printf("%d, ", ia->content[n]);
    }
    printf("\n");
}
