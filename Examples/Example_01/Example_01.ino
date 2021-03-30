/*
 * Example sketch for Arduino EkaTFT shields and breakboards v1.xx, v2.xx, v3.xx, v4.xx
 * 
 * Author: Rinat G. (2020)
 * 
 * Comments:
 * This sketch demonstrate text & graphics.
 * Additionaly need Adafruit-GFX library
 * 
 * Before Uploading, check the required EKA_TFT_VER_X definition in the file EKATFT.h
 */

#include <EKATFT.h>                      // Hardware-specific library
#include <Adafruit_GFX.h>                // Include Adafruit-GFX library
#include <Fonts/FreeSerif9pt7b.h>        // Include Adafruit fonts
#include <Fonts/FreeSerifItalic24pt7b.h>
#include <Fonts/FreeSans24pt7b.h>

EKATFT tft(0);

uint32_t  total_time;
uint16_t  Color[4] = {BRIGHTBLUE, BRIGHTGREEN, BRIGHTRED, BRIGHTYELLOW};
uint16_t  Gray[7] = {GRAY0, GRAY1, GRAY2, GRAY3, GRAY4, GRAY5, GRAY6};

/*************************************************************************************************/
void ClearScreen (void)
{
    tft.SetColor(BLACK);   // Set fone color
    tft.ClearDevice();     // Fill all screen
}

void setup()
{
    Serial.begin(115200);  // initialize the serial port
    Serial.println("Arduino TFT_shield Example 1!");
    tft.begin(0);          // initialize the display
}

