/*=====================================
Filename:
	globalmem.c

Copyright (C) 2006 Wistron
All rights reserved.

Description:
	This is a simple Character Device Drives with ioctl() function.

Author/Created Date:
	Lumi-liu, Nov26'14

Modification History:


Note:


=====================================*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <linux/kdev_t.h>
#include <asm/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>


MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Lumi-liu");


#define DEVICE_NAME "globalmem"
#define GLOBALMEM_SIZE 0x1000
#define MEM_CLEAR 0x1
//#define GLOBALMEM_MAJOR 255  //指定主设备号
#define GLOBALMEM_MAJOR 0  //动态申请主设备号

//#define MEMDEV_IOC_MAGIC  'k'

/* 定义命令 */
//#define MEMDEV_IOCPRINT   _IO(MEMDEV_IOC_MAGIC, 1)
//#define MEMDEV_IOCGETDATA _IOR(MEMDEV_IOC_MAGIC, 2, int)
//#define MEMDEV_IOCSETDATA _IOW(MEMDEV_IOC_MAGIC, 3, int)
//#define MEMDEV_IOC_MAXNR 3


#define SCULL_IOC_MAGIC 'k'
#define SCULL_IOCRESET  _IO(SCULL_IOC_MAGIC, 0)


#define SCULL_IOCSQUANTUM _IOW(SCULL_IOC_MAGIC, 1, int)
#define SCULL_IOCSQSET _IOW(SCULL_IOC_MAGIC, 2, int)

#define SCULL_IOCTQUANTUM _IO(SCULL_IOC_MAGIC, 3)
#define SCULL_IOCTQSET _IO(SCULL_IOC_MAGIC, 4)

#define SCULL_IOCGQUANTUM _IOR(SCULL_IOC_MAGIC, 5, int)
#define SCULL_IOCGQSET _IOR(SCULL_IOC_MAGIC, 6, int)

#define SCULL_IOCQQUANTUM _IO(SCULL_IOC_MAGIC, 7)
#define SCULL_IOCQQSET _IO(SCULL_IOC_MAGIC, 8)

#define SCULL_IOCXQUANTUM _IOWR(SCULL_IOC_MAGIC, 9, int)
#define SCULL_IOCXQSET _IOWR(SCULL_IOC_MAGIC, 10, int)

#define SCULL_IOCHQUANTUM _IO(SCULL_IOC_MAGIC, 11)
#define SCULL_IOCHQSET _IO(SCULL_IOC_MAGIC, 12)

#define SCULL_IOC_MAXNR  14
#define SCULL_QUANTUM 4000
#define SCULL_QSET 1000

int scull_quantum = SCULL_QUANTUM;
int scull_qset = SCULL_QSET;


static int globalmem_major = GLOBALMEM_MAJOR;
static struct class *globalmem_class;

//设备结构体
struct globalmem_dev
{
	struct cdev cdev;
	unsigned char mem[GLOBALMEM_SIZE];
};

//设备结构体指针
struct globalmem_dev *globalmem_devp;

//设备文件打开
int globalmem_open(struct inode *inode,struct file *filp)
{
	filp->private_data = globalmem_devp;
	return 0;
}

//设备文件释放
int globalmem_release(struct inode *inode, struct file *filp)
{
	return 0;
}

