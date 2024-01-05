#include "usrDef_functions.h"

uint32_t __combineRGB(uint8_t red, uint8_t green, uint8_t blue)
{
    uint32_t RGB;

    RGB = (red * 0x010000) + (green * 0x000100) + (blue * 0x000001);

    return RGB;
}

uint8_t __separateRGB(uint32_t RGB, uint8_t whichColorToSeparate)
{
    uint8_t separatedColor;

    switch (whichColorToSeparate)
    {
        case 'r':
            separatedColor = RGB / 0x010000;
            break;
        case 'g':
            separatedColor = RGB / 0x000100;
            break;
        case 'b':
            separatedColor = RGB / 0x000001;
            break;
        case 'R':
            separatedColor = RGB / 0x010000;
            break;
        case 'G':
            separatedColor = RGB / 0x000100;
            break;
        case 'B':
            separatedColor = RGB / 0x000001;
            break;
        default:
            separatedColor = 0x000000;
            break;
    }

    return separatedColor;
}

void __paintLEDs_now(CRGB *LEDStrip,
                     uint16_t startLED, uint16_t endLED,
                     uint32_t color)
{
    uint16_t LEDsIteration;

    for (LEDsIteration = startLED; LEDsIteration <= endLED; LEDsIteration++)
        LEDStrip[LEDsIteration] = color;
    FastLED.show();
}

void __paintLEDs_lag(CRGB *LEDStrip,
                     uint16_t startLED, uint16_t endLED,
                     uint32_t color, uint32_t lagTime_ms)
{
    uint16_t LEDsIteration;
    uint32_t timeNow;

    for (LEDsIteration = startLED; LEDsIteration <= endLED; LEDsIteration++)
    {
        LEDStrip[LEDsIteration] = color;
        FastLED.show();
        timeNow = millis();
        while (millis() - timeNow <= lagTime_ms) {}
    }
}

void __paintBand_now(CRGB *LEDStrip,
                     uint16_t startLED, uint16_t endLED,
                     uint32_t *colorBand,
                     uint16_t howManyColors,
                     uint16_t LEDsPerColor)
{
    uint16_t LEDsIteration;
    uint16_t colorsIteration;
    uint16_t LEDsFilledWithThisColor;

    if (!LEDsPerColor)
        LEDsPerColor = (endLED - startLED + 1) / howManyColors;

    colorsIteration = 0;
    LEDsFilledWithThisColor = 0;
    for (LEDsIteration = startLED;
         LEDsIteration <= endLED;
         LEDsIteration++)
    {
        LEDStrip[LEDsIteration] = colorBand[colorsIteration];
        LEDsFilledWithThisColor = LEDsFilledWithThisColor + 1;
        if (LEDsFilledWithThisColor == LEDsPerColor)
        {
            LEDsFilledWithThisColor = 0;
            colorsIteration = colorsIteration + 1;
        }
        if (colorsIteration >= howManyColors)
            colorsIteration = 0;
    }
    FastLED.show();
}

void __paintBand_lag(CRGB *LEDStrip,
                     uint16_t startLED, uint16_t endLED,
                     uint32_t *colorBand, uint16_t howManyColors,
                     uint32_t lagTime_ms, uint16_t LEDsPerColor)
{
    uint16_t LEDsIteration;
    uint16_t colorsIteration;
    uint16_t LEDsFilledWithThisColor;
    uint32_t timeNow;

    if (!LEDsPerColor)
        LEDsPerColor = (endLED - startLED + 1) / howManyColors;

    colorsIteration = 0;
    LEDsFilledWithThisColor = 0;
    for (LEDsIteration = startLED;
         LEDsIteration <= endLED;
         LEDsIteration++)
    {
        LEDStrip[LEDsIteration] = colorBand[colorsIteration];
        LEDsFilledWithThisColor = LEDsFilledWithThisColor + 1;
        FastLED.show();
        if (LEDsFilledWithThisColor == LEDsPerColor)
        {
            LEDsFilledWithThisColor = 0;
            colorsIteration = colorsIteration + 1;
        }
        if (colorsIteration >= howManyColors)
            colorsIteration = 0;
        timeNow = millis();
        while (millis() - timeNow <= lagTime_ms) {}
    }
}

