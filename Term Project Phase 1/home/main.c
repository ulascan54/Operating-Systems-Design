#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <sys/resource.h>
#include <linux/getProcInfoF24.h>

void testAndDisplayProcessInfo(int flag)
{
    struct procInfoF24 teststruct;
    teststruct.flag = flag;

    int res = getProcInfoF24(&teststruct);
    if (res == 0)
    {
        printf("----------------------------------\n");
        printf("PROCESS INFORMATION:\n");
        printf(" - FLAG: %d\n", teststruct.flag);
        printf(" - PID: %d\n", teststruct.pid);
        printf(" - PARENT PID: %d\n", teststruct.parent_pid);
        printf(" - PROCESS COUNTER: %d\n", teststruct.process_counter);
        printf(" - NICE: %d\n", teststruct.nice);
        printf(" - PARENT NICE: %d\n", teststruct.parent_nice);
        printf(" - UID: %d\n", teststruct.uid);
        printf(" - GID: %d\n", teststruct.gid);
        printf(" - VAL: %d\n", teststruct.val);
        printf("----------------------------------\n");
    }
    else
    {
        printf("WARNING: System call returned with value %d\n", res);
    }
}

void changeProcessProperties()
{
    srand(time(NULL));
    gid_t new_gid = rand() % 100 + 1;
    uid_t new_uid = rand() % 100 + 1;
    int new_nice = rand() % 20 + 1;

    printf("----------------------------------\n");
    printf("Current GID: %d\n", getgid());
    printf("Current UID: %d\n", getuid());
    printf("Current NICE: %d\n", getpriority(PRIO_PROCESS, 0));
    printf("----------------------------------\n");

    if (setgid(new_gid) != 0)
    {
        perror("GID could not be changed!!!");
    }
    else
    {
        printf("New GID: %d\n", getgid());
    }

    if (setuid(new_uid) != 0)
    {
        perror("UID could not be changed!!!");
    }
    else
    {
        printf("New UID: %d\n", getuid());
    }

    if (setpriority(PRIO_PROCESS, 0, new_nice) != 0)
    {
        perror("NICE could not be changed!!!");
    }
    else
    {
        printf("New NICE: %d\n", getpriority(PRIO_PROCESS, 0));
    }
    printf("----------------------------------\n");
}

int main(int argc, char *argv[])
{
    int flag;

    if (argc != 2)
    {
        printf("Usage: %s <flag>\n", argv[0]);
        return 1;
    }

    flag = atoi(argv[1]);

    printf("\033[0;31m");
    testAndDisplayProcessInfo(flag);
    printf("\033[0m");
    if (flag <= 24 && flag > 0)
    {
        printf("\033[0;34m");
        changeProcessProperties();
        printf("\033[0m");
        printf("\033[0;32m");
        testAndDisplayProcessInfo(flag);
        printf("\033[0m");
    }
    printf("\033[0m \n");
    sleep(10);

    return 0;
}
