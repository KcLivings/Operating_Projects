#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/kernel.h>
#include <linux/init_task.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

static int pid = 0; // process ID argument

module_param(pid, int, 0); // process ID argument


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

// function to print process information
void print_process_info(struct task_struct *task) {
    if (task == NULL) {
        return;
    }
  
    // Print current process information
    printk(KERN_INFO "Process name: %s\n", task->comm);
    printk(KERN_INFO "Process id: %d\n", task->pid);
    printk(KERN_INFO "Process state: %s\n", state_to_string(task->state));

    if (task->pid == 1) { // exit on init process
        return;
    }

    print_process_info(task->parent); // recursive call to parent process
}

//module initialization function
static int __init print_other_init(void) {
    struct task_struct *task;

    printk(KERN_INFO "print_other: Process ID argument is %d\n", pid);

    // get task_struct for specified process ID
    task = pid_task(find_vpid(pid), PIDTYPE_PID); 

    //exit on invalid task
    if (task == NULL) {
        printk(KERN_INFO "print_other: Invalid process ID\n");
        return -EINVAL;
    }

    // print process information
    print_process_info(task); 

    return 0;
}

//module exit function
static void __exit print_other_exit(void) {
    printk(KERN_INFO "print_other: Module exiting\n");
}

module_init(print_other_init);
module_exit(print_other_exit);
