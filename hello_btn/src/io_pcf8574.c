#include <linux/delay.h>
#include <linux/i2c.h>
#include "io_pcf8574.h" //mmm



extern struct i2c_client  *ext_i2c_dev;
unsigned char b1 = 0xff;

int pcf8574_write_1byte(unsigned char *buf1){

	//return 	i2c_smbus_write_i2c_block_data(ext_i2c_dev, 0, 1, buf1);
	return  i2c_master_send(ext_i2c_dev, buf1, 1);    
}




int pcf8574_read_1byte(unsigned char *buf1){
	//return i2c_smbus_read_i2c_block_data(ext_i2c_dev, 0xff, 1, buf1);
	return i2c_master_recv(ext_i2c_dev,buf1,1);
}

//-------------------------

void btnx8_init(void) {
	i2c_master_send(ext_i2c_dev, &b1, 1); 
}

unsigned char btnx8_read(void) {
	i2c_master_recv(ext_i2c_dev, &b1, 1);
	b1 = ~ b1;
	return b1;
}
