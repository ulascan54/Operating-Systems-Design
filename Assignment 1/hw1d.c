// Ulaş Can Demirbağ
// 20200702119
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // Ref -> https://man7.org/linux/man-pages/man2/gettimeofday.2.html

#define ARR_SIZE 50000000 // array size -> 50 million

int array[ARR_SIZE]; // create global array

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

    int subarr = atoi(argv[1]); // atoi -> convert the second argument to an integer, but we don't use it here because we run the code with a single process

    // initialize the array with random values
    for (int i = 0; i < ARR_SIZE; i++)
    {
        array[i] = rand() % 100; // Ref -> https://www.cplusplus.com/reference/cstdlib/rand/
    }

    save_arr("arrays/initial/ArrD.txt", array, ARR_SIZE); // save the initial array to a file

    struct timeval start, end;  // store the start and end times
    gettimeofday(&start, NULL); // get the current time before processing starts

    // update the array
    for (int i = 0; i < ARR_SIZE; i++)
    {
        array[i]++;
    }

    gettimeofday(&end, NULL); // get the current time after processing ends
    double exec_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
    // Ref -> https://stackoverflow.com/questions/37129865/how-to-collect-the-processing-time-in-c

    printf("Execution time: %f ms\n", exec_time);          // print the execution time
    save_arr("arrays//updated/ArrD.txt", array, ARR_SIZE); // save the updated array to a file

    return 0;
}
