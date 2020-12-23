#include <U8g2lib.h>

/*
U8g2lib Example Overview:
Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.

This is a frame buffer example.
*/

/* Pin Definitions */

#if defined(__BRD_UNO) || defined(__BRD_MEGA) || defined(__BRD_DUE) || defined(__BRD_GC4) 
  #ifdef __WS_I2C_SW
    #define DSP_SCL           13
    #define DSP_SDA           12
  #endif
#endif

#ifdef __BRD_NUCLEO
  #ifdef __WS_I2C_SW
    #define DSP_SCL           PC0
    #define DSP_SDA           PC1
  #endif
#endif

#ifdef __BRD_FYSETC
  #ifdef __WS_I2C_SW
    #define DSP_SCL           PD2
    #define DSP_SDA           PC3
  #endif
#endif

/* Constructor */
#if defined(__BRD_NUCLEO) || defined(__BRD_UNO) || defined(__BRD_MEGA) || defined(__BRD_DUE) || defined(__BRD_GC4) 
  #if defined( __WS_I2C_HW) && defined(__WS_I2C_SW)
    #error "You ned select only one display"
  #endif
  #if !defined(__WS_I2C_HW) && !defined(__WS_I2C_SW)
    #error "You ned select at least one display"
  #endif

  #ifdef __WS_I2C_HW
    U8G2_SSD1327_WS_128X128_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
  #elif __WS_I2C_SW
    U8G2_SSD1327_WS_128X128_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ DSP_SCL, /* data=*/ DSP_SDA, /* reset=*/ U8X8_PIN_NONE);
  #endif
#endif

#if __BRD_FYSETC
  #if defined(__WS_I2C_HW) &&  defined(__WS_I2C_SW) || defined( __BUNDLED) && defined(__WS_I2C_HW) || defined( __BUNDLED) && defined(__WS_I2C_SW) || defined(__BUNDLED) && defined( __WS_I2C_HW) && defined(__WS_I2C_SW)
    #error "You ned select only one display"
  #endif
  #if !defined(__BUNDLED) && !defined(__WS_I2C_HW) && !defined(__WS_I2C_SW)
    #error "You ned select at least one display"
  #endif

  #ifdef __BUNDLED
    U8G2_UC1701_MINI12864_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ DSP_CS_PIN, /* dc=*/ DSP_DC_PIN, /* reset=*/ DSP_RESET_PIN);
  #elif __WS_I2C_HW
    U8G2_SSD1327_WS_128X128_F_2ND_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
  #elif __WS_I2C_SW
    U8G2_SSD1327_WS_128X128_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ DSP_SCL, /* data=*/ DSP_SDA, /* reset=*/ U8X8_PIN_NONE);
  #endif
#endif

#ifdef __BRD_FYSETC
  void backlit(void) {
    #define DSP_CS_PIN          PB5
    #define DSP_DC_PIN          PA15
    #define DSP_RESET_PIN       PB4

    #define RGB_LED_R_PIN       PB0
    #define RGB_LED_G_PIN       PB6
    #define RGB_LED_B_PIN       PB7

    pinMode(RGB_LED_R_PIN, OUTPUT);
    pinMode(RGB_LED_G_PIN, OUTPUT);
    pinMode(RGB_LED_B_PIN, OUTPUT);

    digitalWrite(RGB_LED_R_PIN, 1);
    digitalWrite(RGB_LED_G_PIN, 1);
    digitalWrite(RGB_LED_B_PIN, 1);
  }
#endif

//#define MINI_LOGO

void setup(void) {
  #ifdef __BRD_FYSETC
    #ifdef __BUNDLED
      afio_cfg_debug_ports(AFIO_DEBUG_NONE);
      backlit();
    #endif
  #endif

  //Serial.begin(9600);
  u8g2.begin();
  #ifdef __BRD_UNO
    u8g2.setFlipMode(0);
  #endif
}

void drawLogo(void) {
  #ifdef __BRD_UNO
    uint8_t mdy = 0;
    if ( u8g2.getDisplayHeight() < 59 )
      mdy = 5;
  #endif
  u8g2.setFontMode(1);  // Transparent
  u8g2.setDrawColor(1);
  #ifdef MINI_LOGO
    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb16_mf);
    u8g2.drawStr(0, 22, "U");

    u8g2.setFontDirection(1);
    u8g2.setFont(u8g2_font_inb19_mn);
    u8g2.drawStr(14,8,"8");

    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb16_mf);
    u8g2.drawStr(36,22,"g");
    u8g2.drawStr(48,22,"\xb2");

    u8g2.drawHLine(2, 25, 34);
    u8g2.drawHLine(3, 26, 34);
    u8g2.drawVLine(32, 22, 12);
    u8g2.drawVLine(33, 23, 12);
  #else
    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb24_mf);
    #ifdef __BRD_UNO
      u8g2.drawStr(0, 30-mdy, "U");
    #else
      u8g2.drawStr(0, 30, "U");
    #endif

    u8g2.setFontDirection(1);
    u8g2.setFont(u8g2_font_inb30_mn);
    #ifdef __BRD_UNO
      u8g2.drawStr(21,8-mdy,"8");
    #else
      u8g2.drawStr(21,8,"8");
    #endif

    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb24_mf);
    #ifdef __BRD_UNO
      u8g2.drawStr(51,30-mdy,"g");
      u8g2.drawStr(67,30-mdy,"\xb2");
    #else
      u8g2.drawStr(51,30,"g");
      u8g2.drawStr(67,30,"\xb2");
    #endif

    #ifdef __BRD_UNO
      u8g2.drawHLine(2, 35-mdy, 47);
      u8g2.drawHLine(3, 36-mdy, 47);
      u8g2.drawVLine(45, 32-mdy, 12);
      u8g2.drawVLine(46, 33-mdy, 12);
    #else
      u8g2.drawHLine(2, 35, 47);
      u8g2.drawHLine(3, 36, 47);
      u8g2.drawVLine(45, 32, 12);
      u8g2.drawVLine(46, 33, 12);
    #endif
  #endif
}

void drawURL(void)
{
#ifndef MINI_LOGO
  u8g2.setFont(u8g2_font_4x6_tr);
  if ( u8g2.getDisplayHeight() < 59 ) {
    u8g2.drawStr(89,20,"github.com");
    u8g2.drawStr(73,29,"/olikraus/u8g2");
  }
  else  {
    u8g2.drawStr(1,54,"github.com/olikraus/u8g2");
  }
#endif
}

//int contrast = 5;
//bool dir = false;

void loop(void) {
  #ifdef __BRD_UNO
    u8g2.firstPage();
    do {
      drawLogo();
      drawURL();
    } while ( u8g2.nextPage() );
    delay(4000);
  #else
    //u8g2.setContrast(contrast);
    u8g2.clearBuffer();
    drawLogo();
    drawURL();
    u8g2.sendBuffer();
    delay(1000);
    //if(contrast >= 250 && !dir)
    // dir = true;
    //if(contrast <=5 && dir)
    // dir = false;
    //if(!dir)
    //  contrast += 5;
    //else
    //  contrast -= 5;

    //Serial.print("Contrast: ");
    //Serial.println(contrast);
  #endif
}
