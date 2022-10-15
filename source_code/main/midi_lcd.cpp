/**
 * @file      midi_lcd.cpp
 * @author    Sourav Jena, Yi Chen
 * @brief     LCD source code.
 * @version   1.0
 * @date      2022-05-28
 * 
 */

#include "midi_lcd.h"
#include "midi_keypad.h"

char password[3] = {'1', '2', '3'};
char entered_pass[3];

// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
LiquidCrystal lcd(17, 16, 21, 20, 19, 18);



void midi_lcd_init(){
    lcd.begin(16,2);
    
    lcd.setCursor(0,0);
    lcd.print("Enter Password:");
    
    lcd.setCursor(0,1);
    lcd.print("");
}

void midi_lcd_welcome(){
    lcd.begin(16,2);
    
    lcd.setCursor(0,0);
    lcd.print("474 YCSJ MIDI");
    
    lcd.setCursor(0,1);
    lcd.print("Controller");
}

int check_password(char *entered_pass){

    if(entered_pass[0] != password[0]){
        return -1;
    }

    if(entered_pass[1] != password[1]){
        return -1;
    }

    if(entered_pass[2] != password[2]){
        return -1;
    }

    return 0;
}   


void midi_lcd_get_password(void){

    static uint8_t x_pos = 0;

    while(1){
        char key = midi_keypad.getKey();     // Read the key

        if(key == '0'){
            
            if(check_password(entered_pass) == -1){
                lcd.setCursor(0,0);
                lcd.print("                ");
                lcd.setCursor(0,1);
                lcd.print("                ");

                lcd.setCursor(0,0);
                lcd.print("Wrong Password!");

                lcd.setCursor(0,1);
                lcd.print("Enter Again.");

                delay(1000);

                lcd.setCursor(0,0);
                lcd.print("Enter Password:");

                lcd.setCursor(0,1);
                lcd.print("                ");

                x_pos = 0;

                continue;

            } else {
                break;
            }

        }
  
        if (key){

            entered_pass[x_pos] = key;
            lcd.setCursor(x_pos, 1);
            lcd.print("*");
            x_pos++;
        }

        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}



void task_midi_lcd(void *p){

    

    while(1){
        midi_lcd_welcome();
        vTaskDelay(3000/portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}