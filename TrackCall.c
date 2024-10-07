//class Demo for /trackCall
#include <stdio.h>
#include "pico/stdlib.h"

//Define GPIO's for circuit components
#define REDLED 5
#define GREENLED 3
#define YELLOWLED 4
#define TRACKCALL 2
#define RESET 7
#define RELAY 6

#define DEBOUNCETIME 50
#define DELAYLOOPTIME 250
#define ELEMENTS(x) (sizeof(x)/sizeof((x)[0]))
// This is where we define our pinouts  

void InitalizeLEDsAndButtons(){
    const uint buttons[] = {RESET, TRACKCALL};
    const uint leds[] = {REDLED,YELLOWLED, GREENLED, RELAY};
    stdio_init_all();

    for (int i = 0; i < ELEMENTS(leds); i++){
        gpio_init(leds[i]);
        gpio_set_dir(leds[i],GPIO_OUT);
        gpio_put(leds[i],0);
    }//END of For Loop

    for (int i = 0; i < ELEMENTS(buttons); i++){
        gpio_init(buttons[i]);
        gpio_set_dir(buttons[i],GPIO_IN);
        gpio_pull_up(buttons[i]);
    }//END of For Loop

}//END of void InitializeJEDsAndButtons()

void activateRelay(uint changed) {
    if (changed)
    {
        gpio_put(RELAY,1);
        sleep_ms(1000);
        gpio_put(RELAY,0);
    }    
}

int main() {
    uint state = 0;
    uint change = 0;
    InitalizeLEDsAndButtons();

    //turn relay off
    while(1){
        //input reading
        if(gpio_get(TRACKCALL) == false) {
            sleep_ms(DEBOUNCETIME);
            if(gpio_get(TRACKCALL) == false) {
                state++;
                change = 1;
            }    
        }

        if(gpio_get(RESET) == false) {
            sleep_ms(DEBOUNCETIME);
            if(gpio_get(RESET) == false)
                state = 0;    
        }    
        //logic and outputs
        switch(state) {
            case 0:
                gpio_put(GREENLED,1);
                gpio_put(YELLOWLED,0);
                gpio_put(REDLED,0);
                break;
        
             case 1:
                gpio_put(GREENLED,0);
                gpio_put(YELLOWLED,1);
                gpio_put(REDLED,0);
                activateRelay(change);
                break;

             case 2:
                gpio_put(GREENLED,0);
                gpio_put(YELLOWLED,0);
                gpio_put(REDLED,1);
                activateRelay(change);
                break;
            
             case 3:
                gpio_put(GREENLED,0);
                gpio_put(YELLOWLED,0);
                gpio_put(REDLED,0);
                activateRelay(change);   
                break;
            
            default:
                gpio_put(GREENLED,1);
                gpio_put(YELLOWLED,1);
                gpio_put(REDLED,1);
                sleep_ms(250);

                gpio_put(GREENLED,0);
                gpio_put(YELLOWLED,0);
                gpio_put(REDLED,0);
        }

        sleep_ms(DELAYLOOPTIME);
        change = 0;
    }//END of While Loop
    
    return 0;
}//END of Main ()

