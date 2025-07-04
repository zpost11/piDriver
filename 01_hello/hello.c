#include <linux/module.h>
#include <linux/init.h>

int my_init(void)
{
    printk("Hello - Hello, Kernel!\n");
    /* this writes to the kernel's log. we need to have the 
    newline character so that we can see the message when this 
    function is called not after */
    return 0;
}

void my_exit(void)
{
    printk("Goodbye - Goodbye, Kernel!\n");
}

/* this tells "the module" which function to use for 
initialization and cleanup */
module_init(my_init);
module_exit(my_exit);

/* to make the module compilable, we need to add the following */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Zach");
MODULE_DESCRIPTION("A simple Hello World LKM");