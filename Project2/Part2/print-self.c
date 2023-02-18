#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init_task.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

/*
*Function: switches an inputted state from its numeric version to its string version
*Input: Takes a long that represents the numeric state of the task
*Output: returns the corresponding string of the numeric state
*/
static const char *state_to_string(long state)
{
    switch (state) {
        case TASK_RUNNING:
            return "TASK_RUNNING";
        case TASK_INTERRUPTIBLE:
            return "TASK_INTERRUPTIBLE";
        case TASK_UNINTERRUPTIBLE:
            return "TASK_UNINTERRUPTIBLE";
        case __TASK_STOPPED:
            return "__TASK_STOPPED";
        case __TASK_TRACED:
            return "__TASK_TRACED";
        case TASK_DEAD:
            return "TASK_DEAD";
        case TASK_WAKEKILL:
            return "TASK_WAKEKILL";
        case TASK_WAKING:
            return "TASK_WAKING";
        case TASK_PARKED:
            return "TASK_PARKED";
        default:
            return "Unknown";
    }
}

//run on initialization
static int __init print_self_init(void)
{
    //create a struct from task_struct names task that holds the current tasks pid, name, and state
    struct task_struct *task = current;

    // Print current process information
    printk(KERN_INFO "Process name: %s\n", task->comm);
    printk(KERN_INFO "Process id: %d\n", task->pid);
    printk(KERN_INFO "Process state: %s\n", state_to_string(task->state));

    // Print parent process information until init, or pid = 1
    while (task->pid != 1) {
        task = task->parent;
        printk(KERN_INFO "Parent process name: %s\n", task->comm);
        printk(KERN_INFO "Parent process id: %d\n", task->pid);
        printk(KERN_INFO "Parent process state: %s\n", state_to_string(task->state));
    }

    return 0;
}

//give successful message on exit
static void __exit print_self_exit(void)
{
    printk(KERN_INFO "print_self module exiting\n");
}

module_init(print_self_init);
module_exit(print_self_exit);
