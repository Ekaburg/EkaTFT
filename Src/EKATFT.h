/******************************************************************************
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL AUTHOR OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
*******************************************************************************/
#ifndef _EKATFT_H_
#define _EKATFT_H_

#define EKA_TFT_VER_1   // 3.5' 320x240 TFT
//#define EKA_TFT_VER_2   // Break Board for Arduino Nano 
//#define EKA_TFT_VER_3   // Break Board for ESP-32
//#define EKA_TFT_VER_4   // 2.8' 320x240 TFT

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <TimeLib.h> // Do not delete !

/************************************************************
 * Defines
 ************************************************************/

#define MASK_I2C_BAUD                               7
#define MASK_I2C_START                           0x80
#define MASK_I2C_STOP                            0x10
#define MASK_I2C_IDLE                            0x00
#define MASK_I2C_WRITE                           0x01
#define MASK_I2C_READ_W_ACK                      0x02
#define MASK_I2C_READ_WO_ACK                     0x03

#define START_ADD                                 0ul
#define FRAME_SIZE              (320ul * 240ul * 2ul)

#ifndef EOF
    #define EOF                             ((int)-1)
#endif

#ifndef FALSE
    #define FALSE                                   0
#endif
#ifndef TRUE
    #define TRUE                               !FALSE  // True value
#endif

#define LSC(c) LCD_SendCommand(c)
#define LSD(d) LCD_SendData(d)
#define LSA(a,b) {LSC(a);LSD(b);}
#define LSB(a,b) {LSD(a);LSD(b);}
#define LSE(a,b,c) {LSD(a);LSD(b);LSD(c);}
#define LSF(a,b,c,d) {LSD(a);LSD(b);LSD(c);LSD(d);}

#define WRITE_THROUGH_MODE                          0
#define AUTO_REFRESH_MODE                           1

//--------------------------------------------------------------------//
#define DS1307_ADDRESS                           0xD0
#define DS1307_CONTROL                           0x07
#define DS1307_NVRAM                             0x08

typedef struct {
    uint8_t info; uint8_t fontID; uint16_t firstChar; uint16_t lastChar; uint8_t reserved; uint8_t height;
} FONT_HEADER;

// Structure describing font glyph entry
typedef struct { uint8_t offsetMSB; uint8_t width; uint16_t offsetLSB;} GLYPH_ENTRY;

typedef enum{ TYPE_FLASH=0, TYPE_EXTERNAL=1, TYPE_VIDEOBUF=2} TYPE_MEMORY;

typedef struct { TYPE_MEMORY type; char *address;} FONT_FLASH;

typedef struct _PREVIEW_PARAM { uint8_t previewHRatio; uint8_t previewVRatio; uint16_t previewCropHStart;
                                uint16_t previewCropVStart; uint16_t previewCropHSize; uint16_t previewCropVSize;} PREVIEW_PARAM;

typedef union {
    uint8_t Val;
    struct __attribute__((packed)) {uint8_t b0:1;uint8_t b1:1;uint8_t b2:1;uint8_t b3:1;uint8_t b4:1;uint8_t b5:1;uint8_t b6:1;uint8_t b7:1;} bits;
} BYTE_VAL, BYTE_BITS;

typedef union {
    uint16_t Val;
    uint8_t v[2];
    struct __attribute__((packed)) { uint8_t LB; uint8_t HB;} byte;
    struct __attribute__((packed)) { uint8_t b0:1;uint8_t b1:1;uint8_t b2:1;uint8_t b3:1;uint8_t b4:1;uint8_t b5:1;uint8_t b6:1;uint8_t b7:1;uint8_t b8:1;
                                     uint8_t b9:1;uint8_t b10:1;uint8_t b11:1;uint8_t b12:1;uint8_t b13:1;uint8_t b14:1;uint8_t b15:1;} bits;
} WORD_VAL, WORD_BITS;

typedef union {
    uint32_t Val;
    uint16_t w[2];
    uint8_t  v[4];
    struct __attribute__((packed)) { uint16_t LW; uint16_t HW;} word;
    struct __attribute__((packed)) { uint8_t LB;uint8_t HB;uint8_t UB;uint8_t MB;} byte;
    struct __attribute__((packed)) { WORD_VAL low; WORD_VAL high;}wordUnion;
    struct __attribute__((packed)) { uint8_t b0:1;uint8_t b1:1;uint8_t b2:1;uint8_t b3:1;uint8_t b4:1;uint8_t b5:1;uint8_t b6:1;uint8_t b7:1;
                                     uint8_t b8:1;uint8_t b9:1;uint8_t b10:1;uint8_t b11:1;uint8_t b12:1;uint8_t b13:1;uint8_t b14:1;uint8_t b15:1;
                                     uint8_t b16:1;uint8_t b17:1;uint8_t b18:1;uint8_t b19:1;uint8_t b20:1;uint8_t b21:1;uint8_t b22:1;uint8_t b23:1;
                                     uint8_t b24:1;uint8_t b25:1;uint8_t b26:1;uint8_t b27:1;uint8_t b28:1;uint8_t b29:1;uint8_t b30:1;uint8_t b31:1;} bits;
} DWORD_VAL;

#ifndef _GFXFONT_H_
#define _GFXFONT_H_
typedef struct { // Data stored PER GLYPH
    uint16_t  bitmapOffset;     // Pointer into GFXfont->bitmap
    uint8_t   width, height;    // Bitmap dimensions in pixels
    uint8_t   xAdvance;         // Distance to advance cursor (x axis)
    int8_t    xOffset, yOffset; // Dist from cursor pos to UL corner
} GFXglyph;

typedef struct { // Data stored for FONT AS A WHOLE:
    uint8_t  *bitmap;           // Glyph bitmaps, concatenated
    GFXglyph *glyph;            // Glyph array
    uint8_t   first, last;      // ASCII extents
    uint8_t   yAdvance;         // Newline distance (y axis)
} GFXfont;
#endif /* _GFXFONT_H_ */

typedef struct  { 
  uint8_t Second; 
  uint8_t Minute; 
  uint8_t Hour; 
  uint8_t Wday;   // day of week, sunday is day 1
  uint8_t Day;
  uint8_t Month; 
  uint8_t Year;   // offset from 1970; 
} RtcElements_t;

#define  tmYearToY2k(Y)      ((Y) - 30)    // offset is from 2000
#define  y2kYearToTm(Y)      ((Y) + 30)   

// For compatibility with sketches written for older versions of library.
// Color function name was changed to 'color565' for parity with 2.2" LCD
// library.
#define Color565 color565

/******************************************************************************
 * User Defines
 *****************************************************************************/
/* Results of Disk Functions */
typedef enum {
    RES_OK = 0,     /* 0: Successful */
    RES_ERROR,      /* 1: R/W Error */
    RES_WRPRT,      /* 2: Write Protected */
    RES_NOTRDY,     /* 3: Not Ready */
    RES_PARERR      /* 4: Invalid Parameter */
} DRESULT;

#define MEDIA_SECTOR_SIZE   (uint32_t) 512

#define IMAGE_NORMAL       1  // Normal image stretch code
#define IMAGE_X2           2  // Stretched image stretch code
// constants used for circle/arc computation
#define SIN45          46341  // sin(45) * 2^16)
#define ONEP25         81920  // 1.25 * 2^16

/*********************************************************************
* Overview: Horizontal or vertical screen size.
*********************************************************************/

