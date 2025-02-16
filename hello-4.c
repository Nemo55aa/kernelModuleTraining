//https://tldp.org/LDP/lkmpg/2.6/html/x245.html
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

static int __init hello_4_init(void)
{
	printk(KERN_INFO "Hello cave of the mighty computer 4..\n");
	return 0;
}

static void __exit hello_4_exit(void)
{
	printk(KERN_INFO "Goodbye warm, calm and dark place 4.\n");
}

module_init(hello_4_init);
module_exit(hello_4_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nemo55aa");
MODULE_DESCRIPTION("A sample driver.");

//MODULE_SUPPORTED_DEVICE("testdevice");
