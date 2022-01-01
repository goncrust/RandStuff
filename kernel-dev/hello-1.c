#include <linux/module.h>
#include <linux/kernel.h>

int __init init_hello(void) {
    printk("Hello, World!\n");
    return 0;
}

void __exit exit_goodbye(void) {
    printk("Goodbye, World!\n");
}

module_init(init_hello);
module_exit(exit_goodbye);
MODULE_LICENSE("GPL");
