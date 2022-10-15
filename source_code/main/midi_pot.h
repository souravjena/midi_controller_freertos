/**
 * @file      midi_pot.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Header file for the potentiometer.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef MIDI_POT_H
#define MIDI_POT_H

#include "midi.h"

#define THRESHOLD   30
#define PIN_POT     A4

/**
 * @brief Returns stabilized pot reading.
 * 
 * @return midi_message_t Returns pot reading in MIDI message format.
 */
midi_message_t midi_get_pot_reading(void);

/**
 * @brief FreeRTOS task to read the pot.
 * 
 * @param p Pointer to the parameters to be passed to the task if any.
 */
void task_midi_pot(void *p);

#endif