/**
 * @file      midi_pot.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Source file for the Potentiometer.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "midi_pot.h"

static int16_t pot_reading_curr = 0;
static int16_t pot_reading_old = 0;
static int16_t  pot_reading_delta = 0;

midi_message_t midi_get_pot_reading(void){

    midi_message_t ret;
    
    ret.status = MIDI_STATUS_CONTROL;
    ret.data1  = 0;
    ret.data2  = 0;
    

    pot_reading_curr = round(analogRead(PIN_POT)/100) * 100;

    pot_reading_delta = pot_reading_curr - pot_reading_old;

    if(abs(pot_reading_delta) > THRESHOLD){
        ret.data2 = map(pot_reading_curr, 0, 1023, 0, 127);
    } else {
        ret.status = -1;
    }

    pot_reading_old = pot_reading_curr;

    delay(2);

    return ret; 
}



void task_midi_pot(void *p){

    int ret;
    midi_message_t tx_midi_msg;
    
    while(1){
        
        tx_midi_msg = midi_get_pot_reading();

        if(tx_midi_msg.status != -1){
            ret = xQueueSendToBack(q_midi_cmd_handle, &tx_midi_msg, 1000);
        }

        vTaskDelay(30/portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}