#define DISP_HOR_RESOLUTION                       320
#define DISP_VER_RESOLUTION                       240
#define DISP_DATA_WIDTH                             8
#define DISP_INV_LSHIFT
#define DISP_HOR_PULSE_WIDTH                        4
#define DISP_HOR_BACK_PORCH                        14
#define DISP_HOR_FRONT_PORCH                       70
#define DISP_VER_PULSE_WIDTH                        1
#define DISP_VER_BACK_PORCH                        12
#define DISP_VER_FRONT_PORCH                       12
#define SCREEN_HOR_SIZE                           320
#define SCREEN_VER_SIZE                           240
#define LINE_MEM_PITCH                            SCREEN_HOR_SIZE
#define PAGE_MEM_SIZE     (uint32_t)SCREEN_HOR_SIZE*SCREEN_VER_SIZE*2 

#define GetX()          _cursorX
#define GetY()          _cursorY
#define MoveTo(x,y)     _cursorX=x; _cursorY=y;
#define MoveRel(dX,dY)  _cursorX+=dX; _cursorY+=dY;

/*********************************************************************
* Overview: Some basic colors definitions.
*********************************************************************/
// COLORS

#define RGBConvert(red, green, blue)    (uint16_t) ((((uint16_t)(red) & 0xF8) << 8) | (((uint16_t)(green) & 0xFC) << 3) | ((uint16_t)(blue) >> 3))
#define RGB565CONVERT(r, g, b) (((r & 0x00F8) << 8) | ((g & 0x00FC) << 3) | (b >> 3))

#ifndef BLACK
#define BLACK                           RGBConvert(0, 0, 0)
#endif
#ifndef BRIGHTBLUE
#define BRIGHTBLUE                      RGBConvert(0, 0, 255)
#endif
#ifndef BRIGHTGREEN
#define BRIGHTGREEN                     RGBConvert(0, 255, 0)
#endif
#ifndef BRIGHTCYAN
#define BRIGHTCYAN                      RGBConvert(0, 255, 255)
#endif
#ifndef BRIGHTRED
#define BRIGHTRED                       RGBConvert(255, 0, 0)
#endif
#ifndef BRIGHTMAGENTA
#define BRIGHTMAGENTA                   RGBConvert(255, 0, 255)
#endif
                                                  //RRRRRGGGGGGBBBBB
#define BRIGHTYELLOW                    (uint16_t)0b1111111111100000
#define BLUE                            (uint16_t)0b0000000000010000
#define GREEN                           (uint16_t)0b0000010000000000
#define CYAN                            (uint16_t)0b0000010000010000
#define RED                             (uint16_t)0b1000000000000000
#define MAGENTA                         (uint16_t)0b1000000000010000
#define BROWN                           (uint16_t)0b1111110000000000
#define LIGHTGRAY                       (uint16_t)0b1000010000010000
#define DARKGRAY                        (uint16_t)0b0100001000001000
#define LIGHTBLUE                       (uint16_t)0b1000010000011111
#define LIGHTGREEN                      (uint16_t)0b1000011111110000
#define LIGHTCYAN                       (uint16_t)0b1000011111111111
#define LIGHTRED                        (uint16_t)0b1111110000010000
#define LIGHTMAGENTA                    (uint16_t)0b1111110000011111
#define YELLOW                          (uint16_t)0b1111111111110000
#define WHITE                           (uint16_t)0b1111111111111111
#define GRAY0                           (uint16_t)0b1110011100011100
#define GRAY1                           (uint16_t)0b1100011000011000
#define GRAY2                           (uint16_t)0b1010010100010100
#define GRAY3                           (uint16_t)0b1000010000010000
#define GRAY4                           (uint16_t)0b0110001100001100
#define GRAY5                           (uint16_t)0b0100001000001000
#define GRAY6                           (uint16_t)0b0010000100000100

#define EMBOSSDKCOLORDEFAULT            RGB565CONVERT(0x2B, 0x55, 0x87)  // Emboss dark color default value.
#define EMBOSSLTCOLORDEFAULT            RGB565CONVERT(0xD4, 0xE4, 0xF7)  // Emboss light color default value.
#define TEXTCOLOR0DEFAULT               RGB565CONVERT(0x07, 0x1E, 0x48)  // Text color 0 default value.
#define TEXTCOLOR1DEFAULT               WHITE                            // Text color 1 default value.
#define TEXTCOLORDISABLEDDEFAULT        WHEAT                            // Text color disabled default value.
#define COLOR0DEFAULT                   RGB565CONVERT(0xA9, 0xDB, 0xEF)  // Color 0 default value.
#define COLOR1DEFAULT                   RGB565CONVERT(0x26, 0xC7, 0xF2)  // Color 1 default value.
#define COLORDISABLEDDEFAULT            RGB565CONVERT(0xB6, 0xD2, 0xFB)  // Disabled color default value.
#define COMMONBACKGROUNDCOLORDEFAULT    RGB565CONVERT(0xD4, 0xED, 0xF7)  // Common background color default value.
// Brown color scheme
#define SADDLEBROWN                     RGB565CONVERT( 139,   69,   19)  // Saddle Color
#define SIENNA                          RGB565CONVERT( 160,   82,   45)  // Sienna Color
#define PERU                            RGB565CONVERT( 205,  133,   63)  // Peru Color
#define BURLYWOOD                       RGB565CONVERT( 222,  184,  135)  // Burly wood Color
#define WHEAT                           RGB565CONVERT( 245,  245,  220)  // Wheat Color
#define TAN                             RGB565CONVERT( 210,  180,  140)  // Tan Color
#define GRAY80                          RGB565CONVERT( 204,  204,  204)  // Gray80 Color
#define GRAY90                          RGB565CONVERT( 229,  229,  229)  // Gray90 Color
#define GRAY95                          RGB565CONVERT( 242,  242,  242)  // Gray95 Color


#define DrawCirc(x, y, radius)              DrawBevel(x,y,x,y,radius)
#define DrawFillCirc(x1, y1, rad)           DrawFillBevel(x1, y1, x1, y1, rad)
#define DrawRect(left, top, right, bottom)  DrawBevel(left, top, right, bottom, 0)
#define Backlight(on)                       gpio_bl(on)

#define DELAY7        \
  asm volatile(       \
    "rjmp .+0" "\n\t" \
    "rjmp .+0" "\n\t" \
    "rjmp .+0" "\n\t" \
    "nop"      "\n"   \
    ::);

#ifdef EKA_TFT_VER_2   // 320x240 TFT Arduino Nano
#define LCD_RESET 0x10
#define LCD_BL    0x08
#else
#define LCD_BL    0x10
#define LCD_RESET 0x08
#define LCD_SPENA 0x04
#define LCD_SPCLK 0x02
#define LCD_SPDAT 0x01
#endif // EKA_TFT_VER_2

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || defined (__AVR_ATmega328__) || defined(__AVR_ATmega8__)

// Arduino Uno, Duemilanove, etc.
#define write8inline(d)         { PORTD = (PORTD & B00000111) | ((d) & B11111000); PORTB = (PORTB & B11111000) | ((d) & B00000111); CS_ACTIVE;CS_IDLE; }
#define read8inline(result)     { CS_ACTIVE; DELAY7; result = (PIND & B11111000) | (PINB & B00000111); CS_IDLE; }
#define setWriteDirInline()     { DDRD |=  B11111000; DDRB |=  B00000111; }
#define setReadDirInline()      { DDRD &= ~B11111000; DDRB &= ~B00000111; }
#define readport8inline(result) { result = ((PINB & B00000111) | (PIND & B11111000)); }
#define scanButtonsInline(result) { RD_ACTIVE; setReadDirInline(); DELAY7; DELAY7; DELAY7; \
                                  result = (PIND & B11111000) | (PINB & B00000111); setWriteDirInline();}
