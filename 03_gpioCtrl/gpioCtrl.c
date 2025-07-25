#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio/consumer.h>

static struct gpio_desc *led;
static struct gpio_desc *button;

const int offset = 512;
const int IO_LED =  21 + offset;
const int IO_BUTTON = 20 + offset;

static int __init my_init(void)
{
	int status = 0;

	led = gpio_to_desc(IO_LED);
	if (!led) 
    {
		printk("gpioctrl - Error getting pin 21\n");
		return -ENODEV;
	}

	button = gpio_to_desc(IO_BUTTON);
	if (!button) 
    {
		printk("gpioctrl - Error getting pin 20\n");
		return -ENODEV;
	}

	status = gpiod_direction_output(led, 0);
	if (status) 
    {
		printk("gpioctrl - Error setting pin 20 to output\n");
		return status;
	}

	status = gpiod_direction_input(button);
	if (status) 
    {
		printk("gpioctrl - Error setting pin 21 to input\n");
		return status;
	}

	gpiod_set_value(led, 1);

	printk("gpioctrl - Button is %spressed\n", gpiod_get_value(button) ? "" : "not ");

	return 0;
}

static void __exit my_exit(void)
{
	gpiod_set_value(led, 0);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John");
MODULE_DESCRIPTION("An example of GPIO control");