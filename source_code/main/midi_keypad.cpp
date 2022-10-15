/**
 * @file      midi_keypad.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Keypad source code.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "midi_keypad.h"

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {45, 43, 41, 39};      // Row Pins
byte colPins[COLS] = {37, 35, 33, 31};      // Col Pins

Keypad midi_keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


midi_message_t midi_get_keypad_reading(void) {

    midi_message_t ret;

    if (midi_keypad.getKeys()) {
        
        for (int i = 0; i < LIST_MAX; i++) {
        
            if (midi_keypad.key[i].stateChanged) {
                
                if (midi_keypad.key[i].kstate == PRESSED) {
                    ret = midi_keypad_message(midi_keypad.key[i].kchar, 'p');
                }

                if (midi_keypad.key[i].kstate == RELEASED)  {
                    ret = midi_keypad_message(midi_keypad.key[i].kchar, 'r');
                }
            }
        }
    
    } else {
        ret.status = -1;
    }

    return ret;
}


midi_message_t midi_keypad_message(char target_key, char state){

    midi_message_t ret;

    int status_byte = MIDI_STATUS_NOTE_ON;
    int velocity = 127;

    if(state == 'r'){
        status_byte = MIDI_STATUS_NOTE_OFF;
        velocity = 0;
    }

    ret.status = status_byte;
    ret.data2 = velocity;

    switch (target_key) {
        case '1':
            ret.data1 = NOTE_MID_C + 0;
            break;
        
        case '2':
            ret.data1 = NOTE_MID_C + 1;
            break;
        
        case '3':
            ret.data1 = NOTE_MID_C + 2;
            break;
        
        case '4':
            ret.data1 = NOTE_MID_C + 3;
            break;
        
        case '5':
            ret.data1 = NOTE_MID_C + 4;
            break;
        
        case '6':
            ret.data1 = NOTE_MID_C + 5;
            break;
        
        case '7':
            ret.data1 = NOTE_MID_C + 6;
            break;
        
        case '8':
            ret.data1 = NOTE_MID_C + 7;
            break;
        
        case '9':
            ret.data1 = NOTE_MID_C + 8;
            break;
        
        case 'S':
            ret.data1 = NOTE_MID_C + 9;
            break;
        
        case '0':
            ret.data1 = NOTE_MID_C + 10;
            break;
        
        case 'P':
            ret.data1 = NOTE_MID_C + 11;
            break;

        case 'A':
            ret.data1 = NOTE_MID_C + 12;
            break;
        
        case 'B':
            ret.data1 = NOTE_MID_C + 13;
            break;
        
        case 'C':
            ret.data1 = NOTE_MID_C + 14;
            break;
        
        case 'D':
            ret.data1 = NOTE_MID_C + 15;
            break;
    }

    return ret;
}



void task_midi_keypad(void *p){

    int ret;
    midi_message_t tx_midi_msg;
    
    while(1){
        
        tx_midi_msg = midi_get_keypad_reading();

        if(tx_midi_msg.status != -1){
            // midi_send_msg(transmit);
            ret = xQueueSendToBack(q_midi_cmd_handle, &tx_midi_msg, 1000);
        }

        vTaskDelay(30/portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}