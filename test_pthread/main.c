#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// test pthread basic usage: create a sub thread.


typedef struct data
{
    float* pdata;
    int size;
} data;

float* sum;
data* global_data;

void* fill(void* num)
{
    int n = *((int*)num);
    global_data->size = n;
    global_data->pdata = (float*)malloc(n*sizeof(float));
    for (int i=0; i<n; i++)
    {
        global_data->pdata[i] = rand()%100;
    }
}

void* add()
{
    sum = (float*)malloc(sizeof(float));
    for (int i=0; i<global_data->size; i++)
    {
        *sum += global_data->pdata[i];
    }
}



int main(int argc, char const *argv[])
{
    int num = 1000;
    int* p = &num;
    pthread_t pthread_1, pthread_2;
    pthread_create(&pthread_1, NULL, fill, p);
    pthread_join(pthread_1, NULL);
    pthread_create(&pthread_2, NULL, add, NULL);
    pthread_join(pthread_2, NULL);
    printf("%f\n", *sum);
    return 0;
}
