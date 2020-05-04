/*
* @name: diskScheduler.c
* @author: Matt Raymond
* @email: raymo116@mail.chapman.edu
* @id: 2270559
* @date: 05/02/2020
* @version: 1.0
*/

#ifndef ALGORITHMS
#define ALGORITHMS

#include <stdio.h>
#include <stdlib.h>
#include "data_structures.h"
#include "boilerplate.h"

#define LEFT -1
#define RIGHT 1
#define MAX_VAL 199
#define MIN_VAL 0
#define INT_MAX 2147483647

/* first come first serve calgorithm */
int FCFS(int init_pos, int_array* requests) {
    /* if there are no requests, just skip out */
    if(requests->len == 0) return 0;

    /* find how far the head needs to move to the first request */
    int sum = abs(init_pos-requests->content[0]);

    /* find the distances between all other requests */
    int i;
    for (i = 0; i < requests->len-1; i++)
        sum += abs(requests->content[i]-requests->content[i+1]);

    return sum;
}

/* shortest seek time first */
int SSTF(int init_pos, int_array* requests) {
    /* Copy by value */
    int_array *ord_req = duplicate_int_array(requests);

    sort_int_array(ord_req, 1);

    /* find the place closest to the start */
    int index = -1;
    while(ord_req->content[index+1] < init_pos) ++index;

    /* finds the numbers to compare */
    int right, left;
    /* if the head starts on a request, you should look at the requests on
       either side. */
    if(ord_req->content[index] == init_pos) {
        right = index+1;
        left = index-1;
    }
    /* If the head starts between two requests, use those two */
    else {
        right = index;
        left = index-1;
    }

    /* cycle though, always finding the request that is closest */
    int right_delta, left_delta;
    int sum = abs(ord_req->content[index]-init_pos);
    while(1) {
        /* calculate the right and left distances */
        if(left > -1) left_delta = abs(ord_req->content[left]-ord_req->content[index]);
        else left_delta = INT_MAX;

        if(right < ord_req->len) right_delta = abs(ord_req->content[right]-ord_req->content[index]);
        else right_delta = INT_MAX;

        /* if it's shorter to the left, go left */
        if((right_delta > left_delta) && left > -1) {
            sum += left_delta;
            index = left--;
        }
        /* if it's shorter to the right, go right */
        else if(right < ord_req->len) {
            sum += right_delta;
            index = right++;
        }
        /* otherwise there are no other options */
        else break;
    }

    /* free memory */
    delete_int_array(ord_req);
    free(ord_req);

    return sum;
}

/*
* since SCAN, C-SCAN, LOOK, and C-LOOK are all so similar, we can use the same
* basic code with just a few minor tweeks so we don't have to rewrite it every
* time
*/
int SCAN_base(int init_pos, int_array* requests, int is_circular, int is_look) {
    /* vectors that hold requests to the left and right of the head position */
    int_array left, right;

    /* allocate memory */
    left.content = malloc(sizeof(int)*10);
    right.content = malloc(sizeof(int)*10);

    /* initialize primitives */
    left.len = 10;
    right.len = 10;
    left.tail = 0;
    right.tail = 0;

    /* the direction on the disk */
    int direction=RIGHT;

    /* if we're not supposed to look ahead (so SCAN and C-SCAN), then we need
    to go all the way to the edge of the disk before changing direction */
    if(is_look != 1) {
        if(is_circular == 1) {
            pushback(MIN_VAL, &left);
            pushback(MAX_VAL, &right);
        }
        else {
            // if (direction == LEFT) pushback(MIN_VAL, &left);
            // else if (direction == RIGHT)
            pushback(MAX_VAL, &right);
        }
    }

    int n;
    /* add requests to the vectors */
    for (n = 0; n < requests->len; n++) {
        if (requests->content[n] < init_pos)
            pushback(requests->content[n], &left);
        if (requests->content[n] > init_pos)
            pushback(requests->content[n], &right);
    }

    /* if it's circular (so C-SCAN and C-LOOK), we're going to want to always be
    headed in the same direction. Thus, our arrays are sorted in the direction
    we will be headed */
    if(is_circular == 1) {
        sort_int_array(&left, direction);
        sort_int_array(&right, direction);
    }
    /* If it's not circular, then we're going to sort them opositely so we can
    call the same for loop on them (just for simplifity) */
    else {
        sort_int_array(&left, -1);
        sort_int_array(&right, 1);
    }

    int sum= 0;
    /* written like this just to illustrate that we do right (1) and then
    left (-1) */
    for(n = RIGHT; n > -2; n-=2) {
        /* sum all on the right */
        if(direction == RIGHT) {
            int k;
            for (k = 0; k < right.tail; ++k) {
                sum += abs(init_pos-right.content[k]);
                init_pos = right.content[k];
            }
            direction = LEFT;
        }
        /* sum all on the left */
        else if(direction == LEFT) {
            int k;
            for (k = 0; k < left.tail; ++k) {
                sum += abs(init_pos-left.content[k]);
                init_pos = left.content[k];
            }
            direction = RIGHT;
        }
    }

    /* free memory */
    delete_int_array(&right);
    delete_int_array(&left);
    return sum;
}

/* performs the SCAN algorithm */
int SCAN(int init_pos, int_array* requests) {
    return SCAN_base(init_pos, requests, 0, 0);
}

/* performs the C-SCAN algorithm */
int CSCAN(int init_pos, int_array* requests) {
    return SCAN_base(init_pos, requests, 1, 0);
}

/* performs the LOOK algorit */
int LOOK(int init_pos, int_array* requests) {
    return SCAN_base(init_pos, requests, 0, 1);
}

/* performs the C-LOOK algorithm */
int CLOOK(int init_pos, int_array* requests) {
    return SCAN_base(init_pos, requests, 1, 1);
}

#endif
