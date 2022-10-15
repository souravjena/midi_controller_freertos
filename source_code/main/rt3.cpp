/**
 * @file      rt3.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Sourcefile for RT3.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "rt3.h"

void task_rt3(void *p){

    xTaskCreate(
        task_rt3p0
        , "task_rt3p0"   
        , 128       
        , NULL
        , 2        
        , &task_rt3p0_handle );
    

    xTaskCreate(
        task_rt3p1
        , "task_rt3p1"  
        , 1600       
        , NULL
        , 2         
        , &task_rt3p1_handle );
    vTaskSuspend(task_rt3p1_handle); 

    vTaskDelete(NULL);
}


void task_rt3p0(void *p){
    
    fft_generate_samples();

    q_handle_buffer = xQueueCreate(3, sizeof(int));
    q_handle_signal = xQueueCreate(3, sizeof(int)); 

    vTaskResume(task_rt3p1_handle);
    vTaskResume(task_rt4_handle);

    vTaskDelete(NULL);

}


void task_rt3p1(void *p){

    int ret;

    fft_buffer_t random_data;

    random_data.arr_real = vReal;
    random_data.arr_img = vImag;
    
    fft_buffer_t *tx_t1 = &random_data;
    time_t *rx_t1;

    while(1){

        
      for(int i = 0; i < 5; i++){
          
          // 1. Send Pointer of the Buffer to RT4
          ret = xQueueSendToBack(q_handle_buffer, &tx_t1, 1000);

          if( ret == pdTRUE ){
            // Serial.println("-----------------");
            // Serial.print("[T1 Tx] Sent: ");
            // Serial.println(tx_t1->arr_real[0]);
          
          } else {
            // Serial.println("[T1 Tx] Failed :/\n");
          
          }


          // 2. Wait for RT4 to complete FFT

          // 3. Receive Signal from RT4
          ret = xQueueReceive(q_handle_signal, &rx_t1, portMAX_DELAY);

          if(ret == pdTRUE){
            // Serial.print("[T1 Rx] Received: ");
            // Serial.println(rx_t1->rtos_ticks);
            // Serial.println(rx_t1->time_ms);
            // Serial.println("-----------------");

            Serial.print("Wall Time -> ");
            // Serial.print("Delta RTOS Ticks: ");
            // Serial.print(rx_t1->rtos_ticks);
            Serial.print("\t Delta Time: ");
            Serial.print(rx_t1->time_ms);
            Serial.println(" ms");
            // Serial.println("-----------------");

          
          } else {
              // Serial.println("[T1 Rx] Failed!\n\n");
          
          }

        vTaskDelay(30/portTICK_PERIOD_MS);   // create a 3 sec delay
      }
      
      vTaskDelete(task_rt4_handle);

      // Start the MIDI Project
      midi_init();

      vTaskDelete(NULL);

        
    }

}



