/**
 * @file      midi.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Source code for general MIDI functions
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "midi.h"


TaskHandle_t task_midi_keypad_handle = NULL;
TaskHandle_t task_midi_ultrasonic_handle = NULL;
TaskHandle_t task_midi_pot_handle = NULL;
TaskHandle_t task_midi_lcd_handle = NULL;
TaskHandle_t task_midi_transmitter_handle = NULL;
TaskHandle_t task_midi_start_handle = NULL;

QueueHandle_t q_midi_cmd_handle = NULL;


void midi_send_msg(midi_message_t transmit){
  Serial.write(transmit.status);
  Serial.write(transmit.data1);
  Serial.write(transmit.data2);
}



void task_midi_transmitter(void *p){

    int ret;
    midi_message_t rx_midi_msg;

    while(1){
        
        ret = xQueueReceive(q_midi_cmd_handle, &rx_midi_msg, 1000);

        if(ret == pdTRUE){
          midi_send_msg(rx_midi_msg);
        } 
    }

}


void midi_init(void){

  midi_ultrasonic_init(); 

  midi_lcd_init();
  midi_lcd_get_password();
  midi_lcd_welcome();

  xTaskCreate(
        task_midi_keypad
        , "MIDI Keypad"   
        , 128       
        , NULL
        , 2         
        , &task_midi_keypad_handle );

    xTaskCreate(
        task_midi_ultrasonic
        , "MIDI Ultrasonic"   
        , 128       
        , NULL
        , 2         
        , &task_midi_ultrasonic_handle );

    xTaskCreate(
        task_midi_pot
        , "MIDI Pot"   
        , 128       
        , NULL
        , 2         
        , &task_midi_pot_handle );

    xTaskCreate(
        task_midi_transmitter
        , "MIDI Tx"  
        , 128       
        , NULL
        , 2        
        , &task_midi_transmitter_handle );

    xTaskCreate(
        task_midi_lcd
        , "MIDI LCD"  
        , 128       
        , NULL
        , 2        
        , &task_midi_lcd_handle );
    // vTaskSuspend(task_midi_lcd_handle);

}