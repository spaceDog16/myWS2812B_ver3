#ifndef _USRDEF_FUNCTIONS_H_
#define _USRDEF_FUNCTIONS_H_

#include <Arduino.h>
#include <FastLED.h>

/*
    @brief Combine 3 separate R, G, B values into 1 hex code.
    @param red Value of red.
    @param green Value of green.
    @param blue Value of blue.
    @return The combined RGB value (Example: F2612E).
*/
uint32_t __combineRGB(uint8_t red, uint8_t green, uint8_t blue);

/*
    @brief Extract R, G, B values from combined hex code.
    @param RGB The color value to extract from.
    @param whichColorToSeparate Choose which value to extract, type 'R', 'G', or 'B' to extract the corresponding colors.
    @return The extracted R, G, or B value (Example: RGB = 0xF800E2, whichColorToExtract = 'R' => 0xF8).
*/
uint8_t __separateRGB(uint32_t RGB, uint8_t whichColorToSeparate);

/*
    @brief Paint and display LEDs all at once.
    @param LEDStrip The LED strip to paint to.
    @param startLED The first LED to paint to.
    @param endLED The final LED to paint to.
    @param color The color to paint to the LEDs.
    @return Nothing.
*/
void __paintLEDs_now(CRGB *LEDStrip,
                     uint16_t startLED, uint16_t endLED,
                     uint32_t color);

/*
    @brief Paint and display LEDs one by one.
    @param LEDStrip The LED strip to paint to.
    @param startLED The first LED to paint to.
    @param endLED The final LED to paint to.
    @param color The color to paint to the LEDs.
    @param lagTime_ms The delay between each LED in milliseconds.
    @return Nothing.
*/
void __paintLEDs_lag(CRGB *LEDStrip,
                     uint16_t startLED, uint16_t endLED,
                     uint32_t color, uint32_t lagTime_ms = 10);

/*
    @brief Paint and display LEDs with multiple colors, all at once.
    @param LEDStrip The LED strip to paint to.
    @param startLED The first LED to paint to.
    @param endLED The final LED to paint to.
    @param colorBand The color band to paint to the LEDs.
    @param howManyColors The amount of different colors in the band.
    @param LEDsPerColor The number of LEDs for each color in the band. If left default at 0, it will be automatically calculated.
    @return Nothing.
*/
void __paintBand_now(CRGB *LEDStrip,
                     uint16_t startLED, uint16_t endLED,
                     uint32_t *colorBand,
                     uint16_t howManyColors,
                     uint16_t LEDsPerColor = 0);

/*
    @brief Paint and display LEDs with multiple colors, one by one.
    @param LEDStrip The LED strip to paint to.
    @param startLED The first LED to paint to.
    @param endLED The final LED to paint to.
    @param colorBand The color band to paint to the LEDs.
    @param howManyColors The amount of different colors in the band.
    @param lagTime_ms The delay between each LED in milliseconds.
    @param LEDsPerColor The number of LEDs for each color in the band. If left default at 0, it will be automatically calculated.
    @return Nothing.
*/
void __paintBand_lag(CRGB *LEDStrip,
                     uint16_t startLED, uint16_t endLED,
                     uint32_t *colorBand, uint16_t howManyColors,
                     uint32_t lagTime_ms = 10,
                     uint16_t LEDsPerColor = 0);

/*
    @brief Glow the LEDs gradually, all at once.
    @param LEDStrip The LED strip to affect.
    @param startLED The first LED to affect.
    @param endLED The final LED to affect.
    @param color The color to paint to the LEDs.
    @param lagTime_ms The breathing FX delay in milliseconds.
    @param maxBrightness The maximum brightness to reach.
    @param minBrightness The minimum brightness to dim to.
    @return Nothing.
*/
void __glowUp(CRGB *LEDStrip,
              uint16_t startLED, uint16_t endLED,
              uint32_t color, uint32_t lagTime_ms,
              uint8_t maxBrightness = 100,
              uint8_t minBrightness = 0);

/*
    @brief Fade the LEDs gradually, all at once.
    @param LEDStrip The LED strip to affect.
    @param startLED The first LED to affect.
    @param endLED The final LED to affect.
    @param color The color to paint to the LEDs.
    @param lagTime_ms The breathing FX delay in milliseconds.
    @param maxBrightness The maximum brightness to reach.
    @param minBrightness The minimum brightness to dim to.
    @return Nothing.
*/
void __fadeAway(CRGB *LEDStrip,
                uint16_t startLED, uint16_t endLED,
                uint32_t color, uint32_t lagTime_ms,
                uint8_t maxBrightness = 100,
                uint8_t minBrightness = 0);

/*
    @brief LEDs FX: Breathing with multiple colors.
    @param LEDStrip The LED strip to affect.
    @param startLED The first LED to affect.
    @param endLED The final LED to affect.
    @param colorBand The color band to affect the LEDs with.
    @param howManyColors The amount of different colors in the band.
    @param lagTime_ms The breathing FX delay in milliseconds.
    @param maxBrightness The maximum brightness to reach.
    @param minBrightness The minimum brightness to dim to.
    @return Nothing.
*/
void __colorsBreathing(CRGB *LEDStrip,
                       uint16_t startLED, uint16_t endLED,
                       uint32_t *colorBand, uint16_t howManyColors,
                       uint32_t lagTime_ms = 10,
                       uint8_t maxBrightness = 100,
                       uint8_t minBrightness = 0);

/*
    @brief LEDs FX: Shifting between multiple colors.
    @param LEDStrip The LED strip to affect.
    @param startLED The first LED to affect.
    @param endLED The final LED to affect.
    @param enableCustomColors If not changed, default color palette is used. Change this to 1 to apply custom colors.
    @param customColorsBank The color bank to affect the LEDs with.
    @param howManyColors The amount of different colors in the bank.
    @param lagTime_ms The shifting FX delay in milliseconds.
    @return Nothing.
*/
void __colorsShifting(CRGB *LEDStrip,
                      uint16_t startLED, uint16_t endLED,
                      uint8_t enableCustomColors = 0,
                      uint32_t *customColorsBank = {0},
                      uint16_t howManyColors = 0,
                      uint32_t lagTime_ms = 50);

/*
    @brief LEDs FX: Police strobing beacon in 2 colors circle.
    @param LEDStrip The LED strip to affect.
    @param startLED The first LED to affect.
    @param endLED The final LED to affect.
    @param color The color to paint to the beam.
    @param beamLength the length of the color beam.
    @param lagTime_ms The delay of beam movement in milliseconds.
    @return Nothing.
*/
void __FX_policeBeacon_circle(CRGB *LEDStrip,
                              uint16_t startLED, uint16_t endLED,
                              uint32_t color = 0x0000FF,
                              uint16_t beamLength = 0,
                              uint32_t lagTime_ms = 0);

/*
    @brief LEDs FX: Police strobing beacon in 2 colors and segments.
    @param LEDStrip The LED strip to affect.
    @param startLED The first LED to affect.
    @param endLED The final LED to affect.
    @param strobeNumber The number of strobes for each color.
    @param lagTime_ms The delay of strobes in milliseconds.
    @param color1 The first color strobe.
    @param color2 The second color strobe.
    @return Nothing.
*/
void __FX_policeBeacon_bar1(CRGB *LEDStrip,
                            uint16_t startLED, uint16_t endLED,
                            uint8_t strobeNumber = 2,
                            uint32_t lagTime_ms = 150,
                            uint32_t color1 = 0x0000FF,
                            uint32_t color2 = 0xFF0000);

/*
    @brief LEDs FX: Police strobing beacon in 2 colors and 4 segments.
    @param LEDStrip The LED strip to affect.
    @param startLED The first LED to affect.
    @param endLED The final LED to affect.
    @param strobeNumber The number of strobes for each color.
    @param lagTime_ms The delay of strobes in milliseconds.
    @param color1 The first color strobe.
    @param color2 The second color strobe.
    @return Nothing.
*/
void __FX_policeBeacon_bar2(CRGB *LEDStrip,
                            uint16_t startLED, uint16_t endLED,
                            uint8_t strobeNumber = 2,
                            uint32_t lagTime_ms = 150,
                            uint32_t color1 = 0x0000FF,
                            uint32_t color2 = 0xFF0000);

#endif /* _USRDEF_FUNCTIONS_H_ */