#define write8                  write8inline
#define CD_MASK                 B00000001
#define CS_MASK                 B00000010
#define RD_MASK                 B00000100
#ifdef EKA_TFT_VER_2   // 320x240 TFT Arduino Nano
#define RST_MASK                B00001000
#define WR_MASK                 B00010000
#else
#define WR_MASK                 B00001000
#define RST_MASK                B00010000
#endif // EKA_TFT_VER_2   // 320x240 TFT Arduino Nano
#define OUT_DIR_SIGNAL          DDRC  |= (CD_MASK|CS_MASK|RD_MASK|WR_MASK|RST_MASK)
#define CD_COMMAND              PORTC &= ~CD_MASK 
#define CD_DATA                 PORTC |=  CD_MASK 
#define CS_ACTIVE               PORTC &= ~CS_MASK 
#define CS_IDLE                 PORTC |=  CS_MASK 
#define RD_ACTIVE               PORTC &= ~RD_MASK 
#define RD_IDLE                 PORTC |=  RD_MASK 
#define WR_ACTIVE               PORTC &= ~WR_MASK 
#define WR_IDLE                 PORTC |=  WR_MASK 
#define RST_ACTIVE              PORTC &= ~RST_MASK
#define RST_IDLE                PORTC |=  RST_MASK
#define WR_RD_CS_IDLE           PORTC |=  (WR_MASK|RD_MASK|CS_MASK)
#define RST_CD_ACTIVE           PORTC &= ~(RST_MASK|CD_MASK)       
#define WR_CD_ACTIVE            PORTC &= ~(WR_MASK|CD_MASK)        
#define RD_CD_IDLE              PORTC |=  (RD_MASK|CD_MASK)        
#define WR_CD_IDLE              PORTC |=  (WR_MASK|CD_MASK)        
#define WR_CS_CD_IDLE           PORTC |=  (WR_MASK|CS_MASK|CD_MASK)
#define RD_CS_ACTIVE            PORTC &= ~(RD_MASK|CS_MASK)        
#define RD_CS_IDLE              PORTC |=  (RD_MASK|CS_MASK)        

#elif defined(__AVR_ATmega1281__) || defined(__AVR_ATmega2561__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__) 

#define write8inline(d)         { PORTH = (PORTH&B10000111)|(((d)&B11000000)>>3)|(((d)&B00000011)<<5); \
                                  PORTE = (PORTE&B11010111)|(((d)&B00100000)>>2)|(((d)&B00001000)<<2); \
                                  PORTG = (PORTG&B11011111)|(((d)&B00010000)<<1);                      \
                                  PORTB = (PORTG&B11101111)|(((d)&B00000100)<<2); CS_ACTIVE;CS_IDLE; }
#define read8inline(result)     { CS_ACTIVE;                                                           \
                                  result = ((PINH & B00011000) << 3) | ((PINE & B00001000) << 2) | ((PING & B00100000) >> 1) | \
                                           ((PINE & B00100000) >> 2) | ((PINB & B00010000) >> 2) | ((PINH & B01100000) >> 5);  \
                                  CS_IDLE; }
#define setWriteDirInline()     { DDRH |=  B01111000; DDRE |=  B00101000; DDRG |=  B00100000; DDRB |=  B00010000;}
#define setReadDirInline()      { DDRH &= ~B01111000; DDRE &= ~B00101000; DDRG &= ~B00100000; DDRB &= ~B00010000;}
#define readport8inline(result) { result = ((PINH & B00011000) << 3) | ((PINE & B00001000) << 2) | ((PING & B00100000) >> 1) | \
                                           ((PINE & B00100000) >> 2) | ((PINB & B00010000) >> 2) | ((PINH & B01100000) >> 5);}
#define scanButtonsInline(result) { RD_ACTIVE; setReadDirInline(); DELAY7; DELAY7; DELAY7; \
                                  result = ((PING & B00100000) >> 1) | ((PINE & B00100000) >> 2) | \
                                           ((PINB & B00010000) >> 2) | ((PINH & B01100000) >> 5); setWriteDirInline();}

#define write8                  write8inline
#define CD_MASK                 B00000001
#define CS_MASK                 B00000010
#define RD_MASK                 B00000100
#ifdef EKA_TFT_VER_2   // 320x240 TFT Arduino Nano
#define RST_MASK                B00001000
#define WR_MASK                 B00010000
#else
#define WR_MASK                 B00001000
#define RST_MASK                B00010000
#endif // EKA_TFT_VER_2   // 320x240 TFT Arduino Nano
#define OUT_DIR_SIGNAL          DDRF  |= (CD_MASK|CS_MASK|RD_MASK|WR_MASK|RST_MASK)
#define CD_COMMAND              PORTF &= ~CD_MASK 
#define CD_DATA                 PORTF |=  CD_MASK 
#define CS_ACTIVE               PORTF &= ~CS_MASK 
#define CS_IDLE                 PORTF |=  CS_MASK 
#define RD_ACTIVE               PORTF &= ~RD_MASK 
#define RD_IDLE                 PORTF |=  RD_MASK 
#define WR_ACTIVE               PORTF &= ~WR_MASK 
#define WR_IDLE                 PORTF |=  WR_MASK 
#define RST_ACTIVE              PORTF &= ~RST_MASK
#define RST_IDLE                PORTF |=  RST_MASK
#define WR_RD_CS_IDLE           PORTF |=  (WR_MASK|RD_MASK|CS_MASK)
#define RST_CD_ACTIVE           PORTF &= ~(RST_MASK|CD_MASK)       
#define WR_CD_ACTIVE            PORTF &= ~(WR_MASK|CD_MASK)        
#define RD_CD_IDLE              PORTF |=  (RD_MASK|CD_MASK)        
#define WR_CD_IDLE              PORTF |=  (WR_MASK|CD_MASK)        
#define WR_CS_CD_IDLE           PORTF |=  (WR_MASK|CS_MASK|CD_MASK)
#define RD_CS_ACTIVE            PORTF &= ~(RD_MASK|CS_MASK)        
#define RD_CS_IDLE              PORTF |=  (RD_MASK|CS_MASK)        

#elif defined(ESP32) /////////////////////////////////////////////////////////////////////////////////////////////////////

#define LCD_CD     2 // Command/Data goes to Analog 0
#define LCD_CS     4 // Chip Select goes to Analog 1
#define LCD_RD    15 // LCD Read goes to Analog 2
#define LCD_WR    33 // LCD Write goes to Analog 3
#define LCD_RST   32 // Can alternately just connect to Arduino's reset pin

//#define LCD_D0  26 // LCD Data 0
#define LCD_D0     5 // LCD Data 0
#define LCD_D1    25 // LCD Data 1
#define LCD_D2    17 // LCD Data 2
#define LCD_D3    16 // LCD Data 3
#define LCD_D4    27 // LCD Data 4
#define LCD_D5    14 // LCD Data 5
#define LCD_D6    12 // LCD Data 6
#define LCD_D7    13 // LCD Data 7

