//Report for Part 4 of Project 2

1) THe difference between the two is that a system call is a request by the user, through a given command from an execute, 
  to access some function within the kernl that fulfills the desired action. while a kernel module is a shared object built 
  speciafically to connect to the kernel to add function and fulfill a particular service. A kernel module is a way of 
  updating the kernel without having to rebuild the entire kernel with a new piece, rather just attaching the module onto 
  the kernel.

2) While the basic approach shown in the code is technically still valid, it will not work as-is on a modern Red Hat Linux system. For one, the sys_call_table array is no longer exported in newer versions of the Linux kernel, which means that this code will not compile as-is. To access the system call table, you would need to use other mechanisms such as kernel symbol lookups. Also, some of the function signatures and data structures used in this code are no longer be valid. This could result in compilation errors or even kernel panics if the code is loaded as a kernel module. And no, it failed to compile properly on my VM.
