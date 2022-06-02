#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/of_gpio.h>
#include <linux/i2c.h>
#include <linux/unistd.h>
#include "io_i2c.h"
#include "io_pcf8574.h" //mmm
#define NAME_OF_PROC 	("HELLO_BTN") //mmm

//static int hello_val=0;


unsigned char tmpbuf[64];


//-----------------------------------------------------
static int test_proc_open(struct inode *inode, struct file *file)
{
	return 0;
}



static ssize_t test_proc_read(struct file *file, char __user *buffer,size_t count, loff_t *f_pos)
{

	int len1;
	//int ret;
	if(*f_pos > 0)
		return 0;
	// limit length of string is 8, 0123456\n
	//ret= pcf8574_read_1byte(tmpbuf);
	//printk("%d\n",ret);

	//len1 = sprintf(buffer, "%s\n", tmpbuf);
	//len1 = sprintf(buffer, "%x\n", tmpbuf[0]);
	len1 = sprintf(buffer, "%x\n", btnx8_read());

	//printk("%s",buffer);
	*f_pos = *f_pos + len1;
	return len1;
}



static ssize_t test_proc_write(struct file *file, const char __user *buffer,size_t count, loff_t *f_pos)
{

//	int ret;

	if(count <= 0)
		return -EFAULT;
	printk("%s\n",__func__);
//	if(count > 8) {
//		count = (8); // "0123456\n" 8-byte is max for at24c02 write one go.
//		printk("max write is 8 byte, 0123456\\n\n");
//	}

//	if (buffer && !copy_from_user(tmpbuf, buffer, count)) {
//		tmpbuf[7]=0; //froce string end
//		tmpbuf[count-1]=0;//change  0x0a to 0x00 
//		ret=eeprom_write_1byte(tmpbuf);
//		//printk("test_proc_write = %d\n",ret);
//	}

	return count;
}



static struct file_operations test_fops = {
	.owner = THIS_MODULE,
	.open = test_proc_open,
	.read = test_proc_read,
	.write = test_proc_write,
	// .release = single_release,
	// .llseek = seq_lseek,
};


static int __init func_module_init(void)
{
	struct proc_dir_entry* file;
	int ret=0;
	file = proc_create(NAME_OF_PROC, 0644, NULL, &test_fops);
	if (!file)
		return -ENOMEM;

    
	ret=i2c_dev_init();
	btnx8_init(); //mmm
	return ret;
}



static void __exit func_module_exit(void)
{
	remove_proc_entry(NAME_OF_PROC, NULL);
	i2c_dev_exit();

}

module_init(func_module_init);
module_exit(func_module_exit);

MODULE_AUTHOR("greatcat@ms18.hinet.net");
MODULE_DESCRIPTION("proc_module "+NAME_OF_PROC);
MODULE_LICENSE("GPL");