#define LCD_D3_PIN    0x02000000 // LCD Data 1
#define LCD_D4_PIN    0x00020000 // LCD Data 2
#define LCD_D5_PIN    0x00010000 // LCD Data 3
#define LCD_D6_PIN    0x08000000 // LCD Data 4
#define LCD_D7_PIN    0x00004000 // LCD Data 5
#define LCD_D0_PIN    0x00001000 // LCD Data 6
#define LCD_D1_PIN    0x00002000 // LCD Data 7
#define LCD_D2_PIN    0x00000020 // LCD Data 0

#define LCD_PORT_PIN  LCD_D0_PIN|LCD_D1_PIN|LCD_D2_PIN|LCD_D3_PIN|LCD_D4_PIN|LCD_D5_PIN|LCD_D6_PIN|LCD_D7_PIN

#define setReadDirInline()      gpio_output_set(   0,  0, 0x00000000, LCD_PORT_PIN);
#define setWriteDirInline()     gpio_output_set(   0,  0, LCD_PORT_PIN, 0x00000000);
#define OUT_DIR_SIGNAL          {pinMode(LCD_CD,OUTPUT);pinMode(LCD_CS,OUTPUT);pinMode(LCD_RD,OUTPUT);pinMode(LCD_WR,OUTPUT);pinMode(LCD_RST,OUTPUT);pinMode(26,OUTPUT);pinMode(25,OUTPUT);pinMode(17,OUTPUT);pinMode(16,OUTPUT);pinMode(27,OUTPUT);pinMode(14,OUTPUT);pinMode(12,OUTPUT);pinMode(13,OUTPUT);pinMode(5,OUTPUT);pinMode(23,OUTPUT);}

#define RD_ACTIVE               gpio_set_level((gpio_num_t)LCD_RD,LOW)
#define RD_IDLE                 gpio_set_level((gpio_num_t)LCD_RD,HIGH)
#define RST_ACTIVE              gpio_set_level((gpio_num_t)LCD_RST,LOW)
#define RST_IDLE                gpio_set_level((gpio_num_t)LCD_RST,HIGH)
#define WR_ACTIVE               gpio_set_level((gpio_num_t)LCD_WR,LOW)
#define WR_IDLE                 gpio_set_level((gpio_num_t)LCD_WR,HIGH)
#define CD_COMMAND              gpio_set_level((gpio_num_t)LCD_CD,LOW)
#define CD_DATA                 gpio_set_level((gpio_num_t)LCD_CD,HIGH)
#define CS_ACTIVE               gpio_set_level((gpio_num_t)LCD_CS,LOW)
#define CS_IDLE                 gpio_set_level((gpio_num_t)LCD_CS,HIGH)
#define WR_RD_CS_IDLE           {WR_IDLE;RD_IDLE;CS_IDLE;}
#define RST_CD_ACTIVE           {RST_ACTIVE;CD_COMMAND;}
#define WR_CD_ACTIVE            {WR_ACTIVE;CD_COMMAND;}
#define RD_CD_IDLE              {RD_IDLE;CD_DATA;}
#define WR_CD_IDLE              {WR_IDLE;CD_DATA;}
#define WR_CS_CD_IDLE           {WR_IDLE;CS_IDLE;CD_DATA;}
#define RD_CS_ACTIVE            {RD_ACTIVE;CS_ACTIVE;}
#define RD_CS_IDLE              {RD_IDLE;CS_IDLE;}

// Data write strobe, ~2 instructions and always inline
#define WR_STROBE { WR_ACTIVE; WR_IDLE; }

#define scanButtonsInline(result) { RD_ACTIVE;setReadDirInline();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();_NOP(); \
                                  readport8inline(result); setWriteDirInline();}

#define write8inline(d)  { uint32_t reg_hi=0, reg_lo=0;  \
                           if ((d)&0x01)  reg_hi = (reg_hi | LCD_D0_PIN);               \
                           else           reg_lo = (reg_lo | LCD_D0_PIN);               \
                           if ((d)&0x02)  reg_hi = (reg_hi | LCD_D1_PIN);               \
                           else           reg_lo = (reg_lo | LCD_D1_PIN);               \
                           if ((d)&0x04)  reg_hi = (reg_hi | LCD_D2_PIN);               \
                           else           reg_lo = (reg_lo | LCD_D2_PIN);               \
                           if ((d)&0x08)  reg_hi = (reg_hi | LCD_D3_PIN);               \
                           else           reg_lo = (reg_lo | LCD_D3_PIN);               \
                           if ((d)&0x10)  reg_hi = (reg_hi | LCD_D4_PIN);               \
                           else           reg_lo = (reg_lo | LCD_D4_PIN);               \
                           if ((d)&0x20)  reg_hi = (reg_hi | LCD_D5_PIN);               \
                           else           reg_lo = (reg_lo | LCD_D5_PIN);               \
                           if ((d)&0x40)  reg_hi = (reg_hi | LCD_D6_PIN);               \
                           else           reg_lo = (reg_lo | LCD_D6_PIN);               \
                           if ((d)&0x80)  reg_hi = (reg_hi | LCD_D7_PIN);               \
                           else           reg_lo = (reg_lo | LCD_D7_PIN);               \
                           gpio_output_set(reg_hi, reg_lo, LCD_PORT_PIN, 0x00000000); \
                           _NOP(); _NOP(); CS_ACTIVE; _NOP(); _NOP(); CS_IDLE;}

#define readport8inline(result)   { uint32_t  shift=READ_PERI_REG(GPIO_IN_REG); shift=READ_PERI_REG(GPIO_IN_REG);\
                                    uint32_t  result8 = 0;                      \
                                    if (shift & LCD_D0_PIN) result8 = (result8 | 0x01);    \
                                    if (shift & LCD_D1_PIN) result8 = (result8 | 0x02);    \
                                    if (shift & LCD_D2_PIN) result8 = (result8 | 0x04);    \
                                    if (shift & LCD_D3_PIN) result8 = (result8 | 0x08);    \
                                    if (shift & LCD_D4_PIN) result8 = (result8 | 0x10);    \
                                    if (shift & LCD_D5_PIN) result8 = (result8 | 0x20);    \
                                    if (shift & LCD_D6_PIN) result8 = (result8 | 0x40);    \
                                    if (shift & LCD_D7_PIN) result8 = (result8 | 0x80);    \
                                    (result) = result8;}

/*********************************************************************************
*  read8
*
*	7	6	5	4	3	2	1	0
*
*	14	27	16	17	25	26      13	12
*
*
*	27	26	25	17	16	14	13	12
*
*	21	24	22	13	11	7	12	12	
*
*********************************************************************************/
#define read8inline(result)  { CS_ACTIVE;_NOP();_NOP();_NOP();_NOP();_NOP();_NOP();readport8inline(result); _NOP(); CS_IDLE; }

#define write8                  write8inline

 #warning "To Do !!!"

#else

 #error "Board type unsupported / not recognized"

#endif

