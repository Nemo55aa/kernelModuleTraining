//https://tldp.org/LDP/lkmpg/2.6/html/x121.html
#include <linux/init.h>
#include <linux/module.h>

int init_module(void)
{
	printk(KERN_INFO "Hello cave of the mighty computer 1..\n");

	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye warm, calm and dark place 1.\n");
}

MODULE_LICENSE("GPL");
