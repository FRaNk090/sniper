#include "sim_api.h"
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>

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
    size_t arr_size = 10;
    size_t mem_size = sizeof(size_t) + sizeof(int) * 2 * arr_size;
    const key_t SHM_KEY = 0x1234;

    int shmid = shmget(SHM_KEY, mem_size, IPC_CREAT | 0666);
    void *shm = shmat(shmid, NULL, 0);

    memset(shm, 0, mem_size);

    size_t *ptr = (size_t *)shm;
    *ptr = arr_size;

    int *arr = (int *)(ptr + 1);

    // array 1
    size_t i;
    for (i = 0; i < arr_size; ++i)
    {
        *arr = (int)i;
        ++arr;
    }

    // array 2
    for (i = 0; i < arr_size; ++i)
    {
        *arr = 2;
        ++arr;
    }

    

    SimRoiStart();
    // print((int *)(ptr + 1), 10);
    SimFan(SHM_KEY, mem_size);
    SimRoiEnd();

    if (shmdt(shm) == -1)
    {
        perror("shmdt");
        return -1;
    }
    return 0;
}