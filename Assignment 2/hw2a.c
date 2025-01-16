// 20200702119
// Ulaş Can Demirbağ
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <semaphore.h>
#include <errno.h>
#include <time.h>

int L[3][3] = {
    {0, -1, 0},
    {-1, 4, -1},
    {0, -1, 0}};

void conv(int *A, int *B, int N, int row)
{
    for (int j = 0; j < N; j++) // convolution
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
        B[row * N + j] = total; // store in B
    }
}

void subt(int *A, int *B, int N, int row)
{
    for (int j = 0; j < N; j++) // subtract
    {
        int temp = A[row * N + j] - B[row * N + j];
        if (temp < 0)
            temp = 0;
        if (temp > 255)
            temp = 255;
        B[row * N + j] = temp; // store in B
    }
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

    char *filename = argv[1]; // read input file
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error: file not found\n");
        exit(0);
    }

    int N;
    fscanf(fp, "%d", &N); // read N

    size_t size = N * N * sizeof(int); // allocate shared memory
    int shm_fd = shm_open("/hw2_shm", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1)
    {
        printf("Error: shm_open\n");
        exit(0);
    }

    if (ftruncate(shm_fd, 2 * size) == -1)
    {
        printf("Error: ftruncate\n");
        exit(0);
    }

    void *shm_ptr = mmap(NULL, 2 * size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED)
    {
        printf("Error: mmap\n");
        exit(0);
    }

    int *A = (int *)shm_ptr;
    int *B = (int *)((char *)shm_ptr + size);

    for (int i = 0; i < N * N; i++)
    {
        fscanf(fp, "%d", &A[i]);
    }
    fclose(fp);

    sem_t *rowSems[N];
    for (int i = 0; i < N; i++)
    {
        char sem_name[256];
        snprintf(sem_name, sizeof(sem_name), "%s%d", "/rowsem_", i);
        sem_unlink(sem_name);
        rowSems[i] = sem_open(sem_name, O_CREAT | O_EXCL, 0666, 0);
        if (rowSems[i] == SEM_FAILED)
        {
            printf("Error: sem_open\n");
            exit(0);
        }
    }

    for (int i = 0; i < N; i++)
    {
        pid_t pid = fork();
        if (pid < 0) // fork error
        {
            printf("Error: fork\n");
            exit(0);
        }
        else if (pid == 0) // child process
        {
            conv(A, B, N, i);
            sem_post(rowSems[i]);
            exit(1);
        }
    }

    for (int i = 0; i < N; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(0);
        }
        else if (pid == 0) // child process
        {
            sem_wait(rowSems[i]);
            subt(A, B, N, i);
            exit(1);
        }
    }

    for (int i = 0; i < 2 * N; i++) // wait for all children
    {
        wait(NULL);
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

    FILE *output = fopen("a.txt", "a");
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
        char sem_name[256];
        snprintf(sem_name, sizeof(sem_name), "%s%d", "/rowsem_", i);
        sem_close(rowSems[i]);
        sem_unlink(sem_name);
    }

    munmap(shm_ptr, 2 * size);
    shm_unlink("/hw2_shm");
    close(shm_fd);

    return 0;
}