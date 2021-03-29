#ifndef OV9653_REGS_H
#define OV9653_REGS_H

/* 
* 
* 
* 
* 
* 
* 
* 
*         
*         
*         
*         
*                 
* 
*/

const uint8_t OV9653_VGA[][2] PROGMEM =
{
    {   1, 0x60},     // Size of byte, Address (ID) 
    { 640/16,  480/16}, // Size X, Size Y
    {0b00000010, 0b00000100},// Reset_Enable_N, 7|6|5|4|3|Vsync Invert|Hsync Invert|0

    {0x12, 0x40},    // COM7       set output to VGA mode
    {0x11, 0x81},    // CLKRC      set the system clock division
    {0x6b, 0x0a},    // DBLV       band gap reference adjustment
    {0x6a, 0x41},    // 		   LSB of Banding Filter (effective only when COM11[0] is high)
    {0x3b, 0x09},    // COM11      use half frame and manual banding filter mode
    {0x13, 0xe0},    // COM8       enable fast AGC/AEC, enable AEC, and enable Banding filter
    {0x01, 0x80},    // BLUE	   Blue channel gain setting, default 0x80
    {0x02, 0x80},    // RED		   Red channel gain setting, default 0x80
    {0x00, 0x00},    // GAIN	   AGC, range 0x00 to 0xFF
    {0x10, 0x00},    // AECH       exposure value set default 0x40
    {0x13, 0xe5},    // COM8       now enable AGC/AEC
    {0x39, 0x43},    // OPON       ???
    {0x38, 0x12},    // ACOM       ???
    {0x37, 0x00},    // ADC		   ???
    {0x35, 0x91},    // RSVD	   ???
    {0x0e, 0x20},    // COM5       ???
    {0x1e, 0x30},    // MVFP       Mirror/VFlip enable, mirror and vflip enable for self-portrait (hardware OV9650_BO)
    {0x04, 0x00},    // COM1       no line skip option
    {0x0c, 0x00},    // COM3       set to default
    {0x0d, 0x00},    // COM4	   default to 0x00
	
    // window start and stop for output size control
    // HSTOP[REG18h] is the high 8 bit of H STOP (low 3 bits are at HREF[5:3])
    // Because HREF[5:3] = 0b100, HSTOP = 0x5A*2^3 + 4 = 0x2D0
    // HSTART[REG17h] is the high 8-bit of H START (low 3 bits are at HREF[2:0])
    // Because HREF[2:0] = 0b100, HSTART = 0x32*2^3 + 4 = 0x190
    // Therefore HSTOP-HSTART = (0x2D0+4)-(0x190+4) = 0x140 (320 dec.)
    {0x32, 0xA4},// HREF       window control
    {0x18, 0x5A},
    {0x17, 0x32},

    // VSTRT      window control
    // VREF[REG03h] contains the start and end low 3 bits for VSTOP and VSTRT
    // VSTRT[REG19h] = 0x31*2^3 = 0x188
    // VSTOP[REG1Ah] = 0x4F*2^3 = 0x278
    // Therefore VSTOP - VSTRT = (0x278+2)-(0x188+2) = 0xF0 (240 dec.)
    {0x03, 0x12},
    {0x19, 0x31},    
    {0x1a, 0x4F},
    {0x14, 0x1a},    // COM9       automatic gain control ceilings
    {0x15, 0x10},    // COM10      set up pclk, vsync and href signals
    {0x3f, 0xa6},    // EDGE	   what edge enhancement ???
    {0x41, 0x02},    // COM16	   Color matrix coefficient double option enable ???
    {0x42, 0xc1},    // COM17	   edge enhancement option, tri-state output etc
    {0x1b, 0x00},    // PSHFT      set pclk delay from href
    {0x16, 0x06},    // RSVD	   another reserved register!
    {0x33, 0xe2},    // CHLF       array current control
    {0x34, 0xbf},    // ARBLM      array reference control
    {0x96, 0x04},    // RSVD	   again, reserved register
    {0x3a, 0x0c},    // TSLB	   line buffer test option for UV output and sequence setting
    {0x8e, 0x00},    // COM24	   Reserved register
    {0x3c, 0x77},    // COM12      href options
    {0x8b, 0x06},
    {0x94, 0x88},
    {0x95, 0x88},
    {0x40, 0xc1},
    {0x29, 0x3f},
    {0x0f, 0x42},
    {0x3d, 0x92},
    {0x69, 0x40},    // Manual Banding Filter MSB
    {0x5c, 0xb9},    // REG[0x59-0x61] all RSVD
    {0x5d, 0x96},	 
    {0x5e, 0x10},
    {0x59, 0xc0},
    {0x5a, 0xaf},
    {0x5f, 0xe0},
    {0x60, 0x8c},
    {0x61, 0x20},
    {0x5b, 0x55},    // REG[0x59-0x61] all RSVD
    {0x43, 0xf0},    // REG[0x43-0x4E] all RSVD
    {0x44, 0x10},
    {0x45, 0x68},
    {0x46, 0x96},
    {0x47, 0x60},
    {0x48, 0x80},
    {0xa5, 0xd9},    // RSVD
    {0xa4, 0x74},    // RSVD
    {0x8d, 0x02},    // color bar test mode disable, digital AWB enable
    {0x13, 0xe7},    // AGC, AWB, AEC all enabled here
    {0x4f, 0x3a},    // REG[4F-58] are Matrix coefficients
    {0x50, 0x3d},
    {0x51, 0x03},
    {0x52, 0x12},
    {0x53, 0x26},
    {0x54, 0x38},
    {0x55, 0x40},
    {0x56, 0x40},
    {0x57, 0x40},
    {0x58, 0x0d},
    {0x8c, 0x23},    // De-noise enable, white-pixel erase enable
    {0x3e, 0x02},
    {0xa9, 0xb8},    // REG[A8-AA] all RSVD
    {0xaa, 0x92},
    {0xab, 0x0a},
    {0x8f, 0xdf},    // Digital BLC offset sign???
    {0x90, 0x00},    // Digital BLC B channel offset value set default
    {0x91, 0x00},    // Digital BLC R channel offset value set default
    {0x9f, 0x00},    // Digital BLC Gb channel offset value set default
    {0xa0, 0x00},    // Digital BLC Gr channel offset value set default
    {0x24, 0x98},    // AEW stable operating region upper limit
    {0x25, 0x88},    // AEW stable operating region lower limit
    {0x26, 0xd3},    // AGC/AEC fast mode operating region
    {0x2a, 0x00},    // Horizontal dummy pixel insert MSB
    {0x2b, 0x00},    // Horizontal dummy insert LSB
    {0x2d, 0x00},    // Vertical LSB of dummy lines 
    {0x6c, 0x40},    // REG[6C-7B] are Gamma Curve setup GSP
    {0x6d, 0x30},	 
    {0x6e, 0x4b},
    {0x6f, 0x60},
    {0x70, 0x70},
    {0x71, 0x70},
    {0x72, 0x70},
    {0x73, 0x70},
    {0x74, 0x60},
    {0x75, 0x60},
    {0x76, 0x50},
    {0x77, 0x48},
    {0x78, 0x3a},
    {0x79, 0x2e},
    {0x7a, 0x28},
    {0x7b, 0x22},
    {0x7c, 0x04},    // REG[7C-8A] are Gamma Curve setup GST
    {0x7d, 0x07},
    {0x7e, 0x10},
    {0x7f, 0x28},
    {0x80, 0x36},
    {0x81, 0x44},
    {0x82, 0x52},
    {0x83, 0x60},
    {0x84, 0x6c},
    {0x85, 0x78},
    {0x86, 0x8c},
    {0x87, 0x9e},
    {0x88, 0xbb},
    {0x89, 0xd2},
    {0x8a, 0xe6},

    { 0xff,0xff},
};


