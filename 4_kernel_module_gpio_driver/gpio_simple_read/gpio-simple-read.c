/* 
 * gpio-simple-read.c - Simple kernel module to read state of GPIOs. 
 */
#include <linux/kernel.h> /* Needed for pr_info() */ 
#include <linux/module.h> /* Needed by all modules */
#include <asm/io.h>

#define GPIO_0_BASE 0xFF720000
#define GPIO_1_BASE 0xFF730000
#define GPIO_2_BASE 0xFF780000
#define GPIO_3_BASE 0xFF788000
#define GPIO_4_BASE 0xFF790000

MODULE_LICENSE("GPL");

int init_module(void) {
	unsigned int * addr;
	void * remap_adr;
	//addr = phys_to_virt(GPIO_4_BASE + 0x0000);
	//pr_info(" DR    %lx\n", *addr);

	//addr = phys_to_virt(GPIO_4_BASE + 0x0004);
        //pr_info("DDR    %lx\n", *addr);
	
	addr = (unsigned int *)GPIO_4_BASE + 0x0050;
        pr_info("EXT PHYS ADR   %p\n", addr);
	pr_info("EXT VIRT ADR   %p\n", phys_to_virt(GPIO_4_BASE + 0x0050));
	
	remap_adr = ioremap(GPIO_4_BASE + 0x0050, 4);
	pr_info("EXT V IOR ADR   %p\n", remap_adr);

	iounmap(remap_adr);

	return 0; 
} 
 
void cleanup_module(void) 
{ 
    pr_info("Goodbye world 1.\n"); 
} 


