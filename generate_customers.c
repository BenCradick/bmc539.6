//
// Created by Ben Cradick on 4/16/18.
//

#include "generate_customers.h"
#include <time.h>
#include <math.h>

struct Customer {
    //t is short for time.
    float arrival_t;
    float t_queue;
};