//设备文件控制
static long globalmem_ioctl(/*struct inode *inodep, */struct file *filp, unsigned int cmd, unsigned long arg)
{

//    struct globalmem_dev *dev = filp->private_data;
    
    int err = 0;
    int tmp;
    int retval = 0;

	if (_IOC_TYPE(cmd) != SCULL_IOC_MAGIC) 
		return -ENOTTY;
	if (_IOC_NR(cmd) > SCULL_IOC_MAXNR) 
		return -ENOTTY;
	/* 根据命令类型，检测参数空间是否可以访问 */
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user*)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ, (void __user*)arg, _IOC_SIZE(cmd));
	if (err) 
		return -EFAULT;


    switch(cmd)
    {
        case SCULL_IOCRESET:
            scull_quantum = SCULL_QUANTUM;
            scull_qset = SCULL_QSET;
            break;

        case SCULL_IOCSQUANTUM:
            if(!capable(CAP_SYS_ADMIN))
             return -EPERM;
            retval = __get_user(scull_quantum,(int __user *)arg);
            break;

        case SCULL_IOCTQUANTUM:
            if(!capable(CAP_SYS_ADMIN))
                return -EPERM;
            scull_quantum = arg;
            break;

        case SCULL_IOCGQUANTUM:
            retval = __put_user(scull_quantum, (int __user *)arg);
            break;

        case SCULL_IOCQQUANTUM:
            return scull_quantum;

        case SCULL_IOCXQUANTUM:
            if(!capable(CAP_SYS_ADMIN))
                return -EPERM;
            tmp = scull_quantum;
            retval = __get_user(scull_quantum,(int __user *)arg);
            if (retval == 0)
            {
                retval = __put_user(tmp,(int __user *)arg);
            }
            break;
        
        case SCULL_IOCHQUANTUM:
            if(!capable(CAP_SYS_ADMIN))
                return -EPERM;
            tmp = scull_quantum;
           scull_quantum = arg;
            return tmp;

        default:
            return -ENOTTY;

    }

    return retval;

}

/*
//设备文件控制
static long globalmem_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct globalmem_dev *dev = filp->private_data;

	int err = 0;
	int ret = 0;
	int ioarg = 0;
    

	if (_IOC_TYPE(cmd) != MEMDEV_IOC_MAGIC) 
		return -EINVAL;
	if (_IOC_NR(cmd) > MEMDEV_IOC_MAXNR) 
		return -EINVAL;
	if (_IOC_DIR(cmd) & _IOC_READ)
		err = !access_ok(VERIFY_WRITE, (void __user*)arg, _IOC_SIZE(cmd));
	else if (_IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok(VERIFY_READ, (void __user*)arg, _IOC_SIZE(cmd));
	if (err) 
		return -EFAULT;
        
	switch (cmd)
	{
		case MEM_CLEAR:
			memset(dev->mem,0,GLOBALMEM_SIZE);
			printk(KERN_INFO "globalmem is set to zero\n");
			break;
		case MEMDEV_IOCPRINT:
			printk(" CMD MEMDEV_IOCPRINT Done !\n");
			break;
		case MEMDEV_IOCGETDATA:
			ioarg = 1101;
			ret = __put_user(ioarg,(int *)arg);
			break;
		case MEMDEV_IOCSETDATA:
			ret = __get_user(ioarg,(int *)arg);
			printk("In kernel MEMDEV_IOCSETDATA ioarg is %d  ! n",ioarg);
			break;
		default:
			return -EINVAL;
	}
	return ret;  
}
*/

//设备文件读
static ssize_t globalmem_read(struct file *filp, char __user *buf, size_t size,loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;

	struct globalmem_dev *dev = filp->private_data;

	if (p > GLOBALMEM_SIZE) 
		return count ? -ENXIO: 0;
	//	return 0;
	if (count > GLOBALMEM_SIZE - p)
		count = GLOBALMEM_SIZE - p;

	if (copy_to_user(buf, (void*)(dev->mem + p), count))
	{
		ret = -EFAULT;
	}
	else
	{
		*ppos += count;
		ret = count;

		printk(KERN_INFO "read %u bytes(s) from %lu\n",count,p);
	}

	return ret;
}

//设备文件写
static ssize_t globalmem_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
	unsigned long p = *ppos;
	unsigned int count = size;
	int ret = 0;
	struct globalmem_dev *dev = filp->private_data;

	if (p > GLOBALMEM_SIZE)
		return count ? -ENXIO: 0;
	//	return 0;
	if (count > GLOBALMEM_SIZE - p)
		count = GLOBALMEM_SIZE - p;

	if (copy_from_user(dev->mem + p, buf, count))
	{
		ret = -EFAULT;
	}
	else
	{
		*ppos += count;
		ret = count;

		printk(KERN_INFO "written %u bytes(s) from %lu\n",count, p);
	}
	return ret;
}


