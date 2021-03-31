/*
 * Example sketch for Arduino EkaTFT shields and breakboards v1.xx, v2.xx, v3.xx, v4.xx
 * 
 * Author: Rinat G. (2020)
 * 
 * Comments: This sketch demonstrates Camera OV7670 initialization and view live image
 * 
 * Before Uploading, check the required EKA_TFT_VER_X definition in the file EKATFT.h
 * 
 */

#include <EKATFT.h>                    // Hardware-specific library
#include <util/ekacam.h>
#include "OV7670_regs.h"

EKATFT tft(0);
CAM    cam;

/*******************************************************************************
*
*******************************************************************************/
void setup() {

    uint8_t state;

    // initialize the serial port
    Serial.begin(115200);
    Serial.println("Camera initialization example!");

    // initialize the display
    tft.begin();

    // Camera OV7670 initialization
    cam.CamInit(&OV7670_VGA[0][0]);
    cam.CamVideoPreview(0, 0, 1, true);
}

void loop()
{
}
