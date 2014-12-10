/*=====================================
Filename:
	dev_test.c

Copyright (C) 2006 Wistron
All rights reserved.

Description:
	This is a simple program with testing ioctl() function.

Author/Created Date:
	Lumi-liu, Nov27'14

Modification History:


Note:


=====================================*/



#include <stdio.h>
#include <linux/types.h>
#include <linux/stat.h>
#include <fcntl.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/kdev_t.h>
#include <sys/types.h>  
#include <sys/stat.h>  
#include <sys/ioctl.h>  

#define SCULL_IOC_MAGIC  'k'   
#define SCULL_IOCRESET    _IO(SCULL_IOC_MAGIC, 0)  
  
#define SCULL_IOCSQUANTUM _IOW(SCULL_IOC_MAGIC,  1, int)  
#define SCULL_IOCSQSET    _IOW(SCULL_IOC_MAGIC,  2, int)  
#define SCULL_IOCTQUANTUM _IO(SCULL_IOC_MAGIC,   3)  
#define SCULL_IOCTQSET    _IO(SCULL_IOC_MAGIC,   4)  
#define SCULL_IOCGQUANTUM _IOR(SCULL_IOC_MAGIC,  5, int)  
#define SCULL_IOCGQSET    _IOR(SCULL_IOC_MAGIC,  6, int)  
#define SCULL_IOCQQUANTUM _IO(SCULL_IOC_MAGIC,   7)  
#define SCULL_IOCQQSET    _IO(SCULL_IOC_MAGIC,   8)  
#define SCULL_IOCXQUANTUM _IOWR(SCULL_IOC_MAGIC, 9, int)  
#define SCULL_IOCXQSET    _IOWR(SCULL_IOC_MAGIC,10, int)  
#define SCULL_IOCHQUANTUM _IO(SCULL_IOC_MAGIC,  11)  
#define SCULL_IOCHQSET    _IO(SCULL_IOC_MAGIC,  12)  
  
  
#define SCULL_P_IOCTSIZE _IO(SCULL_IOC_MAGIC,   13)  
#define SCULL_P_IOCQSIZE _IO(SCULL_IOC_MAGIC,   14)  
  
  
#define SCULL_IOC_MAXNR 14 

  
#define SCULL_DEVICE "/dev/globalmem"  
  
int main(int argc, char *argv[])  
{  
    int fd = 0;  
    int quantum = 8000;  
    int quantum_old = 0;  
    int qset = 2000;  
    int qset_old = 0;  
      
    fd = open(SCULL_DEVICE, O_RDWR);  
    if(fd < 0)  
    {  
        printf("open scull device error!\n");  
        return 0;  
    }  
  
    printf("SCULL_IOCSQUANTUM: quantum = %d\n", quantum);  
    ioctl(fd, SCULL_IOCSQUANTUM, &quantum);  
    quantum -= 500;  
    printf("SCULL_IOCTQUANTUM: quantum = %d\n", quantum);      
    ioctl(fd, SCULL_IOCTQUANTUM, quantum);  
      
    ioctl(fd, SCULL_IOCGQUANTUM, &quantum);  
    printf("SCULL_IOCGQUANTUM: quantum = %d\n", quantum);      
    quantum = ioctl(fd, SCULL_IOCQQUANTUM);  
    printf("SCULL_IOCQQUANTUM: quantum = %d\n", quantum);      
  
    quantum -= 500;  
    quantum_old = ioctl(fd, SCULL_IOCHQUANTUM, quantum);  
    printf("SCULL_IOCHQUANTUM: quantum = %d, quantum_old = %d\n", quantum, quantum_old);      
    quantum -= 500;  
    printf("SCULL_IOCXQUANTUM: quantum = %d\n", quantum);  
    ioctl(fd, SCULL_IOCXQUANTUM, &quantum);  
    printf("SCULL_IOCXQUANTUM: old quantum = %d\n", quantum);  
  
    printf("SCULL_IOCSQSET: qset = %d\n", qset);  
    ioctl(fd, SCULL_IOCSQSET, &qset);  
    qset += 500;  
    printf("SCULL_IOCTQSET: qset = %d\n", qset);  
    ioctl(fd, SCULL_IOCTQSET, qset);  
  
    ioctl(fd, SCULL_IOCGQSET, &qset);  
    printf("SCULL_IOCGQSET: qset = %d\n", qset);  
    qset = ioctl(fd, SCULL_IOCQQSET);  
    printf("SCULL_IOCQQSET: qset = %d\n", qset);  
  
    qset += 500;  
    qset_old = ioctl(fd, SCULL_IOCHQSET, qset);  
    printf("SCULL_IOCHQSET: qset = %d, qset_old = %d\n", qset, qset_old);      
    qset += 500;  
    printf("SCULL_IOCXQSET: qset = %d\n", qset);          
    ioctl(fd, SCULL_IOCXQSET, &qset);  
    printf("SCULL_IOCHQSET: old qset = %d\n", qset);  
  
    return 0;  
}
