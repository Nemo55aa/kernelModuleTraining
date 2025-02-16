// https://tldp.org/LDP/lkmpg/2.6/html/x351.html

#include <linux/kernel.h>
#include <linux/module.h>

int init_module(void)
{
	printk(KERN_INFO "Hello, world - this is the kernel speaking\n");
	printk(KERN_INFO "From: start.c\n");
	return 0;
}

MODULE_LICENSE("GPL");

