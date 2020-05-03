/*
* @name: diskScheduler.c
* @author: Matt Raymond
* @email: raymo116@mail.chapman.edu
* @id: 2270559
* @date: 05/02/2020
* @version: 1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "algorithms.h"
#include "boilerplate.h"

/* a typedef so I can make an array of functions */
typedef int (*func_array) (int, int_array*);

/*
* the objective of this assignment consists of writing a C/C++ program that
* simulates the various disk-scheduling algorithms.
*
* the program will be passed the initial position of the disk head (as a
* parameter on the command line) as well as the file name containing the random
* cylinder requests. The program is to report the total amount of head movement
* required by each algorithm as a summary at the end of the program.
*/
int main(int argc, char const *argv[]) {
    /* all of the algorithms that have been implimented */
    func_array functions[] = {FCFS, SSTF, SCAN, CSCAN, LOOK, CLOOK};
    /* display names for the algorithms */
    char* names[] = {"FCFS", "SSTF", "SCAN", "C-SCAN", "LOOK", "C-LOOK"};

    /* checks to make sure that the inputs are correct */
    if(argc != 3) {
        printf("Usage: ./diskScheduler <initial cylinder position> <cylinder request file>\n");
        return -1;
    }
    else if ((atoi(argv[1]) < MIN_VAL) ||(atoi(argv[1]) > MAX_VAL)) {
        printf("Argument %s must be between %d and %d \n", argv[1], MIN_VAL, MAX_VAL);
        return -1;
    }

    /* opens the file passed */
    FILE* fptr = fopen(argv[2], "r");

    /* makes sure it's valid */
    if(fptr == NULL) {
        printf("Argument %s must be between a valid filepath\n", argv[2]);
        return -1;
    }

    /* reads the information out of the file */
    int_array requests;
    read_file(fptr, &requests);

    fclose(fptr);

    /* runs the algorithms on the requests */
    int i;
    for (i = 0; i < 6; ++i)
        printf("Total Head Movement for %s:\t%08d\n", names[i], functions[i](atoi(argv[1]), &requests));

    /* clean up the memory allocation */
    delete_int_array(&requests);
    return 0;
}