static loff_t globalmem_llseek(struct file *filp, loff_t offset, int orig)
{
	loff_t ret = 0;
	switch (orig)
	{
		case 0:
			if (offset < 0)
			{
				ret = -EINVAL;
				break;
			}
			if ((unsigned int)offset > GLOBALMEM_SIZE)
			{
				ret = -EINVAL;
				break;
			}
			filp->f_pos = (unsigned int)offset;
			ret = filp->f_pos;
			break;
		case 1:
			if ((filp->f_pos + offset) > GLOBALMEM_SIZE)
			{
				ret = -EINVAL;
				break;
			}
			if ((filp->f_pos + offset) < 0)
			{
				ret = -EINVAL;
				break;
			}
			filp->f_pos += offset;
			ret = filp->f_pos;
			break;
		default:
			ret = -EINVAL;
			break;
	}
	return ret;
}


//文件操作结构体
static const struct file_operations globalmem_fops =
{
	.owner = THIS_MODULE,
	.llseek = globalmem_llseek,
	.read = globalmem_read,
	.write = globalmem_write,
//	.ioctl = globalmem_ioctl,
	.compat_ioctl = globalmem_ioctl,
//	.unlocked_ioctl = globalmem_ioctl,
	.open = globalmem_open,
	.release = globalmem_release,
};

//初始化并注册设备
static void globalmem_setup_cdev(struct globalmem_dev *dev, int index)
{
	int err;
	int devno = MKDEV(globalmem_major,index);
	cdev_init(&dev->cdev, &globalmem_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &globalmem_fops;
	err = cdev_add(&dev->cdev, devno, 1);
	if (err)
		printk(KERN_NOTICE "Error %d adding GLOBALMEM %d",err, index);
}


//设备模块加载
int globalmem_init(void)
{
	int result;

	dev_t devno = MKDEV(globalmem_major, 0);

	if (globalmem_major)
		result = register_chrdev_region(devno, 1, "globalmem");
	else
	{
		result = alloc_chrdev_region(&devno, 0, 1, "globalmem");
		globalmem_major = MAJOR(devno);
	}
	if (result < 0)
		return result;
	//动态申请结构体内存
	globalmem_devp = kmalloc(sizeof(struct globalmem_dev), GFP_KERNEL);
	if (!globalmem_devp)
	{
			result = -ENOMEM;
			goto fail_malloc;
	}
	memset(globalmem_devp, 0, sizeof(struct globalmem_dev));

	globalmem_setup_cdev(globalmem_devp, 0);

	globalmem_class =class_create(THIS_MODULE, "globalmem");   
    if( IS_ERR(globalmem_class) )   
    {   
        printk(KERN_NOTICE "creatglobalmem_class failed!");   
        return -1;   
    }   
   
    //创建一个设备节点，节点名字为globalmem   
    device_create(globalmem_class, NULL,MKDEV(globalmem_major, 0), 
					NULL, "globalmem");   
    printk(KERN_NOTICE "globalmem initialized!");
	return 0;
	
fail_malloc: 
	unregister_chrdev_region(devno, 1);
	return result;
}

void globalmem_exit(void)
{
	dev_t devno = MKDEV(globalmem_major, 0);
	device_destroy(globalmem_class,devno);
	class_destroy(globalmem_class);
	kfree(globalmem_devp);
	cdev_del(&globalmem_devp->cdev);
	unregister_chrdev_region(devno,/*MKDEV(globalmem_major, 0),*/ 1);
	printk(KERN_NOTICE "globalmem goodbye!");
}

module_param(globalmem_major, int, S_IRUGO);

module_init(globalmem_init);
module_exit(globalmem_exit);
