PWD = $$(pwd)
REL = $$(uname -r)


obj-m := hello-1.o

all:
	make -C /lib/modules/$(REL)/build M=$(PWD)

clean:
	make -C /lib/modules/$(REL)/build M=$(PWD) clean
