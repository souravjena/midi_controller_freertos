/**
 * @file      rt4.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Source code of RT4.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "rt4.h"

void task_rt4(void *p){

    int ret;

    fft_buffer_t *rx_t2;
    time_t elasped;
    time_t *tx_t2 = &elasped;

    static int i = 1;
    double fft_ans;

    while(1){

        ret = xQueueReceive(q_handle_buffer, &rx_t2, 1000);

        if(ret == pdTRUE){
          // Serial.print("[T2 Rx] Received: ");
          // Serial.println(rx_t2->arr_real[0]);
        
        } else {
            // Serial.println("[T2 Rx] Failed!\n\n");
        
        }

        // Do FFT
        TickType_t ticks_start = xTaskGetTickCount();
        uint32_t time_start = millis();

        fft_ans = fft_get(rx_t2->arr_real, rx_t2->arr_img, samples);
        // vTaskDelay(1000 / portTICK_PERIOD_MS); 

        // Serial.print(fft_ans);
        // Serial.print(" ");
        // Serial.println("[T2] FFT Done!");

        TickType_t ticks_end = xTaskGetTickCount();
        uint32_t time_end = millis();

        elasped.rtos_ticks = ticks_end - ticks_start;
        elasped.time_ms = time_end - time_start;

        ret = xQueueSendToBack(q_handle_signal, &tx_t2, 1000);

        if( ret == pdTRUE ){
          // Serial.print("[T2 Tx] Sent: ");
          // Serial.println(tx_t2->rtos_ticks);
          // Serial.println(tx_t2->time_ms);
        
        } else {
            // Serial.println("[T2 Tx] Failed!\n");
        
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);   // create a 1 sec delay
    }

}