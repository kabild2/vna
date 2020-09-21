#include "xil_io.h"
#include "xgpiops.h"

int gpio_controller_set(XGpioPs InstancePtr, int gpio_no, int value){
	XGpioPs_WritePin(&InstancePtr, gpio_no+54, value);

//	int value_holder;
//	value_holder = XGpio_ReadReg(gpio_controller_baseaddr, XGPIO_DATA_OFFSET);
//	if( (value_holder & (1 << gpio_no) >> gpio_no) == 0 ){
//		value_holder = (value_holder | (value << gpio_no));
//	}
//	else{
//		value_holder = (value_holder & (value << gpio_no));
//	}
//	XGpio_WriteReg(gpio_controller_baseaddr, XGPIO_DATA_OFFSET, value_holder);
	return 0;
}

int gpio_controller_get(XGpioPs InstancePtr, int gpio_no){
	int value_read;
	value_read = XGpioPs_ReadPin(&InstancePtr, gpio_no+54);
	return value_read;
}