#define wrReg8inline(a, d)     {uint8_t hi,lo;hi=(a)>>8;lo=(a);WR_CD_ACTIVE;RD_IDLE;write8(0);write8(hi);write8(lo);CD_DATA;write8(d);WR_IDLE;}
#define wrReg16inline(a, d)    {uint8_t hi,lo;hi=(a)>>8;lo=(a);WR_CD_ACTIVE;RD_IDLE;write8(0);write8(hi);write8(lo);CD_DATA;write8(d);write8(d>>8);WR_IDLE;}
#define wrReg32inline(a, d)    {uint8_t hi,lo;hi=(a)>>8;lo=(a);WR_CD_ACTIVE;RD_IDLE;write8(0);write8(hi);write8(lo);CD_DATA;write8(d);write8(d>>8);write8(d>>16);write8(d>>24);WR_IDLE;}
#define gpio_blInline(a)       {if(a)gpioStatus=gpioStatus|LCD_BL;else gpioStatus=gpioStatus&(~LCD_BL);wrReg8(0xAC,gpioStatus);}
#define gpio_sprstInline(a)    {if(a)gpioStatus=gpioStatus|LCD_RESET;else gpioStatus=gpioStatus&(~LCD_RESET);wrReg8(0xAC,gpioStatus);}
#ifndef EKA_TFT_VER_2   // 320x240 TFT Arduino Nano
#define gpio_spenaInline(a)    {if(a)gpioStatus=gpioStatus|LCD_SPENA;else gpioStatus=gpioStatus&(~LCD_SPENA);wrReg8(0xAC,gpioStatus);}
#define gpio_spclkInline(a)    {if(a)gpioStatus=gpioStatus|LCD_SPCLK;else gpioStatus=gpioStatus&(~LCD_SPCLK);wrReg8(0xAC,gpioStatus);}
#define gpio_spdatInline(a)    {if(a)gpioStatus=gpioStatus|LCD_SPDAT;else gpioStatus=gpioStatus&(~LCD_SPDAT);wrReg8(0xAC,gpioStatus);}
#define spi_writeInline(byte)  {uint8_t bit_ctr;for(bit_ctr=0;bit_ctr<8;bit_ctr++){if(byte&0x80)gpio_spdat(1);else gpio_spdat(0);gpio_spclk(0);gpio_spclk(1);byte=(byte<<1);}}
#define spi_setregwInline(reg, cmd) {uint8_t hi,lo;hi=(cmd)>>8;lo=(cmd);gpio_spena(0);spi_write(0x70);spi_write(0x00);spi_write(reg);gpio_spena(1);gpio_spena(0);spi_write(0x72);spi_write(hi);spi_write(lo);gpio_spena(1);}
#define spi_setregbInline(reg, cmd) {uint16_t _val;uint8_t hi,lo;_val=reg;_val=((_val<<10)|0x0200);_val=_val|cmd;hi=(_val)>>8;lo=(_val);gpio_spena(0);spi_write(hi);spi_write(lo);gpio_spena(1);}
#endif // EKA_TFT_VER_2   // 320x240 TFT Arduino Nano


