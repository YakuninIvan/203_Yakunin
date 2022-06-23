#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct part
{
    int start;
    int end;
    int *point;
};

int counter = 0;
pthread_mutex_t mutex;

static void *threadfunc(void *args)
{
    int s = 0;

    int currsum = 0;
    struct part ex = *((struct part *)args);
    for (int i = ex.start; i < ex.end; i++)
    {
        currsum += ex.point[i];
    }
    s = pthread_mutex_lock(&mutex);
    counter += currsum;
    s = pthread_mutex_unlock(&mutex);
}

int main()
{

    int N;
    scanf("%d", &N);
    int *array = NULL;
    array = (int *)malloc(100);
    pthread_t p[4];
    int i;

    for (i = 0; i < N; i++)
    {
        scanf("%d", &array[i]);
    }

    struct part parts[4];
    parts[0].start = 0;
    parts[0].end = N / 4;
    struct part *parts_pointer[4];  
    for (int i = 1; i < 4; ++i)
    {
        parts[i].start = parts[i - 1].end;
        parts[i].end = parts[i].start + N / 4;
        parts[i].point = array;
        parts_pointer[i] = &(parts[i]);
        if (pthread_create(&p[i], NULL, &threadfunc, parts_pointer[i]) != 0)
        {
            return -1;
        }
    }

    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", counter);
    free(array);
    return 0;
}