void __glowUp(CRGB *LEDStrip,
              uint16_t startLED, uint16_t endLED,
              uint32_t color, uint32_t lagTime_ms,
              uint8_t maxBrightness,
              uint8_t minBrightness)
{
    uint8_t  brightness;
    uint32_t timeNow;

    for (brightness = minBrightness;
         brightness <= maxBrightness;
         brightness++)
    {
        FastLED.setBrightness(brightness);
        __paintLEDs_now(LEDStrip,
                        startLED, endLED,
                        color);
        timeNow = millis();
        while (millis() - timeNow <= lagTime_ms) {}
    }

    timeNow = millis();
    while (millis() - timeNow <= 3 * lagTime_ms) {}
}

void __fadeAway(CRGB *LEDStrip,
                uint16_t startLED, uint16_t endLED,
                uint32_t color, uint32_t lagTime_ms,
                uint8_t maxBrightness,
                uint8_t minBrightness)
{
    int      brightness;
    uint32_t timeNow;

    for (brightness = maxBrightness;
         brightness >= minBrightness;
         brightness--)
    {
        FastLED.setBrightness(brightness);
        __paintLEDs_now(LEDStrip,
                        startLED, endLED,
                        color);
        timeNow = millis();
        while (millis() - timeNow <= lagTime_ms) {}
    }

    timeNow = millis();
    while (millis() - timeNow <= 3 * lagTime_ms) {}
}

void __colorsBreathing(CRGB *LEDStrip,
                       uint16_t startLED, uint16_t endLED,
                       uint32_t *colorBand, uint16_t howManyColors,
                       uint32_t lagTime_ms,
                       uint8_t maxBrightness,
                       uint8_t minBrightness)
{
    uint16_t breathingIteration;

    for (breathingIteration = 0;
         breathingIteration < howManyColors;
         breathingIteration++)
    {
        if (breathingIteration == howManyColors - 1)
            breathingIteration = 0;
        __glowUp(LEDStrip, startLED, endLED,
                 colorBand[breathingIteration], lagTime_ms,
                 maxBrightness, minBrightness);
        __fadeAway(LEDStrip, startLED, endLED,
                   colorBand[breathingIteration], lagTime_ms,
                   maxBrightness, minBrightness);
    }
}

