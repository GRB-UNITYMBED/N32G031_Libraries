/**
 * @file    main.c
 * @brief   OLED SSD1306 Display Test for N32G031
 */

#include "n32g031.h"
#include "oled.h"

int main(void)
{
    // 1. Initialize OLED Display (Software I2C)
    OLED_Init();

    // 2. Clear Display Screen
    OLED_Clear();

    // 3. Display "Ready!" in the center of the screen
    // Screen Resolution: 128x64
    // Font 8x16: "Ready!" has 6 chars -> Width = 6 * 8 = 48 px
    // Center X = (128 - 48) / 2 = 40
    // Center Y = (64 - 16) / 2 = 24
    OLED_ShowString(40, 24, "Ready!", 16);

    // Main Loop
    while (1)
    {
        // Infinite loop - Keep displaying "Ready!"
    }
}