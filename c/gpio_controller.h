#define gpio_direction_input 	0xFFFFFFFF
#define gpio_direction_output 	0x00000000

//int gpio_controller_initialize(int gpio_controller_baseaddr, int direction);
int gpio_controller_set(XGpioPs InstancePtr, int gpio_no, int value);
int gpio_controller_get(XGpioPs InstancePtr, int gpio_no);
