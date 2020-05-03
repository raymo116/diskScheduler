#ifndef ALGORITHMS
#define ALGORITHMS

#include <stdio.h>
#include <stdlib.h>

#define LEFT -1
#define RIGHT 1

typedef struct{
    int* content;
    int len;
    int tail;
} int_array;

int_array* duplicate_int_array(int_array* b) {
    int_array* a = malloc(sizeof(int_array));

    a->content = malloc(sizeof(int)*b->len);
    a->len = b->len;
    a->tail = b->tail;
    int i;
    for (i = 0; i < a->len; ++i) {
        a->content[i] = b->content[i];
    }

    return a;
}

void delete_int_array(int_array* arr) {
    free(arr->content);
}

void pushback(int i, int_array* ia) {
    if(ia->tail == ia->len) {
        int* temp = malloc(sizeof(int)*(ia->len+10));

        int i;
        for(i = 0; i < ia->len; i++) {
            temp[i] = ia->content[i];
        }

        free(ia->content);
        ia->content = temp;
    }
    ia->content[ia->tail++] = i;
}

int FCFS(int init_pos, int_array* requests) {
    int sum = abs(init_pos-requests->content[0]);

    int i;
    for (i = 0; i < requests->len-1; i++)
        sum += abs(requests->content[i]-requests->content[i+1]);

    return sum;
}

void sort_int_array(int_array* ia, int dir) {
    /* sort the list */
    int i, j;
    for (i = 0; i < ia->tail-1; i++) {
        for (j = 0; j < ia->tail-i-1; j++) {
            if(dir == 1) {
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

int SSTF(int init_pos, int_array* requests) {
    /* Copy by value */
    int_array *ord_req = duplicate_int_array(requests);

    sort_int_array(ord_req, 1);

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

int SCAN_base(int init_pos, int_array* requests, int is_circular, int is_look) {

    int_array left, right;
    left.content = malloc(sizeof(int)*10);
    right.content = malloc(sizeof(int)*10);
    left.len = 10;
    right.len = 10;
    left.tail = 0;
    right.tail = 0;

    int max= 9;
    int direction=0;

    /* Find which direction to start in */
    int n;
    for (n = 0; n < requests->len; ++n) {
        if(requests->content[n] != init_pos) {
            if(requests->content[n] > init_pos) direction = RIGHT;
            else direction = LEFT;
            break;
        }
    }

    if(is_look != 1) {
        if (direction == LEFT) pushback(0, &left);
        else if (direction == RIGHT) pushback(max, &right);
    }

    for (n = 0; n < requests->len; n++) {
        if (requests->content[n] < init_pos)
            pushback(requests->content[n], &left);
        if (requests->content[n] > init_pos)
            pushback(requests->content[n], &right);
    }

    if(is_circular == 1) {
        sort_int_array(&left, direction);
        sort_int_array(&right, direction);
    }
    else {
        sort_int_array(&left, -1);
        sort_int_array(&right, 1);
    }

    int sum= 0;
    for(n = RIGHT; n > -2; n-=2) {
        if(direction == RIGHT) {
            int k;
            for (k = 0; k < right.tail; ++k) {
                sum += abs(init_pos-right.content[k]);
                init_pos = right.content[k];
            }
            direction = LEFT;
        }
        else if(direction == LEFT) {
            int k;
            for (k = 0; k < left.tail; ++k) {
                sum += abs(init_pos-left.content[k]);
                init_pos = left.content[k];
            }
            direction = RIGHT;
        }
    }


    delete_int_array(&right);
    delete_int_array(&left);
    return sum;
}

int SCAN(int init_pos, int_array* requests) {
    return SCAN_base(init_pos, requests, 0, 0);
}

int CSCAN(int init_pos, int_array* requests) {
    return SCAN_base(init_pos, requests, 1, 0);
}

int LOOK(int init_pos, int_array* requests) {
    return SCAN_base(init_pos, requests, 0, 1);
}

int CLOOK(int init_pos, int_array* requests) {
    return SCAN_base(init_pos, requests, 1, 1);
}

#endif
