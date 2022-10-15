/**
 * @file      rt2.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     Sourcefile for RT2.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "rt2.h"

uint32_t arr_notes[] = {HZ_293, HZ_329, HZ_261, HZ_130, HZ_196, SILENCE_1S};

void speaker_init(void){

  // 1. PRTIM4 Bit = 0, To turn-on Timer-4 (not required, already done internally by Arduino)
  BIT_CLR(TIMER4_POWER_REG, PRTIM4);    

  // 2. Clock Select Bits -> CS42, CS41, CS40 -> 001 -> For 1/256 as pre-scalar
  BIT_SET(TIMER4_CONTROL_REG_B, CS42);    
  BIT_CLR(TIMER4_CONTROL_REG_B, CS41);
  BIT_CLR(TIMER4_CONTROL_REG_B, CS40);

  // 3. Waveform Generation Bits -> WGM43, WGM42, WGM41, WGM40 -> 0100 -> For CTC Mode
  BIT_CLR(TIMER4_CONTROL_REG_B, WGM43); 
  BIT_SET(TIMER4_CONTROL_REG_B, WGM42);   
  BIT_CLR(TIMER4_CONTROL_REG_A, WGM41);
  BIT_CLR(TIMER4_CONTROL_REG_A, WGM40);

  // 4. Compare Output Bits -> COM4A1, COM4A0 -> 01 -> To toggle OC4A pin on compare match
  BIT_CLR(TIMER4_CONTROL_REG_A, COM4A1);
  BIT_SET(TIMER4_CONTROL_REG_A, COM4A0);  

  // 5. TCNT4 Register = 0 -> To start the count from 0
  TIMER4_COUNT_REG = 0;                   
  
  // 6. OCR4A Register = 78 -> To overflow Timer-4 after 78 ticks. (16MHz, 1/256 prescalar, 78 ticks -> 0.00125 seconds per overflow)
  TIMER4_OUTPUT_COMPARE_REG = SILENCE_1S;

  // 7. PH3 Bit in DDRH = 1 -> To make OC4A a output pin
  BIT_SET(DDR_SPEAKER, PIN_SPEAKER);
  
}


void speaker_turn_off(void){
    // Cut the clock to Timer-4 to turnoff the Speaker.
    BIT_CLR(TIMER4_CONTROL_REG_B, CS42);    
    BIT_CLR(TIMER4_CONTROL_REG_B, CS41);
    BIT_CLR(TIMER4_CONTROL_REG_B, CS40);
}


void task_rt2(void *pvParameters){

    speaker_init();
    
    static uint8_t notes_ticks = 0;
    static uint8_t times = 0;

    while(1) {

        TIMER4_COUNT_REG = 0; 
        TIMER4_OUTPUT_COMPARE_REG = arr_notes[notes_ticks];

        notes_ticks++; 

        if (notes_ticks == 6){
            notes_ticks = 0;
            times++;
            vTaskDelay(1500/portTICK_PERIOD_MS);  // Pause for 1.5s
        
        } else {
            vTaskDelay(1000/portTICK_PERIOD_MS);  // Play each note for 1s
        }

        if(times == 3){
            speaker_turn_off();
            vTaskDelete(NULL);      // Delete the task after playing the melody for 3 times.
        }

        
    }

    vTaskDelete(NULL);
}