//https://tldp.org/LDP/lkmpg/2.6/html/x569.html
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

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

// ----- Prototypes -----
int init_module(void);
void cleanup_module(void);

static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "nemochardev"
#define BUF_LEN 80

// majornumber assigned to our device driver
static int Major;
static int isDevOpened = 0;

static char msg[BUF_LEN];
static char *msg_Ptr;

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

int init_module(void)
{
	Major = register_chrdev(0, DEVICE_NAME, &fops);

	if(Major < 0){
		printk(KERN_ALERT "Registering char device failed with %d\n", Major);
	}

	printk(KERN_INFO "I was assigned major number %d. To talk to \n", Major);
	printk(KERN_INFO "the driver, create a dev file with \n");
	printk(KERN_INFO " 'mknod /dev/%s c %d 0'\n", DEVICE_NAME, Major);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "Remove the device file and module when done.\n");

	return SUCCESS;
}

void cleanup_module(void)
{
	//int ret = unregister_chrdev(Major, DEVICE_NAME);
	unregister_chrdev(Major, DEVICE_NAME);
	printk(KERN_INFO "chardev cleanuped\n");
	/*
	if(ret < 0){
		printk(KERN_ALERT "Error in unregister_chrdev: %d\n", ret);
	}
	*/
}

static int device_open(struct inode *, struct file *)
{
	static int counter = 0;
	if(isDevOpened)
		return -EBUSY;

	isDevOpened++;
	sprintf(msg, "I already told you %d times Hello world!\n", counter++);
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

static int device_release(struct inode *, struct file *)
{
	isDevOpened--;
	module_put(THIS_MODULE);
	return 0;
}

static ssize_t device_read(struct file *filp,
			 char *buf, 
			 size_t len,
			 loff_t * offset)
{
	int bytes_read = 0;

	if(*msg_Ptr == 0)
		return 0;
	
	while(len && *msg_Ptr){
		put_user(*(msg_Ptr++), buf++);

		len --;
		bytes_read++;
	}

	return bytes_read;
}
static ssize_t device_write(struct file *, const char *, size_t, loff_t *)
{
	printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
	return -EINVAL;
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nemo55aa");
MODULE_DESCRIPTION("A sample char device driver.");

