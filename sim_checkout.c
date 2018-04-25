#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#include "GenerateCustomers/generate_customers.h"
#endif
//time required to be serviced, time of arrival, time at front of line.
typedef struct{
    int t_service, t_enqueue, t_service_start;

    struct Customer *next;

}Customer;
//Overall queue structure: has a variable attached to the list that gives time spent idle, and the size of the list.
struct Queue{
    
    int t_idle, size;
    struct Customer *front, *back;

};
//Q is short for Queue
struct Queue* generateQ();
struct Customer* newCustomer(int t_service, int t_enqueue);

int main(){
    FILE *fp;
    fp = fopen("GenerateCustomers/customers", "rb");
    int num_customers = 0;


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
struct Queue* generateQ(){
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));
    
}
struct Customer *newCustomer(int t_service, int t_enqueue)
{
    //Customer
}
//TODO function to assign values to customers needs to iterate through array and get the hex in the right order.