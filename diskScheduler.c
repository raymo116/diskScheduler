#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "algorithms.h"
#include "boilerplate.h"

typedef int (*func_array) (int, int_array*);

int main(int argc, char const *argv[]) {
    func_array functions[] = {FCFS, SSTF, SCAN, CSCAN, LOOK, CLOOK};

    /* initial cylinder position */
    int cyl_position = 4;
    /* cylinder request file */
    char* file = "test_cyl.txt";

    FILE* fptr = fopen(file, "r");

    int_array requests;
    read_file(fptr, &requests);

    int i;
    for (i = 0; i < 6; ++i) {
        run_given_algorithm(&requests, cyl_position, functions[i]);
    }


    delete_int_array(&requests);
    return 0;
}
