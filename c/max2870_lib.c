#include "xil_io.h"
#include "sleep.h"
#include "xgpiops.h"
#include "xil_cache.h"
#include <math.h>
#include <stdio.h>
#include "xspips.h"
#include "gpio_controller.h"


//#define REG0_DEFAULT_1MHZ_STEP	0x00400000
//#define REG1_DEFAULT_1MHZ_STEP	0x200303E9
//#define REG2_DEFAULT_1MHZ_STEP	0x01005E42
//#define REG3_DEFAULT_1MHZ_STEP	0x00000133
//#define REG4_DEFAULT_1MHZ_STEP	0x61DF423C
//#define REG5_DEFAULT_1MHZ_STEP	0x01400005
//#define REG6_DEFAULT_1MHZ_STEP  0x00000006


#define REG0_DEFAULT_1MHZ_STEP	0x00400000
#define REG1_DEFAULT_1MHZ_STEP	0x200303E9
#define REG2_DEFAULT_1MHZ_STEP	0x21005E42
#define REG3_DEFAULT_1MHZ_STEP	0x00000133
#define REG4_DEFAULT_1MHZ_STEP	0x61DF42FC
#define REG5_DEFAULT_1MHZ_STEP	0x01400005
#define REG6_DEFAULT_1MHZ_STEP  0x00000006


//#define REG0_DEFAULT_1MHZ_STEP	0x00400000
//#define REG1_DEFAULT_1MHZ_STEP	0x600303E9
//#define REG2_DEFAULT_1MHZ_STEP	0x41005E42
//#define REG3_DEFAULT_1MHZ_STEP	0x00008133
//#define REG4_DEFAULT_1MHZ_STEP	0x61CF43FC
//#define REG5_DEFAULT_1MHZ_STEP	0x01400005
//#define REG6_DEFAULT_1MHZ_STEP  0x00000006

int max2870_spi_write(XSpiPs SpiInstance, int value){

	u8 sendBuffer[4];
	sendBuffer[0] = (value >> 24) & 0xFF;
	sendBuffer[1] = (value >> 16) & 0xFF;
	sendBuffer[2] = (value >> 8) & 0xFF;
	sendBuffer[3] = value & 0xFF;
	u8 recvBuffer[4];
	XSpiPs_PolledTransfer(&SpiInstance, sendBuffer, recvBuffer,	4);
	int return_value;
	return_value = recvBuffer[0] | (int)recvBuffer[1] << 8 | (int)recvBuffer[2] << 16 | (int)recvBuffer[3] << 24; // Ters çevrilebilir

	//axi_spi_write(max_2870_base_address, value);
//	gpio_controller_set(XPAR_GPIO_0_BASEADDR, le_gpio_no, 1);
//	usleep(1);
//	gpio_controller_set(XPAR_GPIO_0_BASEADDR, le_gpio_no, 0);
	return return_value;
}

int max2870_init(XSpiPs SpiInstance, XGpioPs InstancePtr){
	//int value_holder;
	//value_holder = XGpio_ReadReg(gpio_controller_baseaddr, XGPIO_DATA_OFFSET);
	//usleep(10);
	//value_holder = value_holder | 0x00000003;

	usleep(10);
	//XGpio_WriteReg(gpio_controller_baseaddr, XGPIO_DATA_OFFSET, value_holder);
	gpio_controller_set(InstancePtr, 0, 1);
	gpio_controller_set(InstancePtr, 1, 1);
	usleep(10);
	max2870_spi_write(SpiInstance, 0x5);
	//usleep(10); BURDA BEKLEME 20MS
	usleep(20000);

	max2870_spi_write(SpiInstance, 0x4);
	usleep(10);
	max2870_spi_write(SpiInstance, 0x3);
	usleep(10);
	max2870_spi_write(SpiInstance, 0x2);
	usleep(10);
	max2870_spi_write(SpiInstance, 0x1);
	usleep(10);
	max2870_spi_write(SpiInstance, 0x0);
	usleep(10);
	max2870_spi_write(SpiInstance, 0x5);
	usleep(10);
	max2870_spi_write(SpiInstance, 0x4);
	usleep(10);
	max2870_spi_write(SpiInstance, 0x3);
	usleep(10);
	max2870_spi_write(SpiInstance, 0x2);
	usleep(10);
	max2870_spi_write(SpiInstance, 0x1);
	usleep(10);
	max2870_spi_write(SpiInstance, 0x0);
	usleep(100);
	max2870_spi_write(SpiInstance, 0x124);
	usleep(10);
	return 0;
}

int max2870_1mhz_step_init(XSpiPs SpiInstance){
	max2870_spi_write(SpiInstance, REG5_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG4_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG3_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG2_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG1_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG0_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG5_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG4_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG3_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG2_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG1_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG0_DEFAULT_1MHZ_STEP);
	usleep(10);
	//max2870_spi_write(SpiInstance, REG6_DEFAULT_1MHZ_STEP);
	return 0;
}

