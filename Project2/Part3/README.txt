//Report for Part 3 of Project 2

First, run "make all" to make the kernel module.
Then, run "su" and enter the password to enter root mode.
Then, run "insmod print_other.ko pid=<process id>" replacing <process id> with that of your choice to load the module. 
The command dmesg will show it displaying the process names, PID's, and state up to init of the process that was chosen. 
After running, "rmmod print_self" will unload the module. 
A dmesg command should show a message confirming unloading.