void __colorsShifting(CRGB *LEDStrip,
                      uint16_t startLED, uint16_t endLED,
                      uint8_t enableCustomColors,
                      uint32_t *customColorsBank,
                      uint16_t howManyColors,
                      uint32_t lagTime_ms)
{
    uint8_t  currentRed;
    uint8_t  currentGreen;
    uint8_t  currentBlue;
    uint8_t  targetRed;
    uint8_t  targetGreen;
    uint8_t  targetBlue;
    uint16_t colorIteration;
    uint32_t timeNow;

    if (!enableCustomColors)
    {
        currentRed = 0xFF;
        currentGreen = 0x00;
        currentBlue = 0x00;
        while (currentGreen != 0xFF)
        {
            __paintLEDs_now(LEDStrip, startLED, endLED,
                        __combineRGB(currentRed, currentGreen, currentBlue));
            currentGreen = currentGreen + 3;
            timeNow = millis();
            while (millis() - timeNow <= lagTime_ms) {}
        }
        while (currentRed != 0x00)
        {
            __paintLEDs_now(LEDStrip, startLED, endLED,
                        __combineRGB(currentRed, currentGreen, currentBlue));
            currentRed = currentRed - 3;
            timeNow = millis();
            while (millis() - timeNow <= lagTime_ms) {}
        }
        while (currentBlue != 0xFF)
        {
            __paintLEDs_now(LEDStrip, startLED, endLED,
                        __combineRGB(currentRed, currentGreen, currentBlue));
            currentBlue = currentBlue + 3;
            timeNow = millis();
            while (millis() - timeNow <= lagTime_ms) {}
        }
        while (currentGreen != 0x00)
        {
            __paintLEDs_now(LEDStrip, startLED, endLED,
                        __combineRGB(currentRed, currentGreen, currentBlue));
            currentGreen = currentGreen - 3;
            timeNow = millis();
            while (millis() - timeNow <= lagTime_ms) {}
        }
        while (currentRed != 0xFF)
        {
            __paintLEDs_now(LEDStrip, startLED, endLED,
                        __combineRGB(currentRed, currentGreen, currentBlue));
            currentRed = currentRed + 3;
            timeNow = millis();
            while (millis() - timeNow <= lagTime_ms) {}
        }
        while (currentBlue != 0x00)
        {
            __paintLEDs_now(LEDStrip, startLED, endLED,
                        __combineRGB(currentRed, currentGreen, currentBlue));
            currentBlue = currentBlue - 3;
            timeNow = millis();
            while (millis() - timeNow <= lagTime_ms) {}
        }
    }
    else if (enableCustomColors)
    {
        for (colorIteration = 0;
             colorIteration < howManyColors;
             colorIteration++)
        {
            currentRed = __separateRGB(customColorsBank[colorIteration], 'R');
            currentGreen = __separateRGB(customColorsBank[colorIteration], 'G');
            currentBlue = __separateRGB(customColorsBank[colorIteration], 'B');
            if (colorIteration == howManyColors - 1)
            {
                targetRed = __separateRGB(customColorsBank[0], 'R');
                targetGreen = __separateRGB(customColorsBank[0], 'G');
                targetBlue = __separateRGB(customColorsBank[0], 'B');
            }
            else
            {
                targetRed = __separateRGB(customColorsBank[colorIteration + 1], 'R');
                targetGreen = __separateRGB(customColorsBank[colorIteration + 1], 'G');
                targetBlue = __separateRGB(customColorsBank[colorIteration + 1], 'B');
            }
            while (currentRed != targetRed || currentGreen != targetGreen || currentBlue != targetBlue)
            {
                __paintLEDs_now(LEDStrip, startLED, endLED,
                        __combineRGB(currentRed, currentGreen, currentBlue));
                if (currentRed < targetRed)
                    currentRed++;
                else if (currentRed > targetRed)
                    currentRed--;
                if (currentGreen < targetGreen)
                    currentGreen++;
                else if (currentGreen > targetGreen)
                    currentGreen--;
                if (currentBlue < targetBlue)
                    currentBlue++;
                else if (currentBlue > targetBlue)
                    currentBlue--;
                timeNow = millis();
                while (millis() - timeNow <= lagTime_ms) {}
            }
        }
    }

}
//TODO: Improve this ---------------------------------------
void __FX_policeBeacon_circle(CRGB *LEDStrip,
                              uint16_t startLED, uint16_t endLED,
                              uint32_t color,
                              uint16_t beamLength,
                              uint32_t lagTime_ms)
{
    uint16_t beamStart;
    uint32_t timeNow;

    if (!beamLength)
        beamLength = (endLED - startLED + 1) / 6;
    if (!lagTime_ms)
        lagTime_ms = 500 / (endLED - startLED + 1);

    for (beamStart = startLED; beamStart <= endLED; beamStart++)
    {
        if (beamStart < beamLength)
            __paintLEDs_now(LEDStrip, startLED,
                            beamStart, color);
        else if (endLED - beamStart + 1 <= beamLength)
            __paintLEDs_now(LEDStrip, beamStart,
                            endLED, color);
        else
            __paintLEDs_now(LEDStrip, beamStart,
                            beamStart + beamLength - 1, color);
        if (beamStart >= 1)
            __paintLEDs_now(LEDStrip, startLED, beamStart - 1, 0);
        if (beamStart == endLED)
            __paintLEDs_now(LEDStrip, endLED, endLED, 0);
        timeNow = millis();
        while (millis() - timeNow <= lagTime_ms) {}
    }
}

