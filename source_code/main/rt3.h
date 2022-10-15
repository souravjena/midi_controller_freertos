/**
 * @file      rt3.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Headerfile for RT3.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef RT3_H
#define RT3_H

#include "main.h"
#include "fft.h"
#include "midi.h"
#include "midi_pot.h"
#include "midi_keypad.h"
#include "midi_ultrasonic.h"
#include "midi_lcd.h"

/**
 * @brief FreeRTOS task to perform RT3.
 * 
 * @param p Pointer to the parameters to be passed to the FreeRTOS task if any. 
 */
void task_rt3(void *p);

/**
 * @brief FreeRTOS task to perform RT3p0.
 * 
 * @param p Pointer to the parameters to be passed to the FreeRTOS task if any. 
 */
void task_rt3p0(void *p);


/**
 * @brief FreeRTOS task to perform RTp1 i.e to send vReal and vImg data buffer addresses to RT4.
 * 
 * @param p Pointer to the parameters to be passed to the FreeRTOS task if any.
 */
void task_rt3p1(void *p);

#endif