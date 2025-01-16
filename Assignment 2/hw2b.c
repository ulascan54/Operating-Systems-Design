// 20200702119
// Ulaş Can Demirbağ
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

int L[3][3] = {
    {0, -1, 0},
    {-1, 4, -1},
    {0, -1, 0}};

int *A;
int *B;
int N;
sem_t *rowSems;

void *conv(void *arg)
{
    int row = *(int *)arg;
    free(arg);
    for (int j = 0; j < N; j++)
    {
        int total = 0;
        for (int irow = -1; irow <= 1; irow++)
        {
            for (int icol = -1; icol <= 1; icol++)
            {
                int trow = row + irow;
                int tcol = j + icol;
                if (trow >= 0 && trow < N && tcol >= 0 && tcol < N)
                {
                    total += L[irow + 1][icol + 1] * A[trow * N + tcol];
                }
            }
        }
        B[row * N + j] = total;
    }
    sem_post(&rowSems[row]);
    return NULL;
}

void *subt(void *arg)
{
    int row = *(int *)arg;
    free(arg);
    sem_wait(&rowSems[row]);
    for (int j = 0; j < N; j++)
    {
        int val = A[row * N + j] - B[row * N + j];
        if (val < 0)
            val = 0;
        if (val > 255)
            val = 255;
        B[row * N + j] = val;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error: invalid arguments\n");
        exit(0);
    }

    struct timespec s, f;
    clock_gettime(CLOCK_MONOTONIC, &s);

    char *filename = argv[1];
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: file not found\n");
        exit(0);
    }
    fscanf(fp, "%d", &N);

    A = malloc(N * N * sizeof(int));
    B = malloc(N * N * sizeof(int));
    if (!A || !B)
    {
        printf("Memory allocation failed\n");
        exit(0);
    }

    for (int i = 0; i < N * N; i++)
    {
        fscanf(fp, "%d", &A[i]);
    }
    fclose(fp);

    rowSems = malloc(N * sizeof(sem_t));
    if (!rowSems)
    {
        printf("Memory allocation failed\n");
        exit(0);
    }

    for (int i = 0; i < N; i++)
    {
        sem_init(&rowSems[i], 0, 0);
    }

    pthread_t g1_threads[N];
    pthread_t g2_threads[N];

    for (int i = 0; i < N; i++)
    {
        int *arg = malloc(sizeof(int));
        *arg = i;
        if (pthread_create(&g1_threads[i], NULL, conv, arg) != 0)
        {
            printf("Error: pthread_create\n");
            exit(0);
        }
    }

    for (int i = 0; i < N; i++)
    {
        int *arg = malloc(sizeof(int));
        *arg = i;
        if (pthread_create(&g2_threads[i], NULL, subt, arg) != 0)
        {
            printf("Error: pthread_create\n");
            exit(0);
        }
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(g1_threads[i], NULL);
        pthread_join(g2_threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &f);
    double elapsed = f.tv_sec - s.tv_sec;
    elapsed += (f.tv_nsec - s.tv_nsec) / 1000000000.0;

    FILE *statm = fopen("/proc/self/statm", "r");
    int pages;
    long memory_usage = 0;
    if (statm != NULL)
    {
        if (fscanf(statm, "%d", &pages) == 1)
        {
            memory_usage = pages * sysconf(_SC_PAGESIZE);
        }
        fclose(statm);
    }

    FILE *output = fopen("b.txt", "a");
    if (output != NULL)
    {
        fprintf(output, "Input File: %s, Time: %f seconds, Memory: %ld bytes\n", filename, elapsed, memory_usage);
        fclose(output);
    }

    printf("%d\n", N);
    for (int i = 0; i < N * N; i++)
    {
        printf("%d\n", B[i]);
    }

    for (int i = 0; i < N; i++)
    {
        sem_destroy(&rowSems[i]);
    }
    free(rowSems);
    free(A);
    free(B);

    return 0;
}