const uint8_t OV9653_QVGA[][2] PROGMEM =
{
    {   1, 0x60},     // Size of byte, Address (ID) 
    { 320/16,  240/16}, // Size X, Size Y
    {0b00000010, 0b00000100},// Reset_Enable_N, 7|6|5|4|3|Vsync Invert|Hsync Invert|0

    {0x12, 0x10},    // COM7       set output to QVGA mode
    {0x11, 0x81},    // CLKRC      set the system clock division
    {0x6b, 0x0a},    // DBLV       band gap reference adjustment
    {0x6a, 0x41},    // 		   LSB of Banding Filter (effective only when COM11[0] is high)
    {0x3b, 0x09},    // COM11      use half frame and manual banding filter mode
    {0x13, 0xe0},    // COM8       enable fast AGC/AEC, enable AEC, and enable Banding filter
    {0x01, 0x80},    // BLUE	   Blue channel gain setting, default 0x80
    {0x02, 0x80},    // RED		   Red channel gain setting, default 0x80
    {0x00, 0x00},    // GAIN	   AGC, range 0x00 to 0xFF
    {0x10, 0x00},    // AECH       exposure value set default 0x40
    {0x13, 0xe5},    // COM8       now enable AGC/AEC
    {0x39, 0x43},    // OPON       ???
    {0x38, 0x12},    // ACOM       ???
    {0x37, 0x00},    // ADC		   ???
    {0x35, 0x91},    // RSVD	   ???
    {0x0e, 0x20},    // COM5       ???
    {0x1e, 0x30},    // MVFP       Mirror/VFlip enable, mirror and vflip enable for self-portrait (hardware OV9650_BO)
    {0x04, 0x00},    // COM1       no line skip option
    {0x0c, 0x00},    // COM3       set to default
    {0x0d, 0x00},    // COM4	   default to 0x00
	
    // window start and stop for output size control
    // HSTOP[REG18h] is the high 8 bit of H STOP (low 3 bits are at HREF[5:3])
    // Because HREF[5:3] = 0b100, HSTOP = 0x5A*2^3 + 4 = 0x2D0
    // HSTART[REG17h] is the high 8-bit of H START (low 3 bits are at HREF[2:0])
    // Because HREF[2:0] = 0b100, HSTART = 0x32*2^3 + 4 = 0x190
    // Therefore HSTOP-HSTART = (0x2D0+4)-(0x190+4) = 0x140 (320 dec.)
    {0x32, 0xA4},// HREF       window control
    {0x18, 0x5A},
    {0x17, 0x32},

    // VSTRT      window control
    // VREF[REG03h] contains the start and end low 3 bits for VSTOP and VSTRT
    // VSTRT[REG19h] = 0x31*2^3 = 0x188
    // VSTOP[REG1Ah] = 0x4F*2^3 = 0x278
    // Therefore VSTOP - VSTRT = (0x278+2)-(0x188+2) = 0xF0 (240 dec.)
    {0x03, 0x12},
    {0x19, 0x31},    
    {0x1a, 0x4F},
    {0x14, 0x1a},    // COM9       automatic gain control ceilings
    {0x15, 0x10},    // COM10      set up pclk, vsync and href signals
    {0x3f, 0xa6},    // EDGE	   what edge enhancement ???
    {0x41, 0x02},    // COM16	   Color matrix coefficient double option enable ???
    {0x42, 0xc1},    // COM17	   edge enhancement option, tri-state output etc
    {0x1b, 0x00},    // PSHFT      set pclk delay from href
    {0x16, 0x06},    // RSVD	   another reserved register!
    {0x33, 0xe2},    // CHLF       array current control
    {0x34, 0xbf},    // ARBLM      array reference control
    {0x96, 0x04},    // RSVD	   again, reserved register
    {0x3a, 0x0c},    // TSLB	   line buffer test option for UV output and sequence setting
    {0x8e, 0x00},    // COM24	   Reserved register
    {0x3c, 0x77},    // COM12      href options
    {0x8b, 0x06},
    {0x94, 0x88},
    {0x95, 0x88},
    {0x40, 0xc1},
    {0x29, 0x3f},
    {0x0f, 0x42},
    {0x3d, 0x92},
    {0x69, 0x40},    // Manual Banding Filter MSB
    {0x5c, 0xb9},    // REG[0x59-0x61] all RSVD
    {0x5d, 0x96},	 
    {0x5e, 0x10},
    {0x59, 0xc0},
    {0x5a, 0xaf},
    {0x5f, 0xe0},
    {0x60, 0x8c},
    {0x61, 0x20},
    {0x5b, 0x55},    // REG[0x59-0x61] all RSVD
    {0x43, 0xf0},    // REG[0x43-0x4E] all RSVD
    {0x44, 0x10},
    {0x45, 0x68},
    {0x46, 0x96},
    {0x47, 0x60},
    {0x48, 0x80},
    {0xa5, 0xd9},    // RSVD
    {0xa4, 0x74},    // RSVD
    {0x8d, 0x02},    // color bar test mode disable, digital AWB enable
    {0x13, 0xe7},    // AGC, AWB, AEC all enabled here
    {0x4f, 0x3a},    // REG[4F-58] are Matrix coefficients
    {0x50, 0x3d},
    {0x51, 0x03},
    {0x52, 0x12},
    {0x53, 0x26},
    {0x54, 0x38},
    {0x55, 0x40},
    {0x56, 0x40},
    {0x57, 0x40},
    {0x58, 0x0d},
    {0x8c, 0x23},    // De-noise enable, white-pixel erase enable
    {0x3e, 0x02},
    {0xa9, 0xb8},    // REG[A8-AA] all RSVD
    {0xaa, 0x92},
    {0xab, 0x0a},
    {0x8f, 0xdf},    // Digital BLC offset sign???
    {0x90, 0x00},    // Digital BLC B channel offset value set default
    {0x91, 0x00},    // Digital BLC R channel offset value set default
    {0x9f, 0x00},    // Digital BLC Gb channel offset value set default
    {0xa0, 0x00},    // Digital BLC Gr channel offset value set default
    {0x24, 0x98},    // AEW stable operating region upper limit
    {0x25, 0x88},    // AEW stable operating region lower limit
    {0x26, 0xd3},    // AGC/AEC fast mode operating region
    {0x2a, 0x00},    // Horizontal dummy pixel insert MSB
    {0x2b, 0x00},    // Horizontal dummy insert LSB
    {0x2d, 0x00},    // Vertical LSB of dummy lines 
    {0x6c, 0x40},    // REG[6C-7B] are Gamma Curve setup GSP
    {0x6d, 0x30},	 
    {0x6e, 0x4b},
    {0x6f, 0x60},
    {0x70, 0x70},
    {0x71, 0x70},
    {0x72, 0x70},
    {0x73, 0x70},
    {0x74, 0x60},
    {0x75, 0x60},
    {0x76, 0x50},
    {0x77, 0x48},
    {0x78, 0x3a},
    {0x79, 0x2e},
    {0x7a, 0x28},
    {0x7b, 0x22},
    {0x7c, 0x04},    // REG[7C-8A] are Gamma Curve setup GST
    {0x7d, 0x07},
    {0x7e, 0x10},
    {0x7f, 0x28},
    {0x80, 0x36},
    {0x81, 0x44},
    {0x82, 0x52},
    {0x83, 0x60},
    {0x84, 0x6c},
    {0x85, 0x78},
    {0x86, 0x8c},
    {0x87, 0x9e},
    {0x88, 0xbb},
    {0x89, 0xd2},
    {0x8a, 0xe6},

    { 0xff,0xff},
};

#endif

