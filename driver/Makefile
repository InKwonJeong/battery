obj-m := proc_file.o

KERNELDIR := /lib/modules/$(shell uname -r)/build 
EXTRADIR := /usr/include
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules 
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
