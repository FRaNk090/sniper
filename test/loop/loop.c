#include "sim_api.h"

#include <pthread.h>
#include <stdio.h>

int main()
{
    SimRoiStart();
    int size = 2;
    int a[2] = {1, 2};
    int b[2] = {3, 4};
    int c[2];

    for (int i = 0; i < size; i++)
    {
        c[i] = a[i] + b[i];
        printf('%d', c[i]);
    }
    SimRoiEnd();
    return 0;
}