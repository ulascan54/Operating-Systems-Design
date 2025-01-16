// Ulaş Can Demirbağ
// 20200702119
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h> // Ref -> https://man7.org/linux/man-pages/man2/gettimeofday.2.html

#define ARR_SIZE 50000000 // array size -> 50 million

int array[ARR_SIZE];  // create an global array
pthread_mutex_t lock; // mutex for locking to ensure thread safety

// increment elements of the array within a specified subarray range
void *inc(void *arg)
{
    int *indx = (int *)arg;
    int s = indx[0];
    int e = indx[1];

    for (int i = s; i < e; i++)
    {
        pthread_mutex_lock(&lock); // lock the mutex before updating the array
        array[i]++;
        pthread_mutex_unlock(&lock); // unlock the mutex after updating
    }

    return NULL;
}

// save initial array and updated array to files
void save_arr(const char *fname, int *arr, int s)
{
    // Ref -> https://stackoverflow.com/questions/18597685/how-to-write-an-array-to-file-in-c
    FILE *file = fopen(fname, "w");
    if (file == NULL)
    {
        perror("ERR: File opening failed");
        exit(1);
    }
    for (int i = 0; i < 10; i++) // we don't need to write whole array to file replace (i<s) to (i<10) it is enough to see the result
    {
        fprintf(file, "%d\n", arr[i]);
    }
    fclose(file);
}

int main(int argc, char *argv[])
{
    // get the subbarray size from the arguments
    if (argc != 2)
    {
        printf("Usage: %s <subarr>\n", argv[0]);
        exit(1);
    }

    int subarr = atoi(argv[1]);           // atoi -> convert the second argument to an integer
    int nums_threads = ARR_SIZE / subarr; // calculate the number of threads needed

    // initialize the array with random values
    for (int i = 0; i < ARR_SIZE; i++)
    {
        array[i] = rand() % 100; // Ref -> https://www.cplusplus.com/reference/cstdlib/rand/
    }

    save_arr("arrays/initial/ArrB.txt", array, ARR_SIZE); // save the initial array to a file

    pthread_t threads[nums_threads]; // initialize the threads
    int indx[nums_threads][2];       // initialize the start and end indices for each thread

    pthread_mutex_init(&lock, NULL); // initialize the mutex

    struct timeval start, end;  // store the start and end times
    gettimeofday(&start, NULL); // get the current time before processing starts

    // create threads
    for (int i = 0; i < nums_threads; i++)
    {
        // set the start and end indices for each thread
        indx[i][0] = i * subarr;
        indx[i][1] = indx[i][0] + subarr;
        pthread_create(&threads[i], NULL, inc, indx[i]); // create a new thread
    }

    // wait for all threads to finish
    for (int i = 0; i < nums_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&end, NULL); // get the current time after processing ends
    double exec_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
    // Ref -> https://stackoverflow.com/questions/37129865/how-to-collect-the-processing-time-in-c

    printf("Execution time: %f ms\n", exec_time); // print the execution time

    save_arr("arrays//updated/ArrB.txt", array, ARR_SIZE); // save the updated array to a file

    pthread_mutex_destroy(&lock); // remove the mutex

    return 0;
}
