#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

static int major = 0;
static struct file_operations fops = {};

static int __init my_init(void)
{
    major = register_chrdev(0, "hello_cdev", &fops);
    if (major < 0) {
        printk("hello_cdev - error registering\n");
        return major;
    }
    printk("hello_cdev - registered with major number %d\n", major);
    return 0;
}

static void __exit my_exit(void)
{
    unregitser_chrdev(major, "hello_cdev");
    printk("Goodbye - Goodbye, Kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John");
MODULE_DESCRIPTION("A simple driver for registering a character device.");