/* 
 * hello-1.c - The simplest kernel module. 
 */
#include <linux/kernel.h> /* Needed for pr_info() */ 
#include <linux/module.h> /* Needed by all modules */ 

MODULE_LICENSE("GPL");

int init_module(void) 
{ 
    pr_info("Hello world 1.\n");  
    return 0; 
} 
 
void cleanup_module(void) 
{ 
    pr_info("Goodbye world 1.\n"); 
} 


