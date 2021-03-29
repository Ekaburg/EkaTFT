#ifndef ADCM2700_REGS_H
#define ADCM2700_REGS_H

/*

Using the Simple Control Registers
Follow these steps to change any of the simple control registers:
1 Stop the camera 
2 Change the relevant register.
For example, change the output size from QCIF to CIF, write 0x0202 to the
SIZE register.
3 Set the CONFIG bit in the CONTROL register, write 0x0004.
4 Wait for the CONFIG bit in CONTROL to clear.
5 Start the camera 

*/

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

const uint8_t ADCM2700_VGA[][3] PROGMEM =
{
    {  2, 0xA6, 640/16}, // {7|6|5|4|3|2|(1|0-Size of byte)}, Address (ID), Size X
    {480/16, 0b11000010, 0b00000000}, //  Size Y, Reset_Enable_N, 7|6|5|4|3|Vsync Invert|Hsync Invert|0
    { 0x02<<1, 0x00, 0x00},  // Camera OFF
    { 0x06<<1, 0xC0, 0x5D},  // External clock frequency
    { 0x08<<1, 0x06, 0x06},  // Image size and orientation
    { 0x0A<<1, 0x09, 0x09},  // Output Format YCbCr B, VSYNC Negative !
    { 0x12<<1,  250, 0x00},  // Frame Rate 25 Hz
    { 0x02<<1, 0x04, 0x00},  // Write new configuration
    { 0x02<<1, 0x01, 0x00},  // Camera ON

    { 0xff, 0xff, 0xff}, // end
};        

#endif // ADCM2700_REGS_H

