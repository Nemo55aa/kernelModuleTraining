#https://www.kernel.org/doc/Documentation/kbuild/makefiles.txt

#obj-m += hello-1.o
#obj-m += hello-2.o
#obj-m += hello-3.o
#obj-m += hello-4.o
#obj-m += startstop.o
#startstop-objs := start.o stop.o
obj-m += chardev.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
