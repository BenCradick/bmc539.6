//
// Created by Ben Cradick on 4/16/18.
//
#ifndef DEBUG
#include "generate_customers.h"
#endnif
#include <time.h>
#include <math.h>

void make_queue();
#ifdef DEBUG
int main(){
    make_queue();

}
#endif
void make_queue(){
    //t is short for time in these cases
    unsigned float current_t = 0;
    unsigned float arrival_t;
    unsigned float t_queue;

    FILE *customers;
#ifdef DEBUG
    FILE *customers2;
    customers2 = fopen("customers", "ab+");
#endif
    customers = fopen("customers", "ab+");

    srand(time(0));

    while(current_t < 3600){
        arrival_t = rand()%10;
        current_t += arrival_t;

        t_queue = rand()%300 + 100;

        #ifdef DEBUG
        printf("%10d-%10d-\n", current_t, t_queue);
        fwrite(current_t, sizeof(current_t), 1, customers2);
        fwrite(t_queue, sizeof(t_queue), 1, customers2);
        #endif
        fwrite(current_t, sizeof(current_t), 1, customers);


    }
}