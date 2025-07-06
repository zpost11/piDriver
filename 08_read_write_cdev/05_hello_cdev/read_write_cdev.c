#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

static int major;
static char text[64];

static ssize_t my_read(struct file *filp, char __user *user_buf, size_t len, loff_t *off)
{
	int not_copied = 0;
	int delta = 0;
	int to_copy = 0;

	if ((len + *off) < sizeof(text)) 
	{
		to_copy = len;
	} 
	else 
	{
		to_copy = sizeof(text) - *off;
	}

	if (*off >= sizeof(text)) 
	{
		pr_warn("read_write_cdev - offset greater than buffer size\n");
		return 0; //will fix this after completing tutorial
	}

	not_copied = copy_to_user(user_buf, &text[*off], to_copy);
	delta = to_copy - not_copied;

	if (not_copied)
	{
		pr_warn("read_write_cdev - Could only copy %d bytes\n", delta);
	}

	*off += delta;	
	pr_info("hello_cdev - Read is called\n");

	return delta;
}

static ssize_t my_write(struct file *filp, const char __user *user_buf, size_t len, loff_t *off)
{
	int not_copied = 0;
	int delta = 0;
	int to_copy = 0;

	if ((len + *off) < sizeof(text))
	{
		to_copy = len;
	}
	else
	{
		to_copy = (sizeof(text) - *off);
	}
	pr_info("hello_cdev - Write is called, we want to write %ld bytes, but actually only copying %d bytes. The offset is %lld\n", len, to_copy, *off);

	if (*off >= sizeof(text))
	{
		pr_warn("hello_cdev - Offset greater than buffer size\n");
		return 0; // will fix this after completing tutorial
	}

	not_copied = copy_from_user(&text[*off], user_buf, to_copy);
	delta = to_copy - not_copied;
	if (not_copied) 
	{
		pr_warn("hello_cdev - Could only copy %d bytes\n", delta);
	}

	*off += delta;
	return delta;
}

static struct file_operations fops = 
{
	.read = my_read,
	.write = my_write
};

static int __init my_init(void)
{
	major = register_chrdev(0, "hello_cdev", &fops);
	if (major < 0) 
    {
		printk("read_write_cdev - Error registering chrdev\n");
		return major;
	}
	printk("read_write_cdev - Major Device Number: %d\n", major);
	return 0;
}

static void __exit my_exit(void)
{
	unregister_chrdev(major, "read_write_cdev");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John");
MODULE_DESCRIPTION("A sample driver for registering a character device");