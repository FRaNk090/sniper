#include "sim_api.h"

#include <pthread.h>
#include <stdio.h>

void print(int *array, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    };
    printf("\n");
}

int main()
{
    SimRoiStart();
    int size = 2;
    int a[2] = {1, 2};
    int b[2] = {4, 5};
    int c[2] = {0, 0};

    for (int i = 0; i < size; i++)
    {
        // c[i] = SimFan(a[i], b[i]);
        c[i] = a[i] + b[i];
    }
    printf("In main\n");
    // print(c, size);

    SimRoiEnd();
    return 0;
}