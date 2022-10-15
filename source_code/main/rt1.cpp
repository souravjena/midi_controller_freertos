/**
 * @file      rt1.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Source file for RT1 task.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "rt1.h"

void task_rt1(void *pvParameters){

    pinMode(LED_RED, OUTPUT);

    while(1) {
        digitalWrite(LED_RED, HIGH);        // turn the LED on (HIGH is the voltage level)
        vTaskDelay(100/portTICK_PERIOD_MS);    // wait for 100 ms
        
        digitalWrite(LED_RED, LOW);         // turn the LED off by making the voltage LOW
        vTaskDelay(200/portTICK_PERIOD_MS);    // wait for 200 ms
    }

    vTaskDelete(NULL);
}