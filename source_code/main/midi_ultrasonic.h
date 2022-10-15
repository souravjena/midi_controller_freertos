/**
 * @file      midi_ultrasonic.h
 * @author    Sourav Jena, Yi Chen
 * @brief     headerfile for ultrasonic
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef MIDI_ULTRASONIC_H
#define MIDI_ULTRASONIC_H

#include "midi.h"

#define PIN_ECHO    23 
#define PIN_TRIG    22 


/**
 * @brief Initializes the Ultrasonic Sensor.
 * 
 */
void midi_ultrasonic_init(void);

/**
 * @brief Gets distance from the ultrasonic sensor.
 * 
 * @return uint16_t Distance in cm.
 */
uint16_t midi_ultrasonic_get_dis(void);

/**
 * @brief Maps distance to note.
 * 
 * @return int16_t Note number.
 */
int16_t midi_ultrasonic_get_note(void);


/**
 * @brief Generates midi message for current distance.
 * 
 * @return midi_message_t MIDI message with note information.
 */
midi_message_t midi_ultrasonic_key(void);


/**
 * @brief FreeRTOS task to read ultrasonic sensor.
 * 
 * @param p Pointer to parameters to be passed to the FreeRTOS task if any.
 */
void task_midi_ultrasonic(void *p);

#endif