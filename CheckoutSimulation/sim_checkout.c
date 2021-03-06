#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef DEBUG
#include "GenerateCustomers/generate_customers.h"
#endif

typedef struct Customer
{
    int t_service, t_enqueue, t_service_start, t_inline;

    struct Customer *next;

} Customer;
//Overall queue structure: has a variable attached to the list that gives time spent idle, and the size of the list.
typedef struct
{

    int t_idle, size;
    Customer *front, *back;

} Queue;
//Function prototypes.
//Q is short for Queue
Queue *generateQ();
Customer *newCustomer(int t_service, int t_enqueue);
void enQueue(Queue *queue, int t_service, int t_enqueue);
Customer *dequeue(Queue *queue);
int findShortestLine(Queue *queue[]);
int isEmpty(Queue *q);
void iterateIdles(Queue **, unsigned int *);
void checkNullFrontStarts(Queue **, int);
void checkForServed(Queue **, int, int *, int *, int *);
void checkForServed2(Queue **, int, int *);

int main()
{
    make_queue();
    FILE *fp;
    fp = fopen("customers", "rb");
    int num_customers = 0;
    int customers_served = 0;
    int t = 0;
    unsigned int t_idle = 0;
    int t_inline = 0;
    int t_wait = 0;

    int cashier = 0;

    Queue *cashiers[10];

    //throwaway node for bean counting
    Customer *temp;

    //initializing array of checkouts
    for (cashier = 0; cashier < 10; cashier++)
    {
        cashiers[cashier] = generateQ();
    }

    fseek(fp, 0L, SEEK_END);
    const int size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    int i = 0;
    unsigned char *buffer;
    buffer = (unsigned char *)malloc(size);
    Queue *holding = generateQ();
    //same thing but for secound method
    Queue *holding2 = generateQ();
    if (fp == NULL)
    { /*ERROR detection if file == empty*/

        exit(1);
    }
    else if (fread(buffer, sizeof *buffer, size, fp) != size)
    {

        exit(1);
    }
    else
    {
        fread(buffer, sizeof *buffer, size, fp);
    }
    int j;
    unsigned long a = 0;
    for (j = 0; j < size; j += 8)
    {
        int b;
        a = 0;
        for (b = 7; b >= 4; b--)
        {
            a <<= 8;
            a |= buffer[j + b];
        }

        int t_service = a;

        a = 0;
        //moving the binary format from a psuedo little endian to something more usable.
        for (b = 3; b >= 0; b--)
        {
            a <<= 8;
            a |= buffer[j + b];
        }

        int t_enqueue = a;

        enQueue(holding, t_service, t_enqueue);
        enQueue(holding2, t_service, t_enqueue);

        num_customers++;
    }

    for (t = 0; t <= 3600; t++)
    {

        while (t == holding->front->t_enqueue)
        {
            temp = dequeue(holding);
            cashier = findShortestLine(cashiers);
            if (cashiers[cashier]->size != 0)
            {
                t_inline += (3600 - temp->t_enqueue);
            }
            enQueue(cashiers[cashier], temp->t_service, temp->t_enqueue);
            if (cashiers[cashier]->size == 1)
            {
                cashiers[cashier]->front->t_inline = 1;
            }

            t_wait += (3600 - temp->t_enqueue);
        }
        iterateIdles(cashiers, &t_idle);
        checkNullFrontStarts(cashiers, t);

        checkForServed(cashiers, t, &customers_served, &t_wait, &t_inline);
    }
    printf("Using First Method:\n%-40s%f\n%-40s%u\n%-40s%u\n%-40s%u\n%-40s%f\n%-40s%f\n", "Average Cashier Idle Time:", (double)t_idle / 10, "Total Customers During Sim:", num_customers,
           "Customers Served:", customers_served, "Remaining Customers:", num_customers - customers_served, "Average Time in Line",
           (double)t_inline / num_customers, "Average Total Wait Time", (double)t_wait / num_customers);

    //Start of second method
    //initialize required variabels
    Queue *line = generateQ();
    Queue *cashiers2[10];
    for (t = 0; t < 10; t++)
    {
        cashiers2[t] = generateQ();
    }

    int nonimportant = 0;

    //rezero metrics to be measuered
    customers_served = 0;
    t_wait = 0;
    t_inline = 0;
    t_idle = 0;
    for (t = 0; t <= 3600; t++)
    {
        while (t == holding2->front->t_enqueue)
        {
            temp = dequeue(holding2);
            enQueue(line, temp->t_service, temp->t_service_start);
        }

        checkNullFrontStarts(cashiers2, t);
        checkForServed2(cashiers2, t, &customers_served);

        for (i = 0; i < 10; i++)
        {
            if (cashiers2[i]->front == NULL && line->front != NULL)
            {
                temp = dequeue(line);
                temp->t_inline = 1;
                enQueue(cashiers2[i], temp->t_service, temp->t_enqueue);

                t_wait++;
            }
        }
        t_inline += (line->size - 1);
        t_wait += (line->size);
        iterateIdles(cashiers2, &t_idle);
    }
    printf("Using second method:\n%-40s%f\n%-40s%u\n%-40s%u\n%-40s%u\n%-40s%f\n%-40s%f\n", "Average Cashier Idle Time:", (double)t_idle / 10, "Total Customers During Sim:", num_customers,
           "Customers Served:", customers_served, "Remaining Customers:", num_customers - customers_served, "Average Time in Line",
           (double)t_inline / num_customers, "Average Total Wait Time", (double)t_wait / num_customers);
    fclose(fp);
    return 0;
}
//Initializes a Q to be populated
Queue *generateQ()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->front = queue->back = NULL;
    queue->size = 0;
    return queue;
}
//initializes new customer node.
Customer *newCustomer(int t_service, int t_enqueue)
{
    Customer *temp = (Customer *)malloc(sizeof(Customer));
    temp->t_service = t_service;
    temp->t_enqueue = t_enqueue;
    temp->next = NULL;
    return temp;
}
//Put thing in Q
void enQueue(Queue *queue, int t_service, int t_enqueue)
{
    Customer *temp = newCustomer(t_service, t_enqueue);
    if (queue->back == NULL)
    {
        queue->front = queue->back = temp;
        queue->size++;
    }
    else
    {
        queue->back->next = temp;
        queue->back = temp;
        queue->size++;
    }
}
Customer *dequeue(Queue *queue)
{
    if (queue->front == NULL)
    {
        return NULL;
    }
    Customer *temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL)
    {
        queue->back = NULL;
    }
    queue->size--;
    return temp;
}
int findShortestLine(Queue *queue[])
{
    int i;
    int shortest = 0;
    for (i = 0; i < 10; i++)
    {
        if (queue[i]->size < queue[shortest]->size)
        {
            shortest = i;
        }
    }
    return shortest;
}
int isEmpty(Queue *q)
{
    if (q == NULL)
    {
        return 1;
    }
    return (q->front == NULL);
}
//sums total idle time, across queues, throughout simulation
void iterateIdles(Queue *q[], unsigned int *t_idle)
{
    int i;
    for (i = 0; i < 10; i++)
    {

        if (isEmpty(q[i]))
        {
            (*t_idle)++;
        }
    }
}
void checkNullFrontStarts(Queue *q[], int t)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        if (q[i]->front != NULL && q[i]->front->t_service_start == 0)
        {
            q[i]->front->t_service_start = t;
        }
    }
}
void checkForServed(Queue *q[], int t, int *customers_served, int *t_wait, int *t_inline)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        while (q[i]->front != NULL && (q[i]->front->t_service_start + q[i]->front->t_service) == t)
        {
            (*t_wait) -= (3600 - t);
            dequeue(q[i]);
            if (q[i]->front->t_inline != 1)
            {
                (*t_inline) -= (3600 - t);
            }
            (*customers_served)++;
        }
    }
}
void checkForServed2(Queue *q[], int t, int *customers_served)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        while (q[i]->front != NULL && (q[i]->front->t_service_start + q[i]->front->t_service) == t)
        {

            dequeue(q[i]);
            (*customers_served)++;
        }
    }
}