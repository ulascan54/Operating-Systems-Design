// Ulaş Can Demirbağ
// 20200702119
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h> // Ref -> https://man7.org/linux/man-pages/man7/sysvipc.7.html
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h> // Ref -> https://man7.org/linux/man-pages/man2/gettimeofday.2.html

#define ARR_SIZE 50000000 // array size -> 50 million

// increment elements of the array from start to end
void inc(int *arr, int s, int end)
{
    for (int i = s; i < end; i++)
    {
        arr[i]++;
    }
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

    int subarr = atoi(argv[1]);        // atoi -> convert the second argument to an integer
    int processes = ARR_SIZE / subarr; // calculate the number of processes needed

    // create a shared memory segment
    // Ref -> https://www.ibm.com/docs/en/zos/2.4.0?topic=functions-shmget-get-shared-memory-segment
    int shm_id = shmget(IPC_PRIVATE, ARR_SIZE * sizeof(int), IPC_CREAT | 0666);
    if (shm_id == -1) // check if the shared memory segment is created successfully
    {
        perror("ERR : shmget failed");
        exit(1);
    }
    int *sarray = shmat(shm_id, NULL, 0); // Attach the shared memory segment
    if (sarray == (void *)-1)
    {
        perror("ERR : shmat failed");
        exit(1);
    }

    // initialize the array with random values
    for (int i = 0; i < ARR_SIZE; i++)
    {
        sarray[i] = rand() % 100; // Ref -> https://www.cplusplus.com/reference/cstdlib/rand/
    }

    save_arr("arrays/initial/ArrA.txt", sarray, ARR_SIZE); // save the initial array to a file

    struct timeval start, end;  // store the start and end times
    gettimeofday(&start, NULL); // get the current time before processing starts

    // create child processes to increment parts of the array
    for (int i = 0; i < processes; i++)
    {
        pid_t pid = fork();
        if (pid == 0) // child process created successfully
        {
            // calculate start and end indices for the current subarray
            int si = i * subarr;
            int ei = si + subarr;
            inc(sarray, si, ei); // call increment function
            shmdt(sarray);       // detach the shared memory
            exit(0);
        }
        // fork failed note: between 1000 and 10000 processes can't be created. Because of the limit of the system. The error: Resource temporarily unavailable
        else if (pid == -1)
        {
            perror("fork failed");
            exit(1);
        }
    }

    // wait for all child processes to finish
    for (int i = 0; i < processes; i++)
    {
        wait(NULL);
    }

    gettimeofday(&end, NULL); // get the current time after processing ends
    double exec_time = (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
    // Ref -> https://stackoverflow.com/questions/37129865/how-to-collect-the-processing-time-in-c

    printf("Execution time: %f ms\n", exec_time); // print the execution time

    save_arr("arrays/updated/ArrA.txt", sarray, ARR_SIZE); // save the updated array to a file

    shmdt(sarray);                  // detach the shared memory
    shmctl(shm_id, IPC_RMID, NULL); // remove the shared memory segment

    return 0;
}