void loop()
{
    uint16_t  x, y, x2, y2, mask_gray;
    uint16_t  i;

    ClearScreen();

    // Fonts
    Serial.print("1) View Fonts (");
    total_time = millis();
    tft.SetColor(BRIGHTBLUE);
    tft.SetFont(NULL);
    tft.OutTextXY(5, 5, "Demonstration of work with the TFT display.");
    tft.SetColor(BRIGHTGREEN);
    tft.SetFont(&FreeSerif9pt7b);
    tft.OutTextXY(5, 20, "The   example   uses   fonts   from   Adafruit.");
    tft.SetFont(&FreeSerifItalic24pt7b);
    tft.SetColor(BRIGHTCYAN);
    tft.OutTextXY(5, 45, "3,5''");
    tft.SetColor(BRIGHTRED);
    tft.OutTextXY(90, 45, "QVGA");
    tft.SetColor(BRIGHTMAGENTA);
    tft.OutTextXY(230, 45, "disp.");
    tft.SetColor(BRIGHTYELLOW);
    tft.SetFont(&FreeSans24pt7b);
    tft.OutTextXY(5, 100, "A R D U I N O      +  T F T");

    tft.SetFont(NULL);
    for (i = 0; i < 7; i++)
    {
        tft.SetColor(Gray[i]);
        tft.OutTextXY(5, 170+10*i, "Demonstration of work with the TFT display.");
    }

    PrintTotalTime();

    delay(3000);
    ClearScreen();

    // Circle
    Serial.print("2) Draw circle (");
    total_time = millis();
    tft.SetColor(BRIGHTRED);
    for (i = 10; i < GetMaxY()>>1; i += 10) {
        tft.DrawCirc(GetMaxX()>>1, GetMaxY()>>1, i);
    }

    PrintTotalTime();

    delay(1000);

    // DrawFillCircle & DrawFillRect
    Serial.print("3) Draw FillCircle and FillRect (");
    total_time = millis();
    tft.SetColor(BRIGHTRED);
    tft.DrawFillCirc(GetMaxX()>>1,GetMaxY()>>1,110);
    tft.SetColor(BRIGHTCYAN);
    tft.DrawFillRect(GetMaxX()/2-77,GetMaxY()/2-77, GetMaxX()/2+77,GetMaxY()/2+77);
    tft.SetColor(BRIGHTGREEN);
    tft.DrawFillCirc(GetMaxX()>>1,GetMaxY()>>1,77);
    tft.SetColor(BRIGHTMAGENTA);
    tft.DrawFillRect(GetMaxX()/2-54,GetMaxY()/2-54, GetMaxX()/2+54,GetMaxY()/2+54);
    tft.SetColor(BRIGHTBLUE);
    tft.DrawFillCirc(GetMaxX()>>1,GetMaxY()>>1,54);
    tft.SetColor(BRIGHTYELLOW);
    tft.DrawFillRect(GetMaxX()/2-37,GetMaxY()/2-37, GetMaxX()/2+37,GetMaxY()/2+37);

    PrintTotalTime();

    delay(1000);
    ClearScreen();

    // Arc
    Serial.print("4) Draw Arc (");
    total_time = millis();
    ClearScreen();
    tft.SetColor(BRIGHTBLUE);
    tft.DrawArc((GetMaxX()>>1)-60,(GetMaxY()>>1)-60,(GetMaxX()>>1)+60,(GetMaxY()>>1)+60,20,30,0xFF);
    tft.SetColor(BRIGHTGREEN);
    tft.DrawArc((GetMaxX()>>1)-40,(GetMaxY()>>1)-40,(GetMaxX()>>1)+40,(GetMaxY()>>1)+40,20,30,0xFF);
    tft.SetColor(BRIGHTRED);
    tft.DrawArc((GetMaxX()>>1)-20,(GetMaxY()>>1)-20,(GetMaxX()>>1)+20,(GetMaxY()>>1)+20,20,30,0xFF);

    PrintTotalTime();

    delay(1000);

    Serial.print("5) Draw FillBevel (");
    total_time = millis();
    tft.SetColor(BRIGHTBLUE);
    tft.DrawFillBevel((GetMaxX()>>1)-60,(GetMaxY()>>1)-60,(GetMaxX()>>1)+60,(GetMaxY()>>1)+60,30);
    tft.SetColor(BRIGHTGREEN);
    tft.DrawFillBevel((GetMaxX()>>1)-40,(GetMaxY()>>1)-40,(GetMaxX()>>1)+40,(GetMaxY()>>1)+40,30);
    tft.SetColor(BRIGHTRED);
    tft.DrawFillBevel((GetMaxX()>>1)-20,(GetMaxY()>>1)-20,(GetMaxX()>>1)+20,(GetMaxY()>>1)+20,30);

    PrintTotalTime();

    delay(1000);
    ClearScreen();

    Serial.print("6) Draw Arc (");
    total_time = millis();
    for (i = 0; i < 4; i++) {
        tft.SetColor(Color[i]);
        tft.DrawArc((GetMaxX()>>1),(GetMaxY()>>1)-50,(GetMaxX()>>1),(GetMaxY()>>1)+50,50,60,0x11<<i);
    }
    for (i = 0; i < 4; i++) {
        tft.SetColor(Color[i]);
        tft.DrawArc((GetMaxX()>>1),(GetMaxY()>>1)-30,(GetMaxX()>>1),(GetMaxY()>>1)+30,35,45,0x11<<i);
    }
    for (i = 0; i < 4; i++) {
        tft.SetColor(Color[i]);
        tft.DrawArc((GetMaxX()>>1),(GetMaxY()>>1),(GetMaxX()>>1),(GetMaxY()>>1),20,30,0x11<<i);
    }

    PrintTotalTime();

    delay(1000);
    ClearScreen();

    // Draw 1000 random lines
    Serial.print("7) Draw 1000 random lines (");
    total_time = millis();
    for (i = 0; i < 1000; i++) {
        tft.SetColor(random(65535));
        x  = random(GetMaxX());
        y  = random(GetMaxY());
        x2 = random(GetMaxX());
        y2 = random(GetMaxY());
        tft.DrawLine(x, y, x2, y2);
    }

    PrintTotalTime();

    delay(1000);

    // ReDraw Fill Screen
    Serial.println("8) ReDraw 10 Fill Screen:");
    RedrawFillScreen(BLACK);
    RedrawFillScreen(BRIGHTBLUE);
    RedrawFillScreen(YELLOW);
    RedrawFillScreen(BRIGHTGREEN);
    RedrawFillScreen(BRIGHTRED);
    RedrawFillScreen(BRIGHTCYAN);
    RedrawFillScreen(GREEN);
    RedrawFillScreen(BRIGHTYELLOW);
    RedrawFillScreen(BRIGHTCYAN);
    RedrawFillScreen(BLACK);
}

void  PrintTotalTime (void)
{
    total_time = millis() - total_time;
    Serial.print(total_time);
    Serial.println(" ms)");
}

void  RedrawFillScreen (uint16_t color)
{
    // ReDraw Fill Screen
    Serial.print("ReDraw Fill Screen (");
    total_time = millis();

    tft.SetColor(color);   // Set fone color
    tft.ClearDevice();     // Fill all screen

    PrintTotalTime();

    delay(1000);
}
