#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG
#include "GenerateCustomers/generate_customers.h"
#endif
//time required to be serviced, time of arrival, time at front of line.
typedef struct Customer{
    int t_service, t_enqueue, t_service_start, t_dequeue;

    struct Customer *next;

}Customer;
//Overall queue structure: has a variable attached to the list that gives time spent idle, and the size of the list.
typedef struct{
    
    int t_idle, size;
    Customer *front, *back;

}Queue;
//Function prototypes.
//Q is short for Queue
Queue* generateQ();
Customer* newCustomer(int t_service, int t_enqueue);
void enQueue(Queue *queue, int t_service, int t_enqueue);
Customer *dequeue(Queue *queue);
int findShortestLine(Queue *queue[]);
int isEmpty(Queue *q);
void iterateIdles(Queue**, int);


    int main()
{
    FILE *fp;
    fp = fopen("GenerateCustomers/customers", "rb");
    int num_customers = 0;
    int t = 0;
    int t_idle = 0;

    int cashier = 0;

    Queue *cashiers[10];
    
    //throwaway node for bean counting
    Customer *temp;

    //initializing array of checkouts
    for(cashier = 0; cashier < 10; cashier++){
        cashiers[cashier] = generateQ();
    }


    fseek(fp, 0L, SEEK_END);
    const int size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    int i = 0;
    unsigned char *buffer;
    buffer = (unsigned char *) malloc(size);
    Queue *holding = generateQ();
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
        unsigned long a = 0;
        for(i=0; i<size;i+=8){
            int b;
            a = 0;
            for (b = 8; b >= 4; b--)
            {
                a <<= 8;
                a |= buffer[i + b];
            }
            int t_service = a;

            a=0;
            //moving the binary format from a psuedo little endian to something more usable.
            for(b=3; b >= 0; b--)
            {
                a <<= 8;
                a |= buffer[i + b];
            }
            int t_enqueue = a;
            enQueue(holding, t_service, t_enqueue);

        }
        for(t=0; t <= 3600; t++){
            if(t==holding->front->t_enqueue){
                temp = dequeue(holding);
                cashier = findShortestLine(cashiers);
                enQueue(cashiers[cashier], temp->t_service, temp->t_enqueue);
                }
            iterateIdles(cashiers, &t_idle);

        }
    }

    return 0;
}
//Initializes a Q to be populated
Queue* generateQ(){
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->back = NULL;
    queue->size = 0;
    return queue;
    
}
//initializes new customer node.
Customer *newCustomer(int t_service, int t_enqueue){
   Customer *temp = (Customer*)malloc(sizeof(Customer));
   temp->t_service = t_service;
   temp->t_enqueue = t_enqueue;
   temp->next = NULL;
   return temp;
}
//Put thing in Q
void enQueue(Queue *queue, int t_service, int t_enqueue){
    Customer *temp = newCustomer(t_service, t_enqueue);
    if(queue->back == NULL){
        queue->front = queue->back = temp;
        queue->size++;
        return;
    }
    queue->back->next = temp;
    queue->back = temp;
}
Customer *dequeue(Queue *queue){
    if(queue->front == NULL){
        return NULL;
    }
    Customer *temp = queue->front;
    queue->front = queue->front->next;
    if(queue->front == NULL){
        queue->back = NULL;
    }
    queue->size--;
    return temp;
}
int findShortestLine(Queue *queue[]){
    int i;
    int shortest = 0;
    for(i = 0; i < 10; i ++){
        if(queue[i]->size < queue[shortest]->size){
            shortest = i;
        }
    }
    return shortest;
}
int isEmpty(Queue *q){
    return(q->front == NULL);
}
void iterateIdles(Queue *q[], int t_idle){
    int i;
    for(i = 0; i < 10; i++){
        if(isEmpty(q[i])){t_idle++;}
    }
}