void __FX_policeBeacon_bar1(CRGB *LEDStrip,
                            uint16_t startLED, uint16_t endLED,
                            uint8_t strobeNumber,
                            uint32_t lagTime_ms,
                            uint32_t color1,
                            uint32_t color2)
{
    uint8_t  strobes;
    uint16_t color1_endLED;
    uint32_t timeNow;

    strobes = strobeNumber;
    color1_endLED = (endLED - startLED + 1) / 2;

    // Color 1 strobe
    while (strobes != 0)
    {
        __paintLEDs_now(LEDStrip, startLED,
                        color1_endLED, color1);
        timeNow = millis();
        while (millis() - timeNow <= lagTime_ms) {}
        __paintLEDs_now(LEDStrip, startLED,
                        color1_endLED, 0x000000);
        strobes--;
        if (strobes != 0)
        {
            timeNow = millis();
            while (millis() - timeNow <= lagTime_ms) {}
        }
    }

    strobes = strobeNumber;

    // Color 2 strobe
    while (strobes != 0)
    {
        __paintLEDs_now(LEDStrip, color1_endLED + 1,
                        endLED, color2);
        timeNow = millis();
        while (millis() - timeNow <= lagTime_ms) {}
        __paintLEDs_now(LEDStrip, color1_endLED + 1,
                        endLED, 0x000000);
        strobes--;
        if (strobes != 0)
        {
            timeNow = millis();
            while (millis() - timeNow <= lagTime_ms) {}
        }
    }
}

void __FX_policeBeacon_bar2(CRGB *LEDStrip,
                            uint16_t startLED, uint16_t endLED,
                            uint8_t strobeNumber,
                            uint32_t lagTime_ms,
                            uint32_t color1,
                            uint32_t color2)
{
    uint8_t  strobes;
    uint16_t quarterLength;
    uint32_t timeNow;

    strobes = strobeNumber;
    quarterLength = (endLED - startLED + 1) / 4;

    while (strobes != 0)
    {
        __paintLEDs_now(LEDStrip,
                        quarterLength, 2 * quarterLength - 1,
                        color1);
        __paintLEDs_now(LEDStrip,
                        2 * quarterLength, 3 * quarterLength - 1,
                        color2);
        timeNow = millis();
        while (millis() - timeNow <= lagTime_ms) {}
        __paintLEDs_now(LEDStrip,
                        quarterLength, 2 * quarterLength - 1,
                        0x000000);
        __paintLEDs_now(LEDStrip,
                        2 * quarterLength, 3 * quarterLength - 1,
                        0x000000);
        strobes--;
        if (strobes != 0)
        {
            timeNow = millis();
            while (millis() - timeNow <= lagTime_ms) {}
        }
    }

    strobes = strobeNumber;

    while (strobes != 0)
    {
        __paintLEDs_now(LEDStrip,
                        startLED, quarterLength - 1,
                        color1);
        __paintLEDs_now(LEDStrip,
                        endLED - quarterLength + 1,
                        endLED,
                        color2);
        timeNow = millis();
        while (millis() - timeNow <= lagTime_ms) {}
        __paintLEDs_now(LEDStrip,
                        startLED, quarterLength - 1,
                        0x000000);
        __paintLEDs_now(LEDStrip,
                        endLED - quarterLength + 1,
                        endLED,
                        0x000000);
        strobes--;
        if (strobes != 0)
        {
            timeNow = millis();
            while (millis() - timeNow <= lagTime_ms) {}
        }
    }
}