static const unsigned char font[] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00,
0x3E, 0x5B, 0x4F, 0x5B, 0x3E,
0x3E, 0x6B, 0x4F, 0x6B, 0x3E,
0x1C, 0x3E, 0x7C, 0x3E, 0x1C,
0x18, 0x3C, 0x7E, 0x3C, 0x18,
0x1C, 0x57, 0x7D, 0x57, 0x1C,
0x1C, 0x5E, 0x7F, 0x5E, 0x1C,
0x00, 0x18, 0x3C, 0x18, 0x00,
0xFF, 0xE7, 0xC3, 0xE7, 0xFF,
0x00, 0x18, 0x24, 0x18, 0x00,
0xFF, 0xE7, 0xDB, 0xE7, 0xFF,
0x30, 0x48, 0x3A, 0x06, 0x0E,
0x26, 0x29, 0x79, 0x29, 0x26,
0x40, 0x7F, 0x05, 0x05, 0x07,
0x40, 0x7F, 0x05, 0x25, 0x3F,
0x5A, 0x3C, 0xE7, 0x3C, 0x5A,
0x7F, 0x3E, 0x1C, 0x1C, 0x08,
0x08, 0x1C, 0x1C, 0x3E, 0x7F,
0x14, 0x22, 0x7F, 0x22, 0x14,
0x5F, 0x5F, 0x00, 0x5F, 0x5F,
0x06, 0x09, 0x7F, 0x01, 0x7F,
0x00, 0x66, 0x89, 0x95, 0x6A,
0x60, 0x60, 0x60, 0x60, 0x60,
0x94, 0xA2, 0xFF, 0xA2, 0x94,
0x08, 0x04, 0x7E, 0x04, 0x08,
0x10, 0x20, 0x7E, 0x20, 0x10,
0x08, 0x08, 0x2A, 0x1C, 0x08,
0x08, 0x1C, 0x2A, 0x08, 0x08,
0x1E, 0x10, 0x10, 0x10, 0x10,
0x0C, 0x1E, 0x0C, 0x1E, 0x0C,
0x30, 0x38, 0x3E, 0x38, 0x30,
0x06, 0x0E, 0x3E, 0x0E, 0x06,
0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x5F, 0x00, 0x00,
0x00, 0x07, 0x00, 0x07, 0x00,
0x14, 0x7F, 0x14, 0x7F, 0x14,
0x24, 0x2A, 0x7F, 0x2A, 0x12,
0x23, 0x13, 0x08, 0x64, 0x62,
0x36, 0x49, 0x56, 0x20, 0x50,
0x00, 0x08, 0x07, 0x03, 0x00,
0x00, 0x1C, 0x22, 0x41, 0x00,
0x00, 0x41, 0x22, 0x1C, 0x00,
0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
0x08, 0x08, 0x3E, 0x08, 0x08,
0x00, 0x80, 0x70, 0x30, 0x00,
0x08, 0x08, 0x08, 0x08, 0x08,
0x00, 0x00, 0x60, 0x60, 0x00,
0x20, 0x10, 0x08, 0x04, 0x02,
0x3E, 0x51, 0x49, 0x45, 0x3E,
0x00, 0x42, 0x7F, 0x40, 0x00,
0x72, 0x49, 0x49, 0x49, 0x46,
0x21, 0x41, 0x49, 0x4D, 0x33,
0x18, 0x14, 0x12, 0x7F, 0x10,
0x27, 0x45, 0x45, 0x45, 0x39,
0x3C, 0x4A, 0x49, 0x49, 0x31,
0x41, 0x21, 0x11, 0x09, 0x07,
0x36, 0x49, 0x49, 0x49, 0x36,
0x46, 0x49, 0x49, 0x29, 0x1E,
0x00, 0x00, 0x14, 0x00, 0x00,
0x00, 0x40, 0x34, 0x00, 0x00,
0x00, 0x08, 0x14, 0x22, 0x41,
0x14, 0x14, 0x14, 0x14, 0x14,
0x00, 0x41, 0x22, 0x14, 0x08,
0x02, 0x01, 0x59, 0x09, 0x06,
0x3E, 0x41, 0x5D, 0x59, 0x4E,
0x7C, 0x12, 0x11, 0x12, 0x7C,
0x7F, 0x49, 0x49, 0x49, 0x36,
0x3E, 0x41, 0x41, 0x41, 0x22,
0x7F, 0x41, 0x41, 0x41, 0x3E,
0x7F, 0x49, 0x49, 0x49, 0x41,
0x7F, 0x09, 0x09, 0x09, 0x01,
0x3E, 0x41, 0x41, 0x51, 0x73,
0x7F, 0x08, 0x08, 0x08, 0x7F,
0x00, 0x41, 0x7F, 0x41, 0x00,
0x20, 0x40, 0x41, 0x3F, 0x01,
0x7F, 0x08, 0x14, 0x22, 0x41,
0x7F, 0x40, 0x40, 0x40, 0x40,
0x7F, 0x02, 0x1C, 0x02, 0x7F,
0x7F, 0x04, 0x08, 0x10, 0x7F,
0x3E, 0x41, 0x41, 0x41, 0x3E,
0x7F, 0x09, 0x09, 0x09, 0x06,
0x3E, 0x41, 0x51, 0x21, 0x5E,
0x7F, 0x09, 0x19, 0x29, 0x46,
0x26, 0x49, 0x49, 0x49, 0x32,
0x03, 0x01, 0x7F, 0x01, 0x03,
0x3F, 0x40, 0x40, 0x40, 0x3F,
0x1F, 0x20, 0x40, 0x20, 0x1F,
0x3F, 0x40, 0x38, 0x40, 0x3F,
0x63, 0x14, 0x08, 0x14, 0x63,
0x03, 0x04, 0x78, 0x04, 0x03,
0x61, 0x59, 0x49, 0x4D, 0x43,
0x00, 0x7F, 0x41, 0x41, 0x41,
0x02, 0x04, 0x08, 0x10, 0x20,
0x00, 0x41, 0x41, 0x41, 0x7F,
0x04, 0x02, 0x01, 0x02, 0x04,
0x40, 0x40, 0x40, 0x40, 0x40,
0x00, 0x03, 0x07, 0x08, 0x00,
0x20, 0x54, 0x54, 0x78, 0x40,
0x7F, 0x28, 0x44, 0x44, 0x38,
0x38, 0x44, 0x44, 0x44, 0x28,
0x38, 0x44, 0x44, 0x28, 0x7F,
0x38, 0x54, 0x54, 0x54, 0x18,
0x00, 0x08, 0x7E, 0x09, 0x02,
0x18, 0xA4, 0xA4, 0x9C, 0x78,
0x7F, 0x08, 0x04, 0x04, 0x78,
0x00, 0x44, 0x7D, 0x40, 0x00,
0x20, 0x40, 0x40, 0x3D, 0x00,
0x7F, 0x10, 0x28, 0x44, 0x00,
0x00, 0x41, 0x7F, 0x40, 0x00,
0x7C, 0x04, 0x78, 0x04, 0x78,
0x7C, 0x08, 0x04, 0x04, 0x78,
0x38, 0x44, 0x44, 0x44, 0x38,
0xFC, 0x18, 0x24, 0x24, 0x18,
0x18, 0x24, 0x24, 0x18, 0xFC,
0x7C, 0x08, 0x04, 0x04, 0x08,
0x48, 0x54, 0x54, 0x54, 0x24,
0x04, 0x04, 0x3F, 0x44, 0x24,
0x3C, 0x40, 0x40, 0x20, 0x7C,
0x1C, 0x20, 0x40, 0x20, 0x1C,
0x3C, 0x40, 0x30, 0x40, 0x3C,
0x44, 0x28, 0x10, 0x28, 0x44,
0x4C, 0x90, 0x90, 0x90, 0x7C,
0x44, 0x64, 0x54, 0x4C, 0x44,
0x00, 0x08, 0x36, 0x41, 0x00,
0x00, 0x00, 0x77, 0x00, 0x00,
0x00, 0x41, 0x36, 0x08, 0x00,
0x02, 0x01, 0x02, 0x04, 0x02,
0x3C, 0x26, 0x23, 0x26, 0x3C,
0x1E, 0xA1, 0xA1, 0x61, 0x12,
0x3A, 0x40, 0x40, 0x20, 0x7A,
0x38, 0x54, 0x54, 0x55, 0x59,
0x21, 0x55, 0x55, 0x79, 0x41,
0x22, 0x54, 0x54, 0x78, 0x42, // a-umlaut
0x21, 0x55, 0x54, 0x78, 0x40,
0x20, 0x54, 0x55, 0x79, 0x40,
0x0C, 0x1E, 0x52, 0x72, 0x12,
0x39, 0x55, 0x55, 0x55, 0x59,
0x39, 0x54, 0x54, 0x54, 0x59,
0x39, 0x55, 0x54, 0x54, 0x58,
0x00, 0x00, 0x45, 0x7C, 0x41,
0x00, 0x02, 0x45, 0x7D, 0x42,
0x00, 0x01, 0x45, 0x7C, 0x40,
0x7D, 0x12, 0x11, 0x12, 0x7D, // A-umlaut
0xF0, 0x28, 0x25, 0x28, 0xF0,
0x7C, 0x54, 0x55, 0x45, 0x00,
0x20, 0x54, 0x54, 0x7C, 0x54,
0x7C, 0x0A, 0x09, 0x7F, 0x49,
0x32, 0x49, 0x49, 0x49, 0x32,
0x3A, 0x44, 0x44, 0x44, 0x3A, // o-umlaut
0x32, 0x4A, 0x48, 0x48, 0x30,
0x3A, 0x41, 0x41, 0x21, 0x7A,
0x3A, 0x42, 0x40, 0x20, 0x78,
0x00, 0x9D, 0xA0, 0xA0, 0x7D,
0x3D, 0x42, 0x42, 0x42, 0x3D, // O-umlaut
0x3D, 0x40, 0x40, 0x40, 0x3D,
0x3C, 0x24, 0xFF, 0x24, 0x24,
0x48, 0x7E, 0x49, 0x43, 0x66,
0x2B, 0x2F, 0xFC, 0x2F, 0x2B,
0xFF, 0x09, 0x29, 0xF6, 0x20,
0xC0, 0x88, 0x7E, 0x09, 0x03,
0x20, 0x54, 0x54, 0x79, 0x41,
0x00, 0x00, 0x44, 0x7D, 0x41,
0x30, 0x48, 0x48, 0x4A, 0x32,
0x38, 0x40, 0x40, 0x22, 0x7A,
0x00, 0x7A, 0x0A, 0x0A, 0x72,
0x7D, 0x0D, 0x19, 0x31, 0x7D,
0x26, 0x29, 0x29, 0x2F, 0x28,
0x26, 0x29, 0x29, 0x29, 0x26,
0x30, 0x48, 0x4D, 0x40, 0x20,
0x38, 0x08, 0x08, 0x08, 0x08,
0x08, 0x08, 0x08, 0x08, 0x38,
0x2F, 0x10, 0xC8, 0xAC, 0xBA,
0x2F, 0x10, 0x28, 0x34, 0xFA,
0x00, 0x00, 0x7B, 0x00, 0x00,
0x08, 0x14, 0x2A, 0x14, 0x22,
0x22, 0x14, 0x2A, 0x14, 0x08,
0x55, 0x00, 0x55, 0x00, 0x55, // #176 (25% block) missing in old code
0xAA, 0x55, 0xAA, 0x55, 0xAA, // 50% block
0xFF, 0x55, 0xFF, 0x55, 0xFF, // 75% block
0x00, 0x00, 0x00, 0xFF, 0x00,
0x10, 0x10, 0x10, 0xFF, 0x00,
0x14, 0x14, 0x14, 0xFF, 0x00,
0x10, 0x10, 0xFF, 0x00, 0xFF,
0x10, 0x10, 0xF0, 0x10, 0xF0,
0x14, 0x14, 0x14, 0xFC, 0x00,
0x14, 0x14, 0xF7, 0x00, 0xFF,
0x00, 0x00, 0xFF, 0x00, 0xFF,
0x14, 0x14, 0xF4, 0x04, 0xFC,
0x14, 0x14, 0x17, 0x10, 0x1F,
0x10, 0x10, 0x1F, 0x10, 0x1F,
0x14, 0x14, 0x14, 0x1F, 0x00,
0x10, 0x10, 0x10, 0xF0, 0x00,
0x00, 0x00, 0x00, 0x1F, 0x10,
0x10, 0x10, 0x10, 0x1F, 0x10,
0x10, 0x10, 0x10, 0xF0, 0x10,
0x00, 0x00, 0x00, 0xFF, 0x10,
0x10, 0x10, 0x10, 0x10, 0x10,
0x10, 0x10, 0x10, 0xFF, 0x10,
0x00, 0x00, 0x00, 0xFF, 0x14,
0x00, 0x00, 0xFF, 0x00, 0xFF,
0x00, 0x00, 0x1F, 0x10, 0x17,
0x00, 0x00, 0xFC, 0x04, 0xF4,
0x14, 0x14, 0x17, 0x10, 0x17,
0x14, 0x14, 0xF4, 0x04, 0xF4,
0x00, 0x00, 0xFF, 0x00, 0xF7,
0x14, 0x14, 0x14, 0x14, 0x14,
0x14, 0x14, 0xF7, 0x00, 0xF7,
0x14, 0x14, 0x14, 0x17, 0x14,
0x10, 0x10, 0x1F, 0x10, 0x1F,
0x14, 0x14, 0x14, 0xF4, 0x14,
0x10, 0x10, 0xF0, 0x10, 0xF0,
0x00, 0x00, 0x1F, 0x10, 0x1F,
0x00, 0x00, 0x00, 0x1F, 0x14,
0x00, 0x00, 0x00, 0xFC, 0x14,
0x00, 0x00, 0xF0, 0x10, 0xF0,
0x10, 0x10, 0xFF, 0x10, 0xFF,
0x14, 0x14, 0x14, 0xFF, 0x14,
0x10, 0x10, 0x10, 0x1F, 0x00,
0x00, 0x00, 0x00, 0xF0, 0x10,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
0xFF, 0xFF, 0xFF, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFF,
0x0F, 0x0F, 0x0F, 0x0F, 0x0F,
0x38, 0x44, 0x44, 0x38, 0x44,
0xFC, 0x4A, 0x4A, 0x4A, 0x34, // sharp-s or beta
0x7E, 0x02, 0x02, 0x06, 0x06,
0x02, 0x7E, 0x02, 0x7E, 0x02,
0x63, 0x55, 0x49, 0x41, 0x63,
0x38, 0x44, 0x44, 0x3C, 0x04,
0x40, 0x7E, 0x20, 0x1E, 0x20,
0x06, 0x02, 0x7E, 0x02, 0x02,
0x99, 0xA5, 0xE7, 0xA5, 0x99,
0x1C, 0x2A, 0x49, 0x2A, 0x1C,
0x4C, 0x72, 0x01, 0x72, 0x4C,
0x30, 0x4A, 0x4D, 0x4D, 0x30,
0x30, 0x48, 0x78, 0x48, 0x30,
0xBC, 0x62, 0x5A, 0x46, 0x3D,
0x3E, 0x49, 0x49, 0x49, 0x00,
0x7E, 0x01, 0x01, 0x01, 0x7E,
0x2A, 0x2A, 0x2A, 0x2A, 0x2A,
0x44, 0x44, 0x5F, 0x44, 0x44,
0x40, 0x51, 0x4A, 0x44, 0x40,
0x40, 0x44, 0x4A, 0x51, 0x40,
0x00, 0x00, 0xFF, 0x01, 0x03,
0xE0, 0x80, 0xFF, 0x00, 0x00,
0x08, 0x08, 0x6B, 0x6B, 0x08,
0x36, 0x12, 0x36, 0x24, 0x36,
0x06, 0x0F, 0x09, 0x0F, 0x06,
0x00, 0x00, 0x18, 0x18, 0x00,
0x00, 0x00, 0x10, 0x10, 0x00,
0x30, 0x40, 0xFF, 0x01, 0x01,
0x00, 0x1F, 0x01, 0x01, 0x1E,
0x00, 0x19, 0x1D, 0x17, 0x12,
0x00, 0x3C, 0x3C, 0x3C, 0x3C,
0x00, 0x00, 0x00, 0x00, 0x00  // #255 NBSP
};

