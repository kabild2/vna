#include "xil_printf.h"
#include "xgpiops.h"
#include "gpio_controller.h"

int spdt_purpose(XGpioPs InstancePtr, int purpose_value){
	if(purpose_value!=1 || purpose_value!=2 ){
		xil_printf("SPDT purpose is invalid.\r\n");
		return -1;
	}

	//int value_holder;
	//value_holder = XGpio_ReadReg(gpio_controller_baseaddr, XGPIO_DATA_OFFSET);
	//value_holder = value_holder & 0xFFFE7FFF;

	if(purpose_value==1){
		//value_holder = value_holder | (spdt_power_detect << 15);
		gpio_controller_set(InstancePtr, 15, 1);
		gpio_controller_set(InstancePtr, 16, 0);
		xil_printf("Incident power detect mode is active \r\n");
	}
	else if(purpose_value==2){
		//value_holder = value_holder | (spdt_power_measure << 15);
		gpio_controller_set(InstancePtr, 15, 1);
		gpio_controller_set(InstancePtr, 16, 1);
		xil_printf("Reflected power measure mode is active \r\n");
	}

	else{
		gpio_controller_set(InstancePtr, 15, 0);
		gpio_controller_set(InstancePtr, 16, 0);
		//value_holder = value_holder | (sp4t_freq_off << 15);
	}

	//XGpio_WriteReg(gpio_controller_baseaddr, XGPIO_DATA_OFFSET,value_holder);

	return 0;
}
