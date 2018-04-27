//
// Created by Ben Cradick on 4/16/18.
//
#ifndef DEBUG
#include "generate_customers.h"
#endif
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void make_queue();
//allows me to test this class independently of the larger program, will write test script to test this file independently.
#ifdef DEBUG
int main(){
    make_queue();

}
#endif
void make_queue(){
    //t is short for time in these cases
    //used ints instad of floats to simplify testing
    //using a float is dumb, the OS famously uses a 32bit integer to represent time.
    int current_t = 0;
    int arrival_t;
    int t_queue;


    FILE *customers;
#ifdef DEBUG
   const float MAX_TIME = 3600;
#endif
#ifndef DEBUG
    const float MAX_TIME = 3600;
#endif
    customers = fopen("customers", "ab+");

    srand(time(0));
    int count = 1;
    do {
        arrival_t = rand() % 10;
        current_t += arrival_t;

        t_queue = rand() % 300 + 100;
        count++;

#ifdef DEBUG
        printf("%-10x%-10x\n%-10d", current_t, t_queue, count);
#endif
        fwrite(&current_t, sizeof(current_t), 1, customers);
        fwrite(&t_queue, sizeof(t_queue), 1, customers);


    }while(current_t < MAX_TIME);
    fclose(customers);
}