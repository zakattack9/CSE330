#include<linux/syscalls.h>
#include<linux/kernel.h>

SYSCALL_DEFINE0(zak_sakata) {
  printk(KERN_INFO "\n Zak Sakata's syscall \n");
  return 0;
}