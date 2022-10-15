/**
 * @file      rt1.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Headerfile for RT1.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef RT1_H
#define RT1_H

#include "Arduino.h"
#include <Arduino_FreeRTOS.h>

#define LED_RED     49

/**
 * @brief FreeRTOS task to perform RT1 which is to blink an external LED.
 * 
 * @param pvParameters Pointer to the parameter to be passed to the FreeRTOS task, if any.
 */
void task_rt1(void *pvParameters);

#endif