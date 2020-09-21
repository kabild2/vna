#include "xil_printf.h"
#include "xgpiops.h"
#include "gpio_controller.h"
#include <stdio.h>


int set_attenuator_level(XGpioPs InstancePtr, float attenuator_level){
	float attenuator_set_level = 0;
	if(attenuator_level > 31.75 || attenuator_level < 0){
		xil_printf("Attenuator value out of bounds.\r\n");
	}
	if(attenuator_level >= 16){
		attenuator_level = attenuator_level - 16;
		gpio_controller_set(InstancePtr, 14, 1);
		attenuator_set_level = attenuator_set_level + 16;
	}
	else{
		gpio_controller_set(InstancePtr, 14, 0);
	}
	if(attenuator_level >= 8){
		attenuator_level = attenuator_level - 8;
		gpio_controller_set(InstancePtr, 13, 1);
		attenuator_set_level = attenuator_set_level + 8;
	}
	else{
		gpio_controller_set(InstancePtr, 13, 0);
	}
	if(attenuator_level >= 4){
		attenuator_level = attenuator_level - 4;
		gpio_controller_set(InstancePtr, 12, 1);
		attenuator_set_level = attenuator_set_level + 4;
	}
	else{
		gpio_controller_set(InstancePtr, 12, 0);
	}
	if(attenuator_level >= 2){
		attenuator_level = attenuator_level - 2;
		gpio_controller_set(InstancePtr, 11, 1);
		attenuator_set_level = attenuator_set_level + 2;
	}
	else{
		gpio_controller_set(InstancePtr, 11, 0);
	}
	if(attenuator_level >= 1){
		attenuator_level = attenuator_level - 1;
		gpio_controller_set(InstancePtr, 10, 1);
		attenuator_set_level = attenuator_set_level + 1;
	}
	else{
		gpio_controller_set(InstancePtr, 10, 0);
	}
	if(attenuator_level >= 0.5){
		attenuator_level = attenuator_level - 0.5;
		gpio_controller_set(InstancePtr, 9, 1);
		attenuator_set_level = attenuator_set_level + 0.5;
	}
	else{
		gpio_controller_set(InstancePtr, 9, 0);
	}
	if(attenuator_level >= 0.25){
		attenuator_level = attenuator_level - 0.25;
		gpio_controller_set(InstancePtr, 8, 1);
		attenuator_set_level = attenuator_set_level + 0.25;
	}
	else{
		gpio_controller_set(InstancePtr, 8, 0);
	}
	printf(" Attenuator level is %f \n", attenuator_set_level );

	return 0;
}