/*********************************************************************
* Class
*********************************************************************/
class  INTRFC {
  public:
#ifndef wrReg8
    void        wrReg8(uint16_t a, uint8_t d) {wrReg8inline(a, d);};
#endif
#ifndef wrReg16
    void        wrReg16(uint16_t a, uint16_t d) {wrReg16inline(a, d);};
#endif
#ifndef wrReg32
    void        wrReg32(uint16_t a, uint32_t d) {wrReg32inline(a, d);};
#endif
    uint8_t     rdReg8(uint16_t  r);
    uint16_t    rdReg16(uint16_t r);
    uint32_t    rdReg32(uint16_t r);
#ifndef setReadDir
    void        setReadDir(void) { setReadDirInline();};
#endif
#ifndef setWriteDir
    void        setWriteDir(void) { setWriteDirInline();};
#endif
#ifndef read8fn
    uint8_t     read8fn(void) { uint8_t result; read8inline(result); return result;};
    #define  read8isFunctionalized
#endif
#ifndef readport8fn
    uint8_t     readport8fn(void) { uint8_t result; readport8inline(result); return result;};
    #define  readport8isFunctionalized
#endif
    void        GetMemBuff(uint32_t address, uint8_t * buff, uint16_t length);
    uint8_t     GetMem(uint32_t address);
    void        PutMemBuff(uint32_t address, uint8_t * buff, uint16_t length);
    void        SetAddress(uint32_t  r) { WR_CD_ACTIVE; RD_IDLE; write8(0x80|(r)>>16); write8((r)>>8); write8(r); WR_IDLE;};
    void        WriteData(uint16_t v) { WR_ACTIVE; RD_CD_IDLE; write8((v)>>8); write8(v); WR_IDLE;};
    void        WriteData32(uint32_t v) { WR_ACTIVE; RD_CD_IDLE; write8((v)>>24); write8((v)>>16); write8((v)>>8); write8(v); WR_IDLE;};
    void        I2C_Init(void) { wrReg8(0x235, 0x00); wrReg8(0x233, MASK_I2C_BAUD); wrReg8(0x232, 0x03); wrReg8(0x232, 0x01);};
    void        I2C_SetID(uint8_t  i2c_address) { _I2C_address = i2c_address;};
    void        I2C_Ctl(uint8_t code) { if( I2C_Wait()==0)  wrReg8(0x231, code);};
    uint8_t     I2C_Wait(void) { uint16_t to=65535; while((!(rdReg8(0x234)&0x80))&&(to--)); if (rdReg8(0x234)&0x80) return 0; else return -1;};
    void        I2C_Write(uint8_t byte) { wrReg8(0x230, byte);};
    uint8_t     I2C_Read(void) {uint32_t timeout=0xFFFFFFFF; uint8_t data; wrReg8(0x230, 0xFF); while((!(rdReg8(0x236)&0x01))&&(timeout--));
                                if (rdReg8(0x236)&0x01) data=rdReg8(0x237); else data =-1; return data;};

    uint8_t     _I2C_address;
    PREVIEW_PARAM _param;
    uint16_t    _color;
    uint16_t     max_x;
    uint16_t     max_y;
};


