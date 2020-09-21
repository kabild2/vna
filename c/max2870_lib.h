#define MAX2870_0_LE_GPIO_NO	0

int max2870_spi_write(XSpiPs SpiInstance, int value);
int max2870_init(XSpiPs SpiInstance, XGpioPs InstancePtr);
int max2870_1mhz_step_init(XSpiPs SpiInstance);
int max2870_1mhz_step_set_freq(XSpiPs SpiInstance, int freq_mhz);
int max2870_read_lock_detect(XGpioPs InstancePtr);
int max2870_reg6_read(XSpiPs SpiInstance);