int max2870_1mhz_step_set_freq(XSpiPs SpiInstance, int freq_mhz){
	int n_value;
	int fracn_value;
	int diva_value;
	int reg0_calculated_value;
	int reg4_calculated_value;
	if(freq_mhz < 100 || freq_mhz > 6000){
		xil_printf("Frequency out of bounds.\r\n");
		return -1;
	}
	else if(freq_mhz >= 100 && freq_mhz < 177){
		diva_value 	= 5;
		n_value 	= 120 + (int)floor((freq_mhz*32-3000)/25);
		fracn_value = 5 * ((freq_mhz*32-3000)%25);

	}
	else if(freq_mhz > 177 && freq_mhz < 375){
		diva_value 	= 4;
		n_value	 	= 120 + (int)floor((freq_mhz*16-3000)/25);
		fracn_value = 5 * ((freq_mhz*16-3000)%25);
	}
	else if(freq_mhz >= 375 && freq_mhz < 750){
		diva_value  = 3;
		n_value  	= 120 + (int)floor((freq_mhz*8-3000)/25);
		fracn_value = 5 * ((freq_mhz*8-3000)%25);
	}
	else if(freq_mhz >= 750 && freq_mhz < 1500){
		diva_value = 2;
		n_value 	= 120 + (int)floor((freq_mhz*4-3000)/25);
		fracn_value = 5 * ((freq_mhz*4-3000) % 25);
	}
	else if(freq_mhz >= 1500 && freq_mhz < 3000){
		diva_value = 1;
		n_value 	= 120 + (int)floor((freq_mhz*2-3000)/25);
		fracn_value = 5 * ((freq_mhz*2-3000) % 	25);
	}
	else if(freq_mhz >= 3000 && freq_mhz < 6001){
		diva_value = 0;
		n_value 	= 120 + (int)floor((freq_mhz*1-3000)/25);
		fracn_value = 5 * ((freq_mhz*1-3000)%25);
	}

	reg0_calculated_value = REG0_DEFAULT_1MHZ_STEP & 0x80000000;
	reg0_calculated_value = reg0_calculated_value | (n_value << 15);
	reg0_calculated_value = reg0_calculated_value | (fracn_value << 3);

	reg4_calculated_value = REG4_DEFAULT_1MHZ_STEP & 0xFF8FFFFF;
	reg4_calculated_value = reg4_calculated_value | (diva_value << 20);

	printf(" %d, f = %d\n", n_value , fracn_value );

	max2870_spi_write(SpiInstance, REG5_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, reg4_calculated_value);
	usleep(10);
	max2870_spi_write(SpiInstance, REG3_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG2_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG1_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, reg0_calculated_value);
	usleep(10);
	max2870_spi_write(SpiInstance, REG5_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, reg4_calculated_value);
	usleep(10);
	max2870_spi_write(SpiInstance, REG3_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG2_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, REG1_DEFAULT_1MHZ_STEP);
	usleep(10);
	max2870_spi_write(SpiInstance, reg0_calculated_value);
	usleep(10);
	return 0;
}

int max2870_read_lock_detect(XGpioPs InstancePtr){
	int value_holder;
	Xil_DCacheFlush();
	//value_holder = XGpio_ReadReg(gpio_controller_baseaddr, XGPIO_DATA_OFFSET);
	value_holder = gpio_controller_get(InstancePtr, 17);
	xil_printf("Lock detect pin is %d.\r\n", (value_holder & 0x1));
	return (value_holder & 0x1);
}


int max2870_reg6_read(XSpiPs SpiInstance){

	int value_holder;

	int reg5_calculated_value;
	int reg2_calculated_value;

	reg5_calculated_value = REG5_DEFAULT_1MHZ_STEP & 0xFFFBFFFF;
	reg5_calculated_value = reg5_calculated_value | (1 << 18);

	reg2_calculated_value = REG2_DEFAULT_1MHZ_STEP & 0xEFFFFFFF;
	reg2_calculated_value = reg2_calculated_value | (1 << 28);


	max2870_spi_write(SpiInstance, reg5_calculated_value);
	max2870_spi_write(SpiInstance, reg2_calculated_value);
	max2870_spi_write(SpiInstance, REG6_DEFAULT_1MHZ_STEP);


	XSpiPs_SetSlaveSelect(&SpiInstance, 0x1);
	value_holder = max2870_spi_write(SpiInstance, 0x00000000);
	XSpiPs_SetSlaveSelect(&SpiInstance, 0x0);

	max2870_spi_write(SpiInstance, REG5_DEFAULT_1MHZ_STEP);
	max2870_spi_write(SpiInstance, REG2_DEFAULT_1MHZ_STEP);


	return value_holder;
}












