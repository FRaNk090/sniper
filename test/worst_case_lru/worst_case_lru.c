#include "sim_api.h"

#include <pthread.h>
#include <stdio.h>

int main()
{
    int size = 131072;
    int a[size];

    for (int i = 0; i < size; ++i)
    {
        a[i] = i;
    }

    SimRoiStart();
    int loop_times = 10;

    for (int j = 0; j < loop_times; ++j)
    {
        for (int m = 0; m < size; ++m)
        {
            a[m]++;
        }
    }

    SimRoiEnd();
}