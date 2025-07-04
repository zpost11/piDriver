#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>

static struct gpiod_desc *led;
static struct gpiod_desc *button;

const int PinOffset = 512;
const int IO_LED = 21 + PinOffset;
const int IO_BUTTON = 20 + PinOffset;

static int __init my_init(void)
{
    int status = 0;

    led = gpio_to_desc(IO_LED);
    if (!led) 
    {
        printk("Failed to get GPIO descriptor for LED\n");
        return -ENODEV;
    }

    button = gpio_to_desc(IO_BUTTON);
    if (!button) 
    {
        printk("Failed to get GPIO descriptor for Button\n");
        gpiod_put(led);
        return -ENODEV;
    }

    status = gpiod_direction_output(led, 0);
    if(status)
    {
        printk("Failed to set LED direction\n");
        return status;
    }

    status = gpiod_direction_input(button);
    if (status) 
    {
        printk("Failed to set Button direction\n");
        return status;
    }

    gpiod_set_value(led, 1);
    printk("gpioctrl - button is %spressed\n", gpiod_get_value(button) ? "": "not ");

    return 0;
}

static void __exit my_exit(void)
{
    gpio_set_value(led, 0);
    printk("Goodbye - Goodbye, Kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John");
MODULE_DESCRIPTION("A simple GPIO control module");