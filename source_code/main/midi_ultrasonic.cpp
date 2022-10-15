/**
 * @file      midi_ultrasonic.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Source code for Ultrasonic
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "midi_ultrasonic.h"

uint16_t total_time_taken; 
uint16_t distance; 

void midi_ultrasonic_init(void){
    pinMode(PIN_TRIG, OUTPUT); 
    pinMode(PIN_ECHO, INPUT); 
}


uint16_t midi_ultrasonic_get_dis(void){

    // 1. Make the Trig Pin Low for 2 us
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(2);
    
    // 2. Make the Trig Pin High for 10 us
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    
    // 3. Make the Trig Pin Low
    digitalWrite(PIN_TRIG, LOW);

    // 4. Store the travel time of the sound pulse
    total_time_taken = pulseIn(PIN_ECHO, HIGH);
    
    // 5. Compute the distance using total_time_taken, assuming sound speed to be 340 m/s
    distance = (total_time_taken * 0.034)/2; 
    
    return distance;
}


int16_t midi_ultrasonic_get_note(void){

    uint16_t dis = midi_ultrasonic_get_dis();
    int16_t note;

    if (dis > 80){
        note = -1;
    } else {
        note = map(dis, 0, 100, 0, 10);
        // Serial.println(note);
    }

    return note;
}


midi_message_t midi_ultrasonic_key(void){

    midi_message_t ret;
    int16_t note = midi_ultrasonic_get_note();
    static int16_t note_last = -1;

    if (note == -1 && note_last != -1){
        // NOTE OFF
        ret.status = MIDI_STATUS_NOTE_OFF;
        ret.data1 = note_last;
        ret.data2 = 0;  // velocity
    
    } else if (note != -1){
        // NOTE ON
        ret.status = MIDI_STATUS_NOTE_ON;
        ret.data1 = NOTE_MID_G + 2*note;
        ret.data2 = 127;  // velocity 

        note_last = NOTE_MID_G + 2*note;
    
    } else {

        ret.status = -1;
        ret.data1 = note;
        ret.data2 = 127;  // velocity 

        note_last = note;
    }

    return ret;
}


void task_midi_ultrasonic(void *p){

    int ret;
    midi_message_t tx_midi_msg;
    
    
    
    while(1){
        
        tx_midi_msg = midi_ultrasonic_key();

        if(tx_midi_msg.status != -1){
            ret = xQueueSendToBack(q_midi_cmd_handle, &tx_midi_msg, 1000);
        }

        vTaskDelay(20/portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}