/*********************************************************************
* Class
*********************************************************************/
class EKATFT:INTRFC {
  public:
    EKATFT(uint8_t d) { OUT_DIR_SIGNAL; CD_DATA; CS_IDLE; RD_IDLE; WR_IDLE; RST_IDLE; init();};
    EKATFT(void) { OUT_DIR_SIGNAL; CD_DATA; CS_IDLE; RD_IDLE; WR_IDLE; RST_IDLE; init();};
#ifdef EKA_TFT_VER_4
    void        begin(uint16_t id = 0) { begin(id,0,0,0,1);};
    void        begin(uint16_t id, int8_t shift) { begin(id,shift,0,0,1);};
#else
    void        begin(uint16_t id = 0) { begin(id,0,0,0,2);};
    void        begin(uint16_t id, int8_t shift) { begin(id,shift,0,0,2);};
#endif
    void        begin(uint16_t id, int8_t shift, uint8_t mirr_h, uint8_t mirr_v) { begin(id,shift,mirr_h,mirr_v,1);};
    void        begin(uint16_t id, int8_t shift, uint8_t rotate) { begin(id,shift,0,0,rotate);};
    void        begin(uint16_t id, int8_t shift, uint8_t mirr_h, uint8_t mirr_v, uint8_t rotate);
#if defined (EKA_TFT_VER_2) || defined (EKA_TFT_VER_3)   // 320x240 TFT Arduino Nano
    void        LCD_SendCommand(uint8_t cmd) {wrReg8(0x26e,0x00);wrReg16(0x26c,cmd);};
    void        LCD_SendData(uint8_t data) {wrReg8(0x26e,0x01);wrReg16(0x26c,data);};
    void        LCD_SetWriteModeSPI(uint8_t mode) {if(mode==0) wrReg8(0x260,0xC8);else if(mode==1) wrReg8(0x260,0x48);};
    void        LCD_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
#endif // EKA_TFT_VER_2   // 320x240 TFT Arduino Nano
    void        reset(void) { WR_RD_CS_IDLE; RST_CD_ACTIVE; RST_ACTIVE; delay(20); RST_IDLE; delay(100); wrReg8(0xA2, 0x01); delay(100);};
    void        PutPixel(int16_t x, int16_t y);
    uint16_t    DrawArc(int16_t xL, int16_t yT, int16_t xR, int16_t yB, int16_t r1, int16_t r2, uint8_t octant);
    uint16_t    DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
    void        DrawBevel(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t rad);
    uint16_t    DrawFillBevel(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t rad);
    void        DrawPoly(int16_t numPoints, int16_t* polyPoints);
    void        DrawFillRect(int16_t left, int16_t top, int16_t right, int16_t bottom);
    void        SetColor(uint16_t color) { _color = color;};
    uint16_t    GetColor(void) { return _color;};
    void        SetRGB(void) { wrReg8(0x1A4, 0xc0);};
    void        SetYUV(void) { wrReg8(0x1A4, 0x00);};
    uint16_t    color565(uint8_t r, uint8_t g, uint8_t b) { return ((r&0xF8)<<8)|((g&0xFC)<<3)|(b>>3);};
    void        MainWndEnable(uint8_t enable) { uint8_t r; r=rdReg8(0x70); if(enable) r=r&0x7F; else r=r|0x80; wrReg8(0x70, r);};
    void        MainWndInit(uint32_t startaddr, uint16_t linewidth, uint16_t bpp, uint8_t orient, uint8_t rgb);
    void        FloatWndInit(uint32_t startaddr, uint16_t linewidth, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t rgb);
    void        FloatWndEnable(bool enable) { if(enable==TRUE) wrReg8(0x71, rdReg8(0x71)|0x10); else wrReg8(0x71,rdReg8(0x71)&~0x10);};
    void        FocusWnd(uint8_t wnd);
    void        ClearDevice(void) { uint32_t i; for(i=0; i<(max_y+1); i++) { DrawLine(0, i, max_x+1, i);}};
    void        SetFont(const GFXfont * f);
#if defined(ESP32)
    uint16_t    OutText(const char * textString);
#else
    uint16_t    OutText(unsigned char * textString);
#endif
    void        OutChar(unsigned char ch);
#if defined(ESP32)
    int16_t     GetTextWidth(const char * textString, const void* font);
#else
    int16_t     GetTextWidth(char * textString, void * font);
#endif
    int16_t     GetTextHeight(void * font);
#if defined(ESP32)
    uint16_t    OutTextXY(int16_t x, int16_t y, const char * textString);
#else
    uint16_t    OutTextXY(int16_t x, int16_t y, char * textString);
#endif
    uint16_t     GetMaxX(void) {return  max_x;};
    uint16_t     GetMaxY(void) {return  max_y;};
#ifndef gpio_bl
    void        gpio_bl(uint8_t a) {gpio_blInline(a);};
#endif
#ifndef gpio_rst
    void        gpio_rst(uint8_t a) {gpio_sprstInline(a);};
#endif
#ifdef EKA_TFT_VER_1
#ifndef scanButtons
    uint8_t     scanButtons(void) {uint8_t result; scanButtonsInline(result); return ((~result)&0x1F);};
#endif
#endif // EKA_TFT_VER_1
    // Data
    uint16_t    _color;
    uint8_t     _page;
    uint32_t    _line_mem_pitch;
    uint16_t    _clipRgn;            // Clipping region control
    uint16_t    _clipLeft;           // Clipping region borders
    uint16_t    _clipTop;
    uint16_t    _clipRight;
    uint16_t    _clipBottom;
    uint8_t     _fontOrientation;
    int16_t     _fontHeight;         // Installed font height
    uint16_t    _cursorX;            // Current cursor x-coordinates
    uint16_t    _cursorY;            // Current cursor y-coordinates
    uint16_t    _lineType;           // Current line type
    uint16_t    _lineThickness;      // Current line thickness
    bool        _panelSelect = 1;
    bool        _pause = 0;

 private:

    void        SetPanel(bool panel) {_panelSelect = panel;};
    bool        GetPanel(void) { return (_panelSelect);};
    void        init(void) { setWriteDir();};
#ifndef write8
    void        write8(uint8_t value) { write8inline(value);};
#endif
#ifndef gpio_sprst
    void        gpio_sprst(uint8_t a) { gpio_sprstInline(a);};
#endif
#ifndef EKA_TFT_VER_2   // 320x240 TFT Arduino Nano
#ifndef gpio_spena
    void        gpio_spena(uint8_t a) { gpio_spenaInline(a);};
#endif
#ifndef gpio_spclk
    void        gpio_spclk(uint8_t a) { gpio_spclkInline(a);};
#endif
#ifndef gpio_spdat
    void        gpio_spdat(uint8_t a) { gpio_spdatInline(a);};
#endif
#ifndef spi_write
    void        spi_write(uint8_t  a) { spi_writeInline(a);};
#endif
#ifndef spi_setregw
    void        spi_setregw(uint8_t a, uint16_t b) { spi_setregwInline(a, b);};
#endif
#ifndef spi_setregb
    void        spi_setregb(uint8_t a, uint8_t b) { spi_setregbInline(a, b);};
#endif
#endif // EKA_TFT_VER_2   // 320x240 TFT Arduino Nano
    uint8_t     driver;
    uint8_t     gpioStatus;
    int16_t     cursor_x, cursor_y;
    GFXfont   * gfxFont;
};

/*********************************************************************
* Class DS1307
*********************************************************************/
class  DS1307:INTRFC {
  public:
    uint8_t     isrunning(void);
    bool        read(tmElements_t &tm);
    bool        write(tmElements_t &tm);
    uint8_t     dec2bcd(uint8_t num) { return ((num/10 * 16) + (num % 10));}; // Convert Decimal to Binary Coded Decimal (BCD)
    uint8_t     bcd2dec(uint8_t num) { return ((num/16 * 10) + (num % 16));}; // Convert Binary Coded Decimal (BCD) to Decimal
};

#endif // _EKATFT_H_
