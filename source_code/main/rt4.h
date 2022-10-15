/**
 * @file      rt4.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Headerfile for RT4.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef RT4_H
#define RT4_H

#include "main.h"

/**
 * @brief FreeRTOS task to get data buffer from RT3p1 and pefrom FFT on them.
 * 
 * @param p Pointer to the parameters to be passed to the FreeRTOS task if any.
 */
void task_rt4(void *p);

#endif