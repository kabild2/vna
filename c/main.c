/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpiops.h"
#include "xspips.h"
#include "max2870_lib.h"
#include "sp4t_lib.h"
#include "spdt_lib.h"
#include "attenuator_lib.h"
#include "sleep.h"


int main()
{
    init_platform();

    print("Program start\n\r");

    int Status;
    int i;
    int value_holder;

    XGpioPs Gpio;
    XGpioPs_Config *ConfigPtr;

    ConfigPtr = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
	Status = XGpioPs_CfgInitialize(&Gpio, ConfigPtr, ConfigPtr->BaseAddr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	for(i=0;i<17;i++){
		XGpioPs_SetDirectionPin(&Gpio, 52+i, 1);
		XGpioPs_SetOutputEnablePin(&Gpio, 52+i, 1);
	}

	XGpioPs_SetDirectionPin(&Gpio, 69, 0x0);

	XSpiPs SpiInstance;
	XSpiPs_Config *SpiConfig;

	SpiConfig = XSpiPs_LookupConfig(XPAR_XSPIPS_0_DEVICE_ID);
	if (NULL == SpiConfig) {
		return XST_FAILURE;
	}

	Status = XSpiPs_CfgInitialize(&SpiInstance, SpiConfig, SpiConfig->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to check hardware build
	 */
	Status = XSpiPs_SelfTest(&SpiInstance);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XSpiPs_SetOptions(&SpiInstance, XSPIPS_MASTER_OPTION | XSPIPS_FORCE_SSELECT_OPTION);

	XSpiPs_SetClkPrescaler(&SpiInstance, XSPIPS_CLK_PRESCALE_64);

	XSpiPs_SetSlaveSelect(&SpiInstance, 0x0);

//	while(1){
//		gpio_controller_set(Gpio, 0, 1);
//		gpio_controller_set(Gpio, 1, 1);
//		usleep(1);
//		gpio_controller_set(Gpio, 0, 0);
//		gpio_controller_set(Gpio, 1, 0);
//		usleep(1);
//	}

	max2870_init(SpiInstance, Gpio);
	usleep(1);
	max2870_1mhz_step_init(SpiInstance);
	usleep(1);
	//max2870_1mhz_step_set_freq(SpiInstance, 400);
	usleep(1);
	sp4t_set_line_freq(Gpio, 300);
	usleep(1);
	set_attenuator_level(Gpio,1);
	usleep(1);


	while(max2870_read_lock_detect(Gpio) == 0){
		xil_printf("Waiting for lock detect.\r\n");
		usleep(100000);
	}
		//value_holder = max2870_reg6_read(SpiInstance);
		//xil_printf("MAX2870 Reg 6 Value = %X", value_holder);

	while(1);

    cleanup_platform();
    return 0;
}
