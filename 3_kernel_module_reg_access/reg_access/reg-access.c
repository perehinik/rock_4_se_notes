/* 
 * reg-access.c - Accessing IO registers from kernel space. 
 */
#include <linux/kernel.h> /* Needed for pr_info() */ 
#include <linux/module.h> /* Needed by all modules */
#include <linux/ioport.h>
#include <asm/io.h>

#define GPIO_4_BASE		0xFF790000
#define GPIO_4_BLOCK_SIZE	32 * 1024 //32K
#define GPIO_2_BASE		0xFF780000
#define GPIO_2_BLOCK_SIZE       32 * 1024 //32K

#define OFFS_GPIO_DR		0x0000
#define OFFS_GPIO_DDR		0x0004
#define OFFS_GPIO_EXT		0x0050

static void __iomem * gpio_v_base;
static int memory_reserved = 0;
static unsigned int reg_data [GPIO_4_BLOCK_SIZE];

MODULE_LICENSE("GPL");

void read_registers(void) {
	void  __iomem * v_addr; // virtual address of register.

	v_addr = gpio_v_base + OFFS_GPIO_DR;
        pr_info(" DR    ADR:%p          VAL:%x\n", v_addr, readl(v_addr));

        v_addr = gpio_v_base + OFFS_GPIO_DDR;
        pr_info("DDR    ADR:%p         VAL:%x\n", v_addr, readl(v_addr));

        v_addr = gpio_v_base + OFFS_GPIO_EXT;
        pr_info("EXT    ADR:%p         VAL:%x\n", v_addr, readl(v_addr));
}


void save_states(void) {
	int i;
	for(i = 0; i < GPIO_4_BLOCK_SIZE-3; i+=4){
                reg_data[i] =(unsigned int)readl(gpio_v_base + i);
        }
}


void check_states(void) {
	int i;
	pr_info("-->> BASE ADR:%p", gpio_v_base);
	for(i = 0; i < GPIO_4_BLOCK_SIZE-3; i+=4){
               if (reg_data[i] != (unsigned int)readl(gpio_v_base + i)) {
	       		pr_info("ADR:%p   BEFORE:%x   AFTER:%x\n", gpio_v_base + i, reg_data[i], readl(gpio_v_base + i));
	       }
        }
}


int request_memory(void) {
	if (request_mem_region((unsigned long)GPIO_4_BASE, GPIO_4_BLOCK_SIZE, "CUSTOM_GPIO_DRIVER") == NULL) {
		pr_info("MEMORY IS BUSY");
		return 0;
	}
	pr_info("MEMORY RESERVED");
	return 1;
}

void release_memory(void) {
	release_mem_region((unsigned long)GPIO_4_BASE, GPIO_4_BLOCK_SIZE);
}


void log_ph_mem_region(unsigned long block_base, unsigned int block_size) {
	unsigned long i;
	void __iomem * v_base = ioremap(block_base, block_size);
	pr_info("READING %d BYTES STARTING %lx\n", block_size, block_base);
	for(i = 0; i < block_size-4; i+=2){
		unsigned long resss = (unsigned long)readw((void __iomem *)(v_base + i));
		pr_info("ADR: %lx 	OFS:%x 		DATA: %lx\n", block_base + i,(unsigned int)i, resss);
        }
	iounmap(v_base);
}

int init_module(void) {
	log_ph_mem_region(GPIO_4_BASE, 0x60);
	gpio_v_base = ioremap(GPIO_4_BASE, GPIO_4_BLOCK_SIZE);
	
	pr_info("Virtual address: %p\n", gpio_v_base);

	if (request_memory() == 1) 
	{
		pr_info("REG READ INIT\n");
		memory_reserved = 1;
		read_registers();
		save_states();
		release_memory();
	}
	return 0; 
} 
 
void cleanup_module(void) 
{ 
	if (memory_reserved == 1 && request_memory() == 1)
	{
		memory_reserved = 0;
		pr_info("REG READ CLEANUP\n");
		read_registers();
		check_states();
		release_memory();
	}
	log_ph_mem_region(GPIO_4_BASE, 0x60);
	iounmap(gpio_v_base);
    	pr_info("GPIO virtual space unmounted.");
} 


