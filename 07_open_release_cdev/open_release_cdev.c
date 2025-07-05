#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

static int major;
static int my_open( struct inode *inode, struct file *filp )
{
	pr_info( "open_release_cdev - Major Device Number: %d\n Minor Device Number %d\n", imajor(inode), iminor(inode));

	pr_info( "open_release_cdev - filp->f_pos: %lld\n", filp->f_pos );
	pr_info( "open_release_cdev - filp->f_mode: 0x%x\n", filp->f_mode );
	pr_info( "open_release_cdev - filp->f_flags %x\n", filp->f_flags );			

	return 0;
}

static int my_release( struct inode *inode, struct file *filp )
{
	pr_info( "open_release_cdev - Release is called, file is closed.\n" );
	return 0;
}
static ssize_t my_read(struct file *f, char __user *u, size_t l, loff_t *o)
{
	printk("hello_cdev - Read is called\n");
	return 0;
}


static struct file_operations fops = 
{
	.open = my_open,
	.release = my_release,
	.read = my_read
};

static int __init my_init(void)
{
	major = register_chrdev(0, "hello_cdev", &fops);
	if (major < 0) 
    {
		printk("hello_cdev - Error registering chrdev\n");
		return major;
	}
	printk("hello_cdev - Major Device Number: %d\n", major);
	return 0;
}

static void __exit my_exit(void)
{
	unregister_chrdev(major, "hello_cdev");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John");
MODULE_DESCRIPTION("A sample driver for registering a character device");