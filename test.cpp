#include <wiringPi.h>
#include "inc/curl/include/curl/curl.h"
#include "st7735.h"

#define PIN 3
#define TFT_RST  6
#define TFT_DC   5

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_DC, TFT_RST);


void setup() {
    wiringPiSetup();
    //tft.initR(INITR_144GREENTAB); //for 1,44'
    tft.initR(INITR_BLACKTAB); //for 1.8'
    
}

int main(void)
{
    setup();
    tft.fillScreen(ST7735_BLACK);
    delay(750);
    tft.fillScreen(ST7735_GREEN);
    delay(750);
    tft.fillScreen(ST7735_RED);
    delay(750);
    tft.fillScreen(ST7735_BLUE);
    delay(750);

    // //tft.fillRect(10, 10,  ST7735_TFTWIDTH_128 - 20, ST7735_TFTHEIGHT_128-20, ST7735_WHITE); //for 1.44'
    tft.fillRect(10, 10,  ST7735_TFTWIDTH_128 - 20, ST7735_TFTHEIGHT_160-20, ST7735_WHITE); //for 1.8'
    delay(750);
    // tft.writePixel(1, 2, ST7735_RED);
	tft.fillScreen(ST7735_BLACK);
	tft.setTextBackground(ST7735_BLACK);
	char hello_1[] = "Hello world !\nHello world !\nHello world !\nHello world !\nHello world !\nHello world !\nHello world !\n";
	tft.drawString(hello_1, ST7735_WHITE, 1);
	delay(1000);
	tft.drawString(hello_1, ST7735_GREEN, 1);
	delay(1000);

	tft.drawString("H", ST7735_BLUE, 1);
	tft.drawString("E", ST7735_BLUE, 1);
	tft.drawString("L", ST7735_WHITE, 1);
	tft.drawString("L", ST7735_WHITE, 1);
	tft.drawString("O", ST7735_RED, 1);
	tft.drawString("!", ST7735_RED, 1);

	delay(750);
   
    

    return 0;
}

 
