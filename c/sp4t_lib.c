#include "xil_printf.h"
#include "xgpiops.h"
#include "gpio_controller.h"

int sp4t_set_line_freq(XGpioPs InstancePtr, int freq_val){
	if(freq_val < 100 || freq_val > 6000){
		xil_printf("SP4T frequency is invalid.\r\n");
		return -1;
	}

	//int value_holder;
	//value_holder = XGpioPs_ReadPin(&InstancePtr, XGPIO_DATA_OFFSET+52);
	//value_holder = value_holder & 0xFFFFFF03;
	if((freq_val > 99) & (freq_val < 751)){
		//value_holder = value_holder | (sp4t_freq_100_750 << 2);
		gpio_controller_set(InstancePtr, 2, 0);
		gpio_controller_set(InstancePtr, 3, 1);
		gpio_controller_set(InstancePtr, 4, 0);
		gpio_controller_set(InstancePtr, 5, 1);
		gpio_controller_set(InstancePtr, 6, 1);
		gpio_controller_set(InstancePtr, 7, 0);
		xil_printf("SP4T 1 is active \r\n");
	}
	else if((freq_val > 749) & (freq_val < 1500)){
		//value_holder = value_holder | (sp4t_freq_750_1499 << 2);
		gpio_controller_set(InstancePtr, 2, 1);
		gpio_controller_set(InstancePtr, 3, 1);
		gpio_controller_set(InstancePtr, 4, 0);
		gpio_controller_set(InstancePtr, 5, 0);
		gpio_controller_set(InstancePtr, 6, 1);
		gpio_controller_set(InstancePtr, 7, 0);
		xil_printf("SP4T 2 is active \r\n");
	}
	else if((freq_val > 1499) & (freq_val < 3000)){
		//value_holder = value_holder | (sp4t_freq_1500_2999 << 2);
		gpio_controller_set(InstancePtr, 2, 0);
		gpio_controller_set(InstancePtr, 3, 0);
		gpio_controller_set(InstancePtr, 4, 1);
		gpio_controller_set(InstancePtr, 5, 1);
		gpio_controller_set(InstancePtr, 6, 0);
		gpio_controller_set(InstancePtr, 7, 0);
		xil_printf("SP4T 3 is active \r\n");
	}
	else if(freq_val > 2999 ){
		//value_holder = value_holder | (sp4t_freq_3000_6000 << 2);
		gpio_controller_set(InstancePtr, 2, 1);
		gpio_controller_set(InstancePtr, 3, 0);
		gpio_controller_set(InstancePtr, 4, 0);
		gpio_controller_set(InstancePtr, 5, 0);
		gpio_controller_set(InstancePtr, 6, 0);
		gpio_controller_set(InstancePtr, 7, 1);
		xil_printf("SP4T 4 is active \r\n");
	}
	else{
		gpio_controller_set(InstancePtr, 2, 0);
		gpio_controller_set(InstancePtr, 3, 1);
		gpio_controller_set(InstancePtr, 4, 1);
		gpio_controller_set(InstancePtr, 5, 0);
		gpio_controller_set(InstancePtr, 6, 1);
		gpio_controller_set(InstancePtr, 7, 1);
		//value_holder = value_holder | (sp4t_freq_off << 2);
	}
	// XGpio_WriteReg(gpio_controller_baseaddr, XGPIO_DATA_OFFSET,value_holder);
	return 0;
}
