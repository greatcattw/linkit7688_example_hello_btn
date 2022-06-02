ifneq ($(KERNELRELEASE),)
	obj-m:=hello_btn.o
	hello_btn-objs := interface_proc.o  io_i2c.o io_pcf8574.o
else
	KERNELDIR?="/home/ai7688/1208/AI7688H_OpenWRT_Build_FW_Setting_Tool_V1.0/openwrt/build_dir/target-mipsel_24kec+dsp_uClibc-0.9.33.2/linux-ramips_mt7688/linux-3.18.109"
	PWD:=$(shell pwd)


all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.ko *~ *.mod.c *.order *.symvers

endif








