//Report for part1 of project2

1) The makefile errors in redefinition of function names that already exist. The cleanup and init functions already exist in the build directory. An easy fix for this message printing object is just to change the names of the functions a little. I added "_message" to the end of both names and appropriately changed the calling of them as well.

2) The timestamps on the hello and goodbye reference to when the module was loaded with insmod and then unloaded with rmmod. There is a few seconds difference with the time it took me to run the lsmod command and to view the list and the output of the kernel ring buffer of the dmesg -T | tail command after I ran the insmod command to first install and view the module.

3) The easiest way to print to the console output would be to change the KERN-INFO to KERN-ALERT and then change the level of the KERN-ALERT message to print to console by setting the level to the console.
