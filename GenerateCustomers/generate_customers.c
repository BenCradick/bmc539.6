//
// Created by Ben Cradick on 4/16/18.
//
#ifndef DEBUG
#include "generate_customers.h"
#endif
#include <time.h>
#include <math.h>
#include <stdio.h>

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
    FILE *customers2;
    customers2 = fopen("customers", "ab+");
   const float MAX_TIME = 100;
#endif
#ifndef DEBUG
    const float MAX_TIME = 3600;
#endif
    customers = fopen("customers", "ab+");

    srand(time(0));

    do {
        arrival_t = rand() % 10;
        current_t += arrival_t;

        t_queue = rand() % 300 + 100;

#ifdef DEBUG
        printf("%-10x%-10x\n", current_t, t_queue);
#endif
        fwrite(&current_t, sizeof(current_t), 1, customers);
        fwrite(&t_queue, sizeof(t_queue), 1, customers);


    }while(current_t < MAX_TIME);
}