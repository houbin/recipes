/* new.c */
#include <stdio.h>
#include <string.h> 
#include <sys/mman.h>
#include <dlfcn.h>
#include <stdint.h>

void print_v2(void)
{
    printf("Goodbye\n");
}

static void __attribute__((constructor)) init(void)
{ 
    int numpages;
    void *old_func_entry, *new_func_entry;

    old_func_entry = dlsym(NULL, "print");
    new_func_entry = dlsym(NULL, "print_v2");

    #define PAGE_SHIFT              12 
    #define PAGE_SIZE               (1UL << PAGE_SHIFT) 
    #define PAGE_MASK               (~(PAGE_SIZE-1))
    numpages = 2;
    void *old_func_entry_protect_address = (void *)((uint64_t)old_func_entry & PAGE_MASK);
    mprotect(old_func_entry_protect_address, numpages * PAGE_SIZE, PROT_READ|PROT_WRITE|PROT_EXEC);

    /*
     * Translate the following instructions 
     * 
     * mov $new_func_entry, %rax 
     * jmp %rax 
     * 
     * into machine code 
     * 
     * 48 b8 xx xx xx xx xx xx xx xx 
     * ff e0 
     */
    memset(old_func_entry, 0x48, 1);
    memset(old_func_entry + 1, 0xb8, 1); 
    memcpy(old_func_entry + 2, &new_func_entry, 8); 
    memset(old_func_entry + 10, 0xff, 1);
    memset(old_func_entry + 11, 0xe0, 1);
} 
