//https://sysprog21.github.io/lkmpg/#the-proc-file-system
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
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/version.h>

#define procfs_name "helloworld"

static struct proc_dir_entry *our_proc_file;

static ssize_t procfile_read(struct file *filep,
		char __user *buf,
		size_t buf_len,
		loff_t *offset)
{
	char s[13] = "HelloWorld!\n";
	int len = sizeof(s);
	int ret = len;

	if(*offset >= len || copy_to_user(buf, s, len)){
		pr_info("copy_to_user failed\n");
		ret = 0;
	} else {
		pr_info("procfile read %s\n", filep->f_path.dentry->d_name.name);
		*offset += len;
	}

	return ret;
}

static const struct proc_ops proc_file_fops = {
	.proc_read = procfile_read,
};

/*
static const struct file_operations proc_file_fops = {
	.read = procfile_read,
};
*/

int init_module(void)
{
	our_proc_file = proc_create(procfs_name , 0644, NULL, &proc_file_fops);

	if(NULL == our_proc_file){
		pr_alert("Error:Could not initialize /proc/%s\n", procfs_name);
		return -ENOMEM;
	}

	pr_info("/proc/%s created\n", procfs_name);
	return 0;
}

void cleanup_module(void)
{
	proc_remove(our_proc_file);
	pr_info("/proc/%s removed\n", procfs_name);
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nemo55aa");
MODULE_DESCRIPTION("A sample driver.");

//MODULE_SUPPORTED_DEVICE("testdevice");

