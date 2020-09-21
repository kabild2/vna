#define sp4t_freq_off			0x36
#define sp4t_freq_100_750		0x1A
#define sp4t_freq_750_1499		0x13
#define sp4t_freq_1500_2999		0xC
#define sp4t_freq_3000_6000		0x21

int sp4t_set_line_freq(XGpioPs InstancePtr, int freq_val);
