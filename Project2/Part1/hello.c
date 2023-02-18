#include <linux/module.h>
#include <linux/kernel.h>

int init_module_msg (void) {
	printk(KERN_ALERT "Hello world! \n");
	return 0;
}

void cleanup_module_msg (void) {
	printk(KERN_ALERT "Goodbye world! \n");
}

module_init(init_module_msg);
module_exit(cleanup_module_msg);

MODULE_LICENSE("GPL");
