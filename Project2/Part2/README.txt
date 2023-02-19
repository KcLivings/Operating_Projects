//Report for Part 2 of Project 2

1) Very similar to part 1, to load the module, run "make all". From there you need to run "su" and enter the password to enter root mode and then run "insmod print_self.ko" to load the module. The command dmesg will show it displaying the process names, PID's, and state up to init. After running, "rmmod print_self" will unload the module. A dmesg command should show a message confirming unloading.

2)
	1)The current pointed to the Insmod process.
	2) In our VM, the process with pid of 1 is called systemd and its state is TASK_INTERRUPTIBLE.
	3) The insmod process was in the state TASK_RUNNING, while every parent process up to init and including init was in the state TASK_INTERRUPTIBLE.
