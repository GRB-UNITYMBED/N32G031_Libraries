# 🖥️ OLED Display (SSD1306)

[English](#english) | [ภาษาไทย](#ภาษาไทย)

---

<h2 id="english">🇺🇸 English</h2>

A software I2C library for the SSD1306 OLED Display, specifically for use with the N32G031 microcontroller.

## Default Wiring

| OLED Pin | N32G031 Pin | Description |
| :--- | :--- | :--- |
| **GND** | GND | Ground |
| **VCC** | 3.3V | Power Supply |
| **SCL** | **PB6** | Clock Line |
| **SDA** | **PB7** | Data Line |

## Included Files
Copy these files into your Base Project:
*   `oled.c` -> Place in the `src/` folder
*   `oled.h` -> Place in the `inc/` folder
*   `fonts.h` -> Place in the `inc/` folder

## Quick Test Prompt
Copy and paste this prompt into the UnityMbed AI Assistant to quickly test your screen:

> **Prompt:** "I am using the N32G031 board and Standard Peripheral Library. I have included the custom `oled.h` library. Write a main.c code to initialize the OLED and display the text 'Hello UnityMbed' on the screen. The OLED uses software I2C on pins PB6 (SCL) and PB7 (SDA)."

---

<h2 id="ภาษาไทย">🇹🇭 ภาษาไทย</h2>

ไลบรารีแบบ Software I2C สำหรับหน้าจอ OLED รุ่น SSD1306 สำหรับใช้งานกับไมโครคอนโทรลเลอร์ N32G031 โดยเฉพาะ

## การต่อสาย (Default Wiring)

| ขาจอ OLED | ขา N32G031 | คำอธิบาย |
| :--- | :--- | :--- |
| **GND** | GND | กราวด์ |
| **VCC** | 3.3V | ไฟเลี้ยงบอร์ด |
| **SCL** | **PB6** | สัญญาณนาฬิกา (Clock) |
| **SDA** | **PB7** | สัญญาณข้อมูล (Data) |

## ไฟล์ที่ต้องใช้งาน
ก๊อปปี้ไฟล์เหล่านี้ไปใส่ใน Base Project ของคุณ:
*   `oled.c` -> นำไปวางในโฟลเดอร์ `src/`
*   `oled.h` -> นำไปวางในโฟลเดอร์ `inc/`
*   `fonts.h` -> นำไปวางในโฟลเดอร์ `inc/`

## ตัวอย่างคำสั่ง AI สำหรับทดสอบหน้าจอ (Quick Test Prompt)
ก๊อปปี้ข้อความด้านล่างนี้ไปวางในหน้าต่าง AI Assistant ของ UnityMbed เพื่อทดสอบจอของคุณได้ทันที:

> **Prompt:** "ฉันกำลังใช้บอร์ด N32G031 และ Standard Peripheral Library ฉันได้เพิ่มไลบรารีจอ `oled.h` ไว้แล้ว ช่วยเขียนโค้ด main.c เพื่อเริ่มต้นการทำงานของจอ OLED และแสดงข้อความคำว่า 'Hello UnityMbed' บนหน้าจอให้หน่อย จอ OLED ต่อแบบ Software I2C ที่ขา PB6 (SCL) และ PB7 (SDA)"