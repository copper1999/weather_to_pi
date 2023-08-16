#include <wiringPi.h>
#include "curl/curl.h"
#include "st7735.h"
#include <string>
#include <iostream>

#define PIN 3
#define TFT_RST 6
#define TFT_DC 5

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_DC, TFT_RST);

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t total_size = size * nmemb;
    std::string *response_data = static_cast<std::string *>(userp);
    response_data->append(static_cast<char *>(contents), total_size);
    return total_size;
}

void setup()
{
    wiringPiSetup();
    // tft.initR(INITR_144GREENTAB); //for 1,44'
    tft.initR(INITR_BLACKTAB); // for 1.8'
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
    tft.fillRect(10, 10, ST7735_TFTWIDTH_128 - 20, ST7735_TFTHEIGHT_160 - 20, ST7735_WHITE); // for 1.8'
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

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl)
    {
        std::string response_data; // To store response data

        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openweathermap.org/data/2.5/weather?q=London&appid=c827243ba6976f602b0a6558865c491c");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); // Set callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);    // Pass response_data pointer

        res = curl_easy_perform(curl);

        if (res == CURLE_OK)
        {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            if (response_code == 200)
            {
                std::cout << "Response:\n"
                          << response_data << std::endl;
                tft.drawString(response_data.c_str(), ST7735_GREEN, 1);
                delay(1000);
            }
            else
            {
                std::cout << "HTTP Response Error: " << response_code << std::endl;
            }
        }
        else
        {
            std::cout << "Curl Error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return 0;
}
