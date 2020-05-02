#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "algorithms.h"


#define BUFFER_LEN 64

void read_file(FILE*, int_array*);
void run_given_algorithm(int_array* requests, int, int (*algorithm)(int, int_array*));

/* disk scheduling algorithms */
int SCAN(int, int_array*);

int main(int argc, char const *argv[]) {
    /* initial cylinder position */
    int cyl_position = 1;
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
}

void run_given_algorithm(int_array* requests, int init_pos, int (*algorithm)(int, int_array*)) {
    printf("%d\n", algorithm(init_pos, requests));
}

int SCAN(int init_pos, int_array* requests) {
    int max= 9;
    int_array* first, *second;
    first = duplicate_int_array(requests);
    second = duplicate_int_array(requests);
    second->len = 0;

    int direction=0;

    /* Ignore when the head starts at the first place */
    int n;
    for (n = 0; n < first->len; ++n) {
        if(first->content[n] != init_pos) {
            if(first->content[n] > init_pos) direction = 1;
            else direction = -1;
            break;
        }
    }

    /* find the distance between the read head and the first place */
    int sum = abs(init_pos-first->content[n]);

    /* find one scan through */
    int current = first->content[n];
    printf("current: %d\n", current);
    for (; n < first->len; n+=direction) {
        if((first->content[n]-current)*direction >= 0) {
            sum += abs(first->content[n]-current);
            current = first->content[n];
        }
        else {
            second->content[second->len++]=first->content[n];
        }
    }

    printf("sum: %d\n", sum);
    printf("first: ");
    int p;
    for (p = 0; p < first->len; p++) {
        printf("%d, ", first->content[p]);
    }
    printf("\nsecond: ");
    for (p = 0; p < second->len; p++) {
        printf("%d, ", second->content[p]);
    }
    printf("\n");

    if(current == max) {
        int_array* temp = first;
        first = second;
        second=temp;

        second->len = 0;
        n = first->len-1;
        direction = -direction;
        current = first->content[n];
    }

    for (; n > -1; n+=direction) {
        if((first->content[n]-current)*direction >= 0) {
            sum += abs(first->content[n]-current);
            current = first->content[n];
        }
        else {
            second->content[second->len++]=first->content[n];
        }
    }

    if(second->len == 0) {
        printf("completed\n");
    }


    delete_int_array(first);
    free(first);
    delete_int_array(second);
    free(second);
    return -1;
}
