/**
 * @file    oled.h
 * @brief   OLED SSD1306 API Header
 * @note    This file contains only standard public APIs. 
 *          No project-specific logic or hardware-specific registers here.
 */

#ifndef __OLED_H
#define __OLED_H

#include <stdint.h>

/* ==================================================================== */
/*                      OLED Public API                                 */
/* ==================================================================== */

/**
 * @brief Initialize the OLED Display (SSD1306)
 */
void OLED_Init(void);

/**
 * @brief Clear the entire OLED screen
 */
void OLED_Clear(void);

/**
 * @brief Set the cursor position for drawing text
 * @param x Column address (0 - 127)
 * @param y Page address (0 - 7) -> 1 Page = 8 pixels high
 */
void OLED_SetCursor(uint8_t x, uint8_t y);

/**
 * @brief Display a single character on the OLED
 * @param x    Start column (0 - 127)
 * @param y    Start Y coordinate in pixels
 * @param chr  The character to display (ASCII)
 * @param size Font size (8 for 6x8, 16 for 8x16)
 */
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size);

/**
 * @brief Display a string on the OLED
 * @param x    Start column (0 - 127)
 * @param y    Start Y coordinate in pixels
 * @param chr  Pointer to the string array (null-terminated)
 * @param size Font size (8 for 6x8, 16 for 8x16)
 */
void OLED_ShowString(uint8_t x, uint8_t y, const char *chr, uint8_t size);

#endif /* __OLED_H */