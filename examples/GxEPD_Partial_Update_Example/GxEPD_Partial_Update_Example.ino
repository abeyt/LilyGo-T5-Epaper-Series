/*
    LilyGo Ink Screen Series Test
        - Created by Lewis he
*/

// According to the board, cancel the corresponding macro definition
// #define LILYGO_T5_V213
// #define LILYGO_T5_V22
// #define LILYGO_T5_V24
// #define LILYGO_T5_V28


#include <boards.h>
#include <GxEPD.h>                          //https://github.com/lewisxhe/GxEPD
#include <SD.h>
#include <FS.h>

// #include <GxGDEH0154D67/GxGDEH0154D67.h>  // 1.54" b/w
// #include <GxDEPG0150BN/GxDEPG0150BN.h>    // 1.54" b/w newer panel

// #include <GxGDEW027W3/GxGDEW027W3.h>      // 2.7" b/w

// #include <GxGDEH0213B72/GxGDEH0213B72.h>  // 2.13" b/w new panel
// #include <GxGDEH0213B73/GxGDEH0213B73.h>  // 2.13" b/w newer panel
// #include <GxDEPG0213BN/GxDEPG0213BN.h>    // 2.13" b/w newer panel

// #include <GxGDEH029A1/GxGDEH029A1.h>      // 2.9" b/w
// #include <GxQYEG0290BN/GxQYEG0290BN.h>    // 2.9" b/w new panel


// The following screens are not supported
// #include <GxGDEW0213Z16/GxGDEW0213Z16.h>  // 2.13" b/w/r
// #include <GxGDEW0154Z04/GxGDEW0154Z04.h>  // 1.54" b/w/r 200x200
// #include <GxGDEW0154Z17/GxGDEW0154Z17.h>  // 1.54" b/w/r 152x152
// #include <GxGDEW027C44/GxGDEW027C44.h>    // 2.7" b/w/r
// #include <GxGDEW029Z10/GxGDEW029Z10.h>    // 2.9" b/w/r
// #include <GxDEPG0290B/GxDEPG0290B.h>      // 2.9" b/w new panel



#include GxEPD_BitmapExamples

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <WiFi.h>

GxIO_Class io(SPI,  EPD_CS, EPD_DC,  EPD_RSET);
GxEPD_Class display(io, EPD_RSET, EPD_BUSY);


void setup(void)
{
    Serial.begin(115200);
    Serial.println();
    Serial.println("setup");
    display.init(); // enable diagnostic output on Serial
    Serial.println("setup done");
}


void loop()
{
// use asymmetric values for test
    uint16_t box_x = 10;
    uint16_t box_y = 15;
    uint16_t box_w = 70;
    uint16_t box_h = 20;
    uint16_t cursor_y = box_y + box_h - 6;
    float value = 13.95;
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setRotation(0);
    // draw background
    display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
    display.update();
    delay(2000);

    // partial update to full screen to preset for partial update of box window
    // (this avoids strange background effects)
    display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, false);

    // show where the update box is
    for (uint16_t r = 0; r < 4; r++) {
        display.setRotation(r);
        display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
        display.updateWindow(box_x, box_y, box_w, box_h, true);
        delay(1000);
        display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
        display.updateWindow(box_x, box_y, box_w, box_h, true);
    }
    // show updates in the update box
    for (uint16_t r = 0; r < 4; r++) {
        // reset the background
        display.setRotation(0);
        display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
        display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, false);
        display.setRotation(r);
        for (uint16_t i = 1; i <= 10; i++) {
            display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
            display.setCursor(box_x, cursor_y);
            display.print(value * i, 2);
            display.updateWindow(box_x, box_y, box_w, box_h, true);
            delay(2000);
        }
        delay(2000);
        display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
        display.updateWindow(box_x, box_y, box_w, box_h, true);
    }
    // should have checked this, too
    box_x = GxEPD_HEIGHT - box_x - box_w - 1; // not valid for all corners
    // should show on right side of long side
    // reset the background
    display.setRotation(0);
    display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
    display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, false);
    // show where the update box is
    for (uint16_t r = 0; r < 4; r++) {
        display.setRotation(r);
        display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
        display.updateWindow(box_x, box_y, box_w, box_h, true);
        delay(1000);
        display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
        display.updateWindow(box_x, box_y, box_w, box_h, true);
    }
    // show updates in the update box
    for (uint16_t r = 0; r < 4; r++) {
        // reset the background
        display.setRotation(0);
        display.drawExampleBitmap(BitmapExample1, 0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, GxEPD_BLACK);
        display.updateWindow(0, 0, GxEPD_WIDTH, GxEPD_HEIGHT, false);
        display.setRotation(r);
        if (box_x >= display.width()) continue; // avoid delay
        for (uint16_t i = 1; i <= 10; i++) {
            display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
            display.setCursor(box_x, cursor_y);
            display.print(value * i, 2);
            display.updateWindow(box_x, box_y, box_w, box_h, true);
            delay(2000);
        }
        delay(2000);
        display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);
        display.updateWindow(box_x, box_y, box_w, box_h, true);
    }
    display.setRotation(0);
    display.powerDown();
    delay(30000);
}
