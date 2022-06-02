#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/string.h>
#include "io_i2c.h"

//mmm
#define I2C_BUS_AVAILABLE   (         0 )		// I2C Bus that we have created
#define SLAVE_DEVICE_NAME   (  " BTNx8")		// Device and Driver Name
#define LCDI2C_SLAVE_ADDR  (       0x20 )		// LCD Slave Address
//----



struct i2c_client  *ext_i2c_dev = NULL;;	// I2C device Structure

static struct i2c_adapter *ext_i2c_adapter     = NULL;  // I2C Adapter Structure

static int i2c_dev_probe(struct i2c_client *client,
                         const struct i2c_device_id *id)
{
    pr_info("I2C dev Probed!!!\n");
    
    return 0;
}

static int i2c_dev_remove(struct i2c_client *client)
{   
    
    pr_info("I2C dev Removed!!!\n");
    return 0;
}


static struct i2c_board_info lcd_i2c_board_info = {
        I2C_BOARD_INFO(SLAVE_DEVICE_NAME, LCDI2C_SLAVE_ADDR)
    };
static const struct i2c_device_id I2c_dev_id[] = {
        { SLAVE_DEVICE_NAME, 0 },
        { }
};
MODULE_DEVICE_TABLE(i2c, I2c_dev_id);
static struct i2c_driver ext_oled_driver = {
        .driver = {
            .name   = SLAVE_DEVICE_NAME,
            .owner  = THIS_MODULE,
        },
        .probe          = i2c_dev_probe,
        .remove         = i2c_dev_remove,
        .id_table       = I2c_dev_id,
};

int i2c_dev_init(void){

	ext_i2c_adapter     = i2c_get_adapter(I2C_BUS_AVAILABLE);
	if( ext_i2c_adapter != NULL ){
		ext_i2c_dev = i2c_new_device(ext_i2c_adapter, &lcd_i2c_board_info);
        
        	if( ext_i2c_dev != NULL )
        	{
            		i2c_add_driver(&ext_oled_driver);
        	} else {
			printk("err, ext_i2c_dev = null\n");
			return -ENOMEM;
		}
        	i2c_put_adapter(ext_i2c_adapter);
	} else {
		printk("err! ext_i2c_adapter = NULL\n");
		return -ENOMEM;
	}
	printk("%s init ok!\n",SLAVE_DEVICE_NAME);
	return 0;
}
void i2c_dev_exit(void){
	i2c_unregister_device(ext_i2c_dev);
	i2c_del_driver(&ext_oled_driver);
	printk("%s exit ok\n",SLAVE_DEVICE_NAME);
}
