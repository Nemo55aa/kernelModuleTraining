//https://tldp.org/LDP/lkmpg/2.6/html/x121.html
/**
 * 1. makeする(See: *./Makefile*)、
 * 2.
 * $: sudo journalctl -f
 * 3. 
 * 	$: sudo modprobe ./hello-1.ko 
 * OR
 * 	$: sudo insmod ./hello-1.ko
 * 4.journalctlしたところにprintk()したメッセージが出てくる
 */
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
