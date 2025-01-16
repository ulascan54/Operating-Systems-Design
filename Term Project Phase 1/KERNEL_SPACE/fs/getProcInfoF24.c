#include <linux/getProcInfoF24.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <asm/uaccess.h>
#include <linux/types.h>

asmlinkage int sys_getProcInfoF24(struct procInfoF24 *data)
{
    cli();
    struct procInfoF24 pinfo;
    copy_from_user(&pinfo, data, sizeof(struct procInfoF24));

    struct task_struct *ctask;
    ctask = get_current();
    int value = (20 - ctask->nice) / 4 + 1;

    if (pinfo.flag > 24)
    {
        sti();
        return value;
    }
    else if (pinfo.flag <= 24 && pinfo.flag > 0)
    {
        pinfo.pid = ctask->pid;
        pinfo.parent_pid = ctask->p_opptr->pid;
        pinfo.process_counter = ctask->counter;
        pinfo.nice = ctask->nice;
        pinfo.parent_nice = ctask->p_opptr->nice;
        pinfo.uid = (long)ctask->uid;
        pinfo.gid = (long)ctask->gid;
        pinfo.val = value;
        copy_to_user(data, &pinfo, sizeof(struct procInfoF24));
        sti();
        return 0;
    }

    else
    {
        sti();
        return -1;
    }
}