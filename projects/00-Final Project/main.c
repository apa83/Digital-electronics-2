/*
 ---------------------------------------------------------------------
  Author:      Jose Ramon Hoz & Antonio Perojo
               Brno Univ. of Technology
  Created:     2018-12-03
  Last update: 2019-XX-XX
  Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 ---------------------------------------------------------------------
  Description:
    Timer that shows how much time has the poker player left in his turn. 
*/

/* Includes ----------------------------------------------------------*/
#include <stdlib.h>         // itoa() function
#include <avr/io.h>
#include <avr/interrupt.h>
#include "gpio.h"
#include "segment.h"
#include "timer.h"
#include <TM1637Display.h>


/* Typedef -----------------------------------------------------------*/
typedef enum {
    START = 1,
    STOP,
    RESET
} state_t;

/* Define ------------------------------------------------------------*/

/* Variables ---------------------------------------------------------*/
state_t current_state = START;

/* Function prototypes -----------------------------------------------*/
//void fsm_buttons(void);

int main(void)
{
    /* 7-segment display interface
       TODO: Configure 7-segment display pins */

    GPIO_config_output(&DDRB, SEGMENT_DATA);
    GPIO_config_output(&DDRD, SEGMENT_CLK);
    GPIO_config_output(&DDRD, SEGMENT_LATCH);

    //Timer1 configuration for value incrementation
    TIM_config_prescaler(TIM1, TIM_PRESC_256);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    // Enable interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    for (;;)
    {
        //TODO: Use function to display digit 1 at position 0
        SEG_putc(9, 0);
    }

    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Update state of Finite
 *         State Machine.
 */

ISR(TIMER1_OVF_vect)
{
    // TODO: SHOW THE TIME LEFT

    static uint8_t digit = 0;
    digit++;
    if(digit>9)
    {
        digit = 0;
    }
    SEG_putc(digit, 0);
}
/*
void fsm_buttons(void)
{
    switch (current_state) {
    case START:
    
        current_state = STOP;
        
        break;

    case STOP:
        
        current_state = RESET;
        
        break;

    case RESET:

        current_state = START;
        
        break;

    default:
        current_state = START;
    }*/

