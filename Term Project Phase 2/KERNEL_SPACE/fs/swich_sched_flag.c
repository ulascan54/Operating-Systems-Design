#include <linux/swich_sched_flag.h>

int scheduler_flag = 0;

asmlinkage int sys_swich_sched_flag()
{
    scheduler_flag = scheduler_flag == 0 ? 1 : 0;
    printk("scheduler_flag = %d\n", scheduler_flag);
}
