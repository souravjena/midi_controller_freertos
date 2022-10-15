/**
 * @file      midi.h
 * @author    Sourav Jena, Yi Chen
 * @brief     Headerfile for MIDI.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#ifndef MIDI_H
#define MIDI_H

#include "Arduino.h"
#include <stdint.h>

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <task.h>


#define NOTE_MID_C  60
#define NOTE_MID_G 81

#define MIDI_STATUS_CONTROL     0b10110001
#define MIDI_STATUS_NOTE_ON     0b10010000
#define MIDI_STATUS_NOTE_OFF    0b10000000


extern TaskHandle_t task_midi_keypad_handle;
extern TaskHandle_t task_midi_ultrasonic_handle;
extern TaskHandle_t task_midi_pot_handle;
extern TaskHandle_t task_midi_lcd_handle;
extern TaskHandle_t task_midi_transmitter_handle;
extern TaskHandle_t task_midi_start_handle;

extern QueueHandle_t q_midi_cmd_handle;

struct midi_message {
    int8_t status;
    uint8_t data1;
    uint8_t data2;
};
typedef struct midi_message midi_message_t;

#include "midi_pot.h"
#include "midi_keypad.h"
#include "midi_ultrasonic.h"
#include "midi_lcd.h"


/**
 * @brief Sends midi messsages over UART.
 * 
 * @param transmit MIDI message data to be transmitted.
 */
void midi_send_msg(midi_message_t transmit);

/**
 * @brief FreeRTOS task to read queue for midi messages and then send them over UART.
 * 
 * @param p Pointer to parameters to be passed to the FreeRTOS task if any.
 */
void task_midi_transmitter(void *p);


/**
 * @brief Runs all the MIDI tasks.
 * 
 */
void midi_init(void);

#endif