obj-m := hello.o
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
#PWD := $(shell pwd)
all:
	make -C $(KERNEL_DIR) SUBDIRS=$(shell pwd) modules
clean:
	rm *.o *.ko *.mod.c 

