#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
//#include "GenerateCustomers/generate_customers.h"
#endif

typedef struct{
    int t_queue;
    int t_enqueue;
    int t_dequeue;

}Customer;
//Overall queue structure: the current customer.
struct Queue{
    Customer current;
    Customer* next;

};

int main(){
    FILE *fp;
    fp = fopen("GenerateCustomers/customers", "rb");

    fseek(fp, 0L, SEEK_END);
    const int size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    int i = 0;
    unsigned char *buffer;
    buffer = (unsigned char *) malloc(size);
    if (fp == NULL){ /*ERROR detection if file == empty*/
        //printf("Error: There was an Error reading the file %s \n", fp);
        exit(1);
    }
    else if (fread(buffer, sizeof *buffer, size, fp) != size){
        //printf("Error: There was an Error reading the file %s - %d\n", path, "r");
        exit(1);
    }
    else{
        int i;
        fread(buffer, sizeof *buffer, size, fp);
        for(i=0; i<size;i+=4){
            printf("%02x%02x%02x%02x\t%d\n",buffer[i+3], buffer[i+2], buffer[i+1], buffer[i], i);
        }
    }

    return 0;
}

//TODO function to assign values to customers needs to iterate through array and get the hex in the right order.