#include "usrDef_functions.h"


/***************************************************************
    System Configs
***************************************************************/
#define __dataPin       13
#define __LED_amount    60
#define __brightness    80
#define __LED_type      WS2812
#define __colorOrder    GRB
#define __refreshRate   100


/***************************************************************
    Instancings
***************************************************************/
CRGB g_LEDs[__LED_amount];

uint32_t g_colorBand_1[12] = {
    0xFF0000, 0xFF6A00, 0xFFD000,
    0xAAFF00, 0x15FF00, 0x00FF8C,
    0x00F7FF, 0x0044FF, 0x5100FF,
    0xC800FF, 0xFF00A2, 0xFF003C
};

uint32_t g_colorBand_2[6] = {
    0xFF0000, 0xFF003C, 0x0044FF, 0x00FF00, 0x000000, 0x0000FF
};


/***************************************************************
    Setup
***************************************************************/
void setup() {
    Serial.begin(9600);

    delay(3000);
    FastLED.addLeds<__LED_type,
                    __dataPin,
                    __colorOrder>(g_LEDs,
                    __LED_amount).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(__brightness);
}


/***************************************************************
    Main Loop
***************************************************************/
void loop() {
    // __paintBand_lag(g_LEDs, 0, 59, g_colorBand_1, 12);
    // __paintLEDs_lag(g_LEDs, 0, 59, 0);

    // __colorsBreathing(g_LEDs, 0, 59, g_colorBand_1, 12);

    // __FX_policeBeacon_bar2(g_LEDs, 0, 59, 3, 100);

    // __paintLEDs_now(g_LEDs, 0, 59, __combineRGB(0xFF, 0x00, 0xFF));

    __colorsShifting(g_LEDs, 0, 59, 1, g_colorBand_2, 6, 30);
}