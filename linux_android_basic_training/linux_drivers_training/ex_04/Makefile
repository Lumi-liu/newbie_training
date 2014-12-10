obj-m := globalmem.o
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
#PWD := $(shell pwd)
all:
	make -C $(KERNEL_DIR) SUBDIRS=$(shell pwd) modules
clean:
	rm -rf *.o *.ko *.mod.c *.mod.o *.symvers *.order .*.ko.cmd .*.o.cmd .*.mod.o.cmd .*.swp .tmp_versions

