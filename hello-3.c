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

static int hello3_data __initdata = 3;
static int __initdata initdata = 0xff;

static int __init hello_3_init(void)
{
	printk(KERN_INFO "initdata: %2X\n", initdata);
	printk(KERN_INFO "Hello cave of the mighty computer %d..\n", hello3_data);
	return 0;
}

static void __exit hello_3_exit(void)
{
	printk(KERN_INFO "Goodbye warm, calm and dark place 3.\n");
}

MODULE_LICENSE("GPL");

module_init(hello_3_init);
module_exit(hello_3_exit);

