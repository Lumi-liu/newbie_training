/*==========================================
 Filename:
      hello.c

 Copyright (C) 2014 Wistron
 All rights reserved.

 Description:
      This file is a Device Driver and It can show some words on screen.

 Author/Created Date:
      Lumi-liu, Nov13,2014

 Modification History:

*/

#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
	printk(KERN_ALERT "hello world\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "goodbye\n");
}

module_init(hello_init);
module_exit(hello_exit);
