/**
 * @file      midi_lcd.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Header file for the LCD.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef MIDI_LCD_H
#define MIDI_LCD_H

#include "midi.h"
#include "LiquidCrystal.h"

/**
 * @brief Initialized the LCD.
 * 
 */
void midi_lcd_init();


/**
 * @brief Waits for user to enter the correct password.
 * 
 */
void midi_lcd_get_password(void);

/**
 * @brief Prints welcome message on the LCD.
 * 
 */
void midi_lcd_welcome();


/**
 * @brief FreeRTOS task to print welcome message on the LCD
 * 
 * @param p Input parameter for the FreeRTOS task, if any.
 */
void task_midi_lcd(void *p);

#endif