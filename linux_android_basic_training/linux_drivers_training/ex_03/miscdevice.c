 /*=====================================
Filename:
	miscdevice.c

Copyright (C) 2006 Wistron
	All rights reserved.

Description:
	This is a simple Character Device Drives with MISC. 

Author/Created Date:
     Lumi-liu, Nov25'14

Modification History:


Note:


=======================================*/

#include <linux/miscdevice.h>  
#include <linux/module.h>  
#include <linux/init.h>  
#include <linux/fs.h>  
#include <linux/slab.h>  

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Lumi-liu");

 
static long dev_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)  
{  
    printk ("misc dev_ioctl\n");  
    return 0;  
}  
  
static int dev_open(struct inode *inode, struct file *filp)  
{  
    printk ("misc in dev_open\n");  
    return 0;  
}  
static int dev_release(struct inode *inode, struct file *filp)  
{  
    printk ("misc dev_release\n");  
    return 0;  
}  
  
static ssize_t dev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)  
{  
      printk ("misc dev_read\n");  
      return 1;  
}  
  
static struct file_operations dev_fops =  
{  
    .owner   = THIS_MODULE,  
    .read    = dev_read,  
    .compat_ioctl   = dev_ioctl,  
    .open    = dev_open,  
    .release = dev_release  
};  
  
static struct miscdevice misc = {  
    .minor = MISC_DYNAMIC_MINOR,  
    .name = "misc_dev", 
    .fops = &dev_fops,  
};  
  
static int __init dev_init(void)  
{  
    int ret = misc_register(&misc);  
    printk ("misc dev initialized\n");  
    return ret;  
}  
  
static void __exit dev_exit(void)  
{  
    misc_deregister(&misc);  
    printk("misc dev unloaded\n");  
}  
  
module_init(dev_init);  
module_exit(dev_exit);
