/**
 * @file      midi_keypad.h
 * @author    Sourav Jena, Yi Chen
 * @brief     headerfile for the keypad file.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef MIDI_KEYPAD_H
#define MIDI_KEYPAD_H

#include "midi.h"
#include <Keypad.h>

#define ROWS    4
#define COLS    4

extern Keypad midi_keypad;

/**
 * @brief Reads entered key and returns corresponding note.
 * 
 * @return midi_message_t Note corresponding to the key in MIDI format.
 */
midi_message_t midi_get_keypad_reading(void);

/**
 * @brief Returns MIDI message for the target key and state.
 * 
 * @param target_key Which key on the keypad is pressed.
 * @param state Note to be ON or OFF.
 * @return midi_message_t Returns MIDI message which is consumed by the DAW.
 */
midi_message_t midi_keypad_message(char target_key, char state);


/**
 * @brief FreeRTOS Task to read the Keypad and push the corresponding note as MIDI message in a Queue.
 * 
 * @param p Parameters to be passed to the Task if any.
 */
void task_midi_keypad(void *p);

#endif