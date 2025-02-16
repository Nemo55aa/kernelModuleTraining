// https://tldp.org/LDP/lkmpg/2.6/html/x351.html

#include <linux/kernel.h>
#include <linux/module.h>

void cleanup_module(void)
{
	printk(KERN_INFO "Short is the life of a kernel module\n");
}

MODULE_LICENSE("GPL");
