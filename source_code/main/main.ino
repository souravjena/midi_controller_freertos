/**
 * @file      main.ino
 * @author    Sourav Jena, Yi Chen
 * @brief     main file for Lab-4
 * @version   1.0
 * @date      2022-06-10
 * 
 */

#include "main.h"
#include "midi.h"
#include "midi_pot.h"
#include "midi_keypad.h"
#include "midi_ultrasonic.h"
#include "midi_lcd.h"

QueueHandle_t q_handle_buffer = NULL;
QueueHandle_t q_handle_signal = NULL;

TaskHandle_t task_rt1_handle = NULL;
TaskHandle_t task_rt2_handle = NULL;
TaskHandle_t task_rt3_handle = NULL;
TaskHandle_t task_rt3p0_handle = NULL;
TaskHandle_t task_rt3p1_handle = NULL;
TaskHandle_t task_rt4_handle = NULL;

void setup(){

    Serial.begin(115200);

    q_midi_cmd_handle = xQueueCreate(10, sizeof(midi_message_t));

    xTaskCreate(
        task_rt1
        , "Blink"   
        , 128       
        , NULL
        , 2         
        , &task_rt1_handle );

    xTaskCreate(
        task_rt2
        , "Speaker"  
        , 128       
        , NULL
        , 2        
        , &task_rt2_handle );

    xTaskCreate(
        task_rt3
        , "task_rt3"   
        , 128       
        , NULL
        , 2        
        , &task_rt3_handle );
    
    xTaskCreate(
        task_rt4
        , "task_rt4"   
        , 1600       
        , NULL
        , 2        
        , &task_rt4_handle );
    vTaskSuspend(task_rt4_handle);


}


void loop(){}