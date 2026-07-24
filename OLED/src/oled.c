/**
 * @file    oled.c
 * @brief   OLED SSD1306 Software I2C Driver for N32G031
 * @note    Pin connection: SCL -> PB6, SDA -> PB7
 *          Software Bit-Banging (Ultra Stable)
 */

#include "oled.h"
#include "fonts.h"
#include "n32g031.h"
#include "n32g031_gpio.h"
#include "n32g031_rcc.h"

#define OLED_I2C_ADDR   0x78   // SSD1306 8-bit slave address

/* ==================================================================== */
/*                       Software I2C Bit-Banging                       */
/* ==================================================================== */

#define OLED_SCL_HIGH()   GPIO_SetBits(GPIOB, GPIO_PIN_6)
#define OLED_SCL_LOW()    GPIO_ResetBits(GPIOB, GPIO_PIN_6)

#define OLED_SDA_HIGH()   GPIO_SetBits(GPIOB, GPIO_PIN_7)
#define OLED_SDA_LOW()    GPIO_ResetBits(GPIOB, GPIO_PIN_7)

static void OLED_I2C_Delay(void)
{
    for(volatile int i = 0; i < 20; i++);
}

static void OLED_I2C_Start(void)
{
    OLED_SDA_HIGH();
    OLED_SCL_HIGH();
    OLED_I2C_Delay();
    OLED_SDA_LOW();
    OLED_I2C_Delay();
    OLED_SCL_LOW();
    OLED_I2C_Delay();
}

static void OLED_I2C_Stop(void)
{
    OLED_SDA_LOW();
    OLED_SCL_HIGH();
    OLED_I2C_Delay();
    OLED_SDA_HIGH();
    OLED_I2C_Delay();
}

static void OLED_I2C_SendByte(uint8_t byte)
{
    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        if(byte & 0x80)
            OLED_SDA_HIGH();
        else
            OLED_SDA_LOW();
            
        OLED_I2C_Delay();
        OLED_SCL_HIGH();
        OLED_I2C_Delay();
        OLED_SCL_LOW();
        OLED_I2C_Delay();
        byte <<= 1;
    }
    
    // Clock cycle for ACK (Ignore ACK to prevent hanging)
    OLED_SDA_HIGH();
    OLED_I2C_Delay();
    OLED_SCL_HIGH();
    OLED_I2C_Delay();
    OLED_SCL_LOW();
    OLED_I2C_Delay();
}

/* ==================================================================== */
/*                       SSD1306 Core Commands                          */
/* ==================================================================== */

void OLED_WriteCmd(uint8_t cmd)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(OLED_I2C_ADDR);
    OLED_I2C_SendByte(0x00); // Control byte: Command
    OLED_I2C_SendByte(cmd);
    OLED_I2C_Stop();
}

void OLED_WriteDat(uint8_t dat)
{
    OLED_I2C_Start();
    OLED_I2C_SendByte(OLED_I2C_ADDR);
    OLED_I2C_SendByte(0x40); // Control byte: Data
    OLED_I2C_SendByte(dat);
    OLED_I2C_Stop();
}

void OLED_SetCursor(uint8_t x, uint8_t y)
{
    OLED_WriteCmd(0xB0 + y);
    OLED_WriteCmd(((x & 0xF0) >> 4) | 0x10);
    OLED_WriteCmd((x & 0x0F) | 0x00);
}

void OLED_Clear(void)
{
    uint8_t i, n;
    for(i = 0; i < 8; i++)
    {
        OLED_WriteCmd(0xB0 + i);
        OLED_WriteCmd(0x00);
        OLED_WriteCmd(0x10);
        for(n = 0; n < 128; n++)
        {
            OLED_WriteDat(0x00);
        }
    }
}

/* ==================================================================== */
/*                      OLED Public API                                 */
/* ==================================================================== */

void OLED_Init(void)
{
    GPIO_InitType gpio_init;

    // 1. Enable Clock for GPIOB
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);

    // 2. Configure PB6 (SCL) and PB7 (SDA) as Output Open-Drain
    GPIO_InitStruct(&gpio_init);
    gpio_init.Pin        = GPIO_PIN_6 | GPIO_PIN_7;
    gpio_init.GPIO_Mode  = GPIO_MODE_OUTPUT_OD;
    gpio_init.GPIO_Speed = GPIO_SPEED_HIGH;
    gpio_init.GPIO_Pull  = GPIO_PULL_UP;
    GPIO_InitPeripheral(GPIOB, &gpio_init);

    // Idle State
    OLED_SCL_HIGH();
    OLED_SDA_HIGH();

    for(volatile int delay = 0; delay < 50000; delay++);

    // 3. SSD1306 Initialization Sequence
    OLED_WriteCmd(0xAE); // Display OFF
    OLED_WriteCmd(0x20); // Set Memory Addressing Mode
    OLED_WriteCmd(0x10); // Page Addressing Mode
    OLED_WriteCmd(0xb0); // Set Page Start Address
    OLED_WriteCmd(0xc8); // Set COM Output Scan Direction
    OLED_WriteCmd(0x00); // Set low column address
    OLED_WriteCmd(0x10); // Set high column address
    OLED_WriteCmd(0x40); // Set start line address
    OLED_WriteCmd(0x81); // Set contrast control register
    OLED_WriteCmd(0xff); 
    OLED_WriteCmd(0xa1); // Set segment re-map 0 to 127
    OLED_WriteCmd(0xa6); // Set normal display
    OLED_WriteCmd(0xa8); // Set multiplex ratio(1 to 64)
    OLED_WriteCmd(0x3F); 
    OLED_WriteCmd(0xa4); // Output follows RAM content
    OLED_WriteCmd(0xd3); // Set display offset
    OLED_WriteCmd(0x00); // No offset
    OLED_WriteCmd(0xd5); // Set display clock divide ratio/oscillator frequency
    OLED_WriteCmd(0xf0); // Set divide ratio
    OLED_WriteCmd(0xd9); // Set pre-charge period
    OLED_WriteCmd(0x22); 
    OLED_WriteCmd(0xda); // Set com pins hardware configuration
    OLED_WriteCmd(0x12);
    OLED_WriteCmd(0xdb); // Set vcomh
    OLED_WriteCmd(0x20); 
    OLED_WriteCmd(0x8d); // Set DC-DC enable
    OLED_WriteCmd(0x14);
    OLED_WriteCmd(0xaf); // Display ON

    OLED_Clear();
}

void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size)
{
    uint8_t c = chr - ' ';
    uint8_t i = 0;
    
    if(x > 128 - 1) { x = 0; y += 2; }
    
    if(size == 16)
    {
        OLED_SetCursor(x, y / 8);
        for(i = 0; i < 8; i++) OLED_WriteDat(F8X16[c * 16 + i]);
        OLED_SetCursor(x, (y / 8) + 1);
        for(i = 0; i < 8; i++) OLED_WriteDat(F8X16[c * 16 + i + 8]);
    }
    else
    {
        OLED_SetCursor(x, y / 8);
        for(i = 0; i < 6; i++) OLED_WriteDat(F6x8[c][i]);
    }
}

void OLED_ShowString(uint8_t x, uint8_t y, const char *chr, uint8_t size)
{
    uint8_t j = 0;
    while(chr[j] != '\0')
    {
        OLED_ShowChar(x, y, chr[j], size);
        if(size == 16) x += 8;
        else           x += 6;
        
        if(x > 120) { x = 0; y += 2; }
        j++;
    }
}