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

#define GLOBALMEM_IOC_MAGIC  'k'   
#define GLOBALMEM_IOCRESET    _IO(GLOBALMEM_IOC_MAGIC, 0)  
  
#define GLOBALMEM_IOCSQUANTUM _IOW(GLOBALMEM_IOC_MAGIC,  1, int)  
#define GLOBALMEM_IOCSQSET    _IOW(GLOBALMEM_IOC_MAGIC,  2, int)  
#define GLOBALMEM_IOCTQUANTUM _IO(GLOBALMEM_IOC_MAGIC,   3)  
#define GLOBALMEM_IOCTQSET    _IO(GLOBALMEM_IOC_MAGIC,   4)  
#define GLOBALMEM_IOCGQUANTUM _IOR(GLOBALMEM_IOC_MAGIC,  5, int)  
#define GLOBALMEM_IOCGQSET    _IOR(GLOBALMEM_IOC_MAGIC,  6, int)  
#define GLOBALMEM_IOCQQUANTUM _IO(GLOBALMEM_IOC_MAGIC,   7)  
#define GLOBALMEM_IOCQQSET    _IO(GLOBALMEM_IOC_MAGIC,   8)  
#define GLOBALMEM_IOCXQUANTUM _IOWR(GLOBALMEM_IOC_MAGIC, 9, int)  
#define GLOBALMEM_IOCXQSET    _IOWR(GLOBALMEM_IOC_MAGIC,10, int)  
#define GLOBALMEM_IOCHQUANTUM _IO(GLOBALMEM_IOC_MAGIC,  11)  
#define GLOBALMEM_IOCHQSET    _IO(GLOBALMEM_IOC_MAGIC,  12)  
  
  
#define GLOBALMEM_P_IOCTSIZE _IO(GLOBALMEM_IOC_MAGIC,   13)  
#define GLOBALMEM_P_IOCQSIZE _IO(GLOBALMEM_IOC_MAGIC,   14)  
  
  
#define GLOBALMEM_IOC_MAXNR 14 

  
#define GLOBALMEM_DEVICE "/dev/globalmem"  
  
int main(int argc, char *argv[])  
{  
    int fd = 0;  
    int quantum = 8000;  
    int quantum_old = 0;  
    int qset = 2000;  
    int qset_old = 0;  
      
    fd = open(GLOBALMEM_DEVICE, O_RDWR);  
    if(fd < 0)  
    {  
        printf("open GLOBALMEM device error!\n");  
        return 0;  
    }  
  
    printf("GLOBALMEM_IOCSQUANTUM: quantum = %d\n", quantum);  
    ioctl(fd, GLOBALMEM_IOCSQUANTUM, &quantum);  
    quantum -= 500;  
    printf("GLOBALMEM_IOCTQUANTUM: quantum = %d\n", quantum);      
    ioctl(fd, GLOBALMEM_IOCTQUANTUM, quantum);  
      
    ioctl(fd, GLOBALMEM_IOCGQUANTUM, &quantum);  
    printf("GLOBALMEM_IOCGQUANTUM: quantum = %d\n", quantum);      
    quantum = ioctl(fd, GLOBALMEM_IOCQQUANTUM);  
    printf("GLOBALMEM_IOCQQUANTUM: quantum = %d\n", quantum);      
  
    quantum -= 500;  
    quantum_old = ioctl(fd, GLOBALMEM_IOCHQUANTUM, quantum);  
    printf("GLOBALMEM_IOCHQUANTUM: quantum = %d, quantum_old = %d\n", quantum, quantum_old);      
    quantum -= 500;  
    printf("GLOBALMEM_IOCXQUANTUM: quantum = %d\n", quantum);  
    ioctl(fd, GLOBALMEM_IOCXQUANTUM, &quantum);  
    printf("GLOBALMEM_IOCXQUANTUM: old quantum = %d\n", quantum);  
  
    printf("GLOBALMEM_IOCSQSET: qset = %d\n", qset);  
    ioctl(fd, GLOBALMEM_IOCSQSET, &qset);  
    qset += 500;  
    printf("GLOBALMEM_IOCTQSET: qset = %d\n", qset);  
    ioctl(fd, GLOBALMEM_IOCTQSET, qset);  
  
    ioctl(fd, GLOBALMEM_IOCGQSET, &qset);  
    printf("GLOBALMEM_IOCGQSET: qset = %d\n", qset);  
    qset = ioctl(fd, GLOBALMEM_IOCQQSET);  
    printf("GLOBALMEM_IOCQQSET: qset = %d\n", qset);  
  
    qset += 500;  
    qset_old = ioctl(fd, GLOBALMEM_IOCHQSET, qset);  
    printf("GLOBALMEM_IOCHQSET: qset = %d, qset_old = %d\n", qset, qset_old);      
    qset += 500;  
    printf("GLOBALMEM_IOCXQSET: qset = %d\n", qset);          
    ioctl(fd, GLOBALMEM_IOCXQSET, &qset);  
    printf("GLOBALMEM_IOCHQSET: old qset = %d\n", qset);  
  
    return 0;  
}
