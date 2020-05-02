#ifndef ALGORITHMS
#define ALGORITHMS

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int* content;
    int len;
} int_array;

int_array* duplicate_int_array(int_array* b) {
    int_array* a = malloc(sizeof(int_array));
    
    a->content = malloc(sizeof(int)*b->len);
    a->len = b->len;
    int i;
    for (i = 0; i < a->len; ++i) {
        a->content[i] = b->content[i];
    }

    return a;
}

void delete_int_array(int_array* arr) {
    free(arr->content);
}

int FCFS(int init_pos, int_array* requests) {
    int sum = abs(init_pos-requests->content[0]);

    int i;
    for (i = 0; i < requests->len-1; i++)
        sum += abs(requests->content[i]-requests->content[i+1]);

    return sum;
}

int SSTF(int init_pos, int_array* requests) {
    /* Copy by value */
    int_array *ord_req = duplicate_int_array(requests);

    /* sort the list */
    int i, j;
    for (i = 0; i < ord_req->len-1; i++) {
        for (j = 0; j < ord_req->len-i-1; j++) {
            if (ord_req->content[j] > ord_req->content[j+1]) {
                int p = ord_req->content[j];
                ord_req->content[j] = ord_req->content[j+1];
                ord_req->content[j+1] = p;
            }
        }
    }

    /* find the place closest to the start */
    int index = 0;
    while(ord_req->content[index] < init_pos) ++index;

    /* finds the numbers to compare */
    int right, left;
    if(ord_req->content[index] == init_pos) {
        right = index+1;
        left = index-1;
    }
    else {
        right = index;
        left = index-1;
    }

    /* figure out which direction to go */
    int right_delta, left_delta, sum = 0;
    while(1) {
        right_delta = abs(ord_req->content[right]-ord_req->content[index]);
        left_delta = abs(ord_req->content[left]-ord_req->content[index]);
        if((right_delta > left_delta) && left > -1) {
            sum += left_delta;
            index = left--;
        }
        else if(right < ord_req->len) {
            sum += right_delta;
            index = right++;
        }
        else break;
    }

    delete_int_array(ord_req);
    free(ord_req);

    return sum;
}

#endif
