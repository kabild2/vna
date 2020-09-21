# ----------------------------------------------------------------------------
# JA Pmod - Bank 13 
# ---------------------------------------------------------------------------- 
set_property PACKAGE_PIN Y11  [get_ports {spi_ss}];         # "JA1"           H1-9  LE
set_property PACKAGE_PIN AA8  [get_ports {JA10}];           # "JA10"          
set_property PACKAGE_PIN AA11 [get_ports {gpio_out[0]}];    # "JA2"           H1-3  RF_EN
set_property PACKAGE_PIN Y10  [get_ports {spi_mosi}];       # "JA3"           H1-7  LO1_DATA 
set_property PACKAGE_PIN AA9  [get_ports {spi_sclk}];       # "JA4"           H1-5  LO1_CLOCK
set_property PACKAGE_PIN AB11 [get_ports {gpio_in[0]}];     # "JA7"           H1-2  LD_OUT     
set_property PACKAGE_PIN AB10 [get_ports {gpio_out[1]}];    # "JA8"           H1-11 CE       
set_property PACKAGE_PIN AB9  [get_ports {spi_miso}];       # "JA9"           H1-1  MUX_OUT  
                                                            

# ----------------------------------------------------------------------------
# JB Pmod - Bank 13
# ---------------------------------------------------------------------------- 
set_property PACKAGE_PIN W12 [get_ports {gpio_out[2]}];     # "JB1"         # "JB1"  H2-1  S4_1_V1 
set_property PACKAGE_PIN W11 [get_ports {gpio_out[3]}];     # "JB2"         # "JB2"  H2-3  S4_1_V2
set_property PACKAGE_PIN V10 [get_ports {gpio_out[4]}];     # "JB3"         # "JB3"  H2-5  S4_1_V3
set_property PACKAGE_PIN W8 [get_ports  {gpio_out[5]}];     # "JB4"         # "JB4"  H2-10 S4_2_V1 
set_property PACKAGE_PIN V12 [get_ports {gpio_out[6]}];     # "JB7"         # "JB7"  H2-9  S4_2_V2
set_property PACKAGE_PIN W10 [get_ports {gpio_out[7]}];     # "JB8"         # "JB8"  H2-7  S4_2_V3
set_property PACKAGE_PIN V9 [get_ports  {gpio_out[15]}];    # "JB9"         # "JB9"  H2-11 LS
set_property PACKAGE_PIN V8 [get_ports  {gpio_out[16]}];    # "JB10"        # "JB10" H2-12 CTRL

# ----------------------------------------------------------------------------
# JC Pmod - Bank 13
# ---------------------------------------------------------------------------- 
set_property PACKAGE_PIN AB6 [get_ports {gpio_out[8]}];     # "JC1_N"        #  JC1_N     H3-10 C0.25 
set_property PACKAGE_PIN AB7 [get_ports {gpio_out[9]}];     # "JC1_P"        # "JC1_P"   H3-1  C0.5
set_property PACKAGE_PIN AA4 [get_ports {gpio_out[10]}];    # "JC2_N"        # "JC2_N"   H3-8  C1
set_property PACKAGE_PIN Y4  [get_ports {gpio_out[11]}];    # "JC2_P"        # "JC2_P"   H3-3  C2
set_property PACKAGE_PIN T6  [get_ports {gpio_out[12]}];    # "JC3_N"        # "JC3_N"   H3-2  C4
set_property PACKAGE_PIN R6  [get_ports {gpio_out[13]}];    # "JC3_P"        # "JC3_P"   H3-6  C8
set_property PACKAGE_PIN U4  [get_ports {gpio_out[14]}];    # "JC4_N"        # "JC4_N"   H3-4  C16
#set_property PACKAGE_PIN T4  [get_ports {JC4_P}];  # "JC4_P"   # "JC4_N"   H3-4  C16

# ----------------------------------------------------------------------------
# JD Pmod - Bank 13
# ---------------------------------------------------------------------------- 
#set_property PACKAGE_PIN W7 [get_ports {JD1_N}];  # "JD1_N"
#set_property PACKAGE_PIN V7 [get_ports {JD1_P}];  # "JD1_P"
set_property PACKAGE_PIN V4 [get_ports {UART_1_0_txd}];  # "JD2_N"
set_property PACKAGE_PIN V5 [get_ports {UART_1_0_rxd}];  # "JD2_P"
#set_property PACKAGE_PIN W5 [get_ports {JD3_N}];  # "JD3_N"
#set_property PACKAGE_PIN W6 [get_ports {JD3_P}];  # "JD3_P"
#set_property PACKAGE_PIN U5 [get_ports {JD4_N}];  # "JD4_N"
#set_property PACKAGE_PIN U6 [get_ports {JD4_P}];  # "JD4_P"

# ----------------------------------------------------------------------------
# IOSTANDARD Constraints
#
# Note that these IOSTANDARD constraints are applied to all IOs currently
# assigned within an I/O bank.  If these IOSTANDARD constraints are 
# evaluated prior to other PACKAGE_PIN constraints being applied, then 
# the IOSTANDARD specified will likely not be applied properly to those 
# pins.  Therefore, bank wide IOSTANDARD constraints should be placed 
# within the XDC file in a location that is evaluated AFTER all 
# PACKAGE_PIN constraints within the target bank have been evaluated.
#
# Un-comment one or more of the following IOSTANDARD constraints according to
# the bank pin assignments that are required within a design.
# ---------------------------------------------------------------------------- 

# Note that the bank voltage for IO Bank 33 is fixed to 3.3V on ZedBoard. 
set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 33]];

# Set the bank voltage for IO Bank 34 to 1.8V by default.
# set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 34]];
# set_property IOSTANDARD LVCMOS25 [get_ports -of_objects [get_iobanks 34]];
set_property IOSTANDARD LVCMOS18 [get_ports -of_objects [get_iobanks 34]];

# Set the bank voltage for IO Bank 35 to 1.8V by default.
# set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 35]];
# set_property IOSTANDARD LVCMOS25 [get_ports -of_objects [get_iobanks 35]];
set_property IOSTANDARD LVCMOS18 [get_ports -of_objects [get_iobanks 35]];

# Note that the bank voltage for IO Bank 13 is fixed to 3.3V on ZedBoard. 
set_property IOSTANDARD LVCMOS33 [get_ports -of_objects [get_iobanks 13]];