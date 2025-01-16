#ifndef __GETPROCINFOF24_H
#define __GETPROCINFOF24_H

#include <linux/unistd.h>
#include <linux/types.h>
#include <errno.h>
extern int errno;
struct procInfoF24
{
    int flag;             /* flag for option */
    pid_t pid;            /* process id */
    pid_t parent_pid;     /* process id of parent process */
    long process_counter; /* counter value of the process */
    long nice;            /* nice value of the process */
    long parent_nice;     /* nice value of parent process’s owner */
    long uid;             /* user id of process owner */
    long gid;             /* group id of process owner */
    long val;             /* a value calculated with (20-nice)/4+1 */
};
_syscall1(int, getProcInfoF24, struct procInfoF24 *, data);

#endif
