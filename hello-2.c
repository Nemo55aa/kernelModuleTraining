//https://tldp.org/LDP/lkmpg/2.6/html/hello2.html
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

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init hello_2_init(void)
{
	printk(KERN_INFO "Hello cave of the mighty computer 2..\n");
	return 0;
}

static void __exit hello_2_exit(void)
{
	printk(KERN_INFO "Goodbye warm, calm and dark place 2.\n");
}

MODULE_LICENSE("GPL");

module_init(hello_2_init);
module_exit(hello_2_exit);

