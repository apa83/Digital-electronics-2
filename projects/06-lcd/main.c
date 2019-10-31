/*
 * ---------------------------------------------------------------------
 * Author:      Tomas Fryza
 *              Dept. of Radio Electronics, Brno Univ. of Technology
 * Created:     2018-10-16
 * Last update: 2019-10-25
 * Platform:    ATmega328P, 16 MHz, AVR 8-bit Toolchain 3.6.2
 * ---------------------------------------------------------------------
 * Description:
 *    Decimal counter with data output on LCD display.
 * 
 * Note:
 *    Modified version of Peter Fleury's LCD library with R/W pin 
 *    connected to GND. Newline symbol "\n" is not implemented, use
 *    lcd_gotoxy() function instead.
 */

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>             // itoa() function
#include "timer.h"
#include "lcd.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 *  Brief:  Main program. Shows decimal values ​​on LCD display.
 *  Input:  None
 *  Return: None
 */
uint8_t value = 255;
char lcd_string[9];

int main(void)
{
    /* LCD display
     * TODO: See Peter Fleury's online manual for LCD library 
     * http://homepage.hispeed.ch/peterfleury/avr-software.html
     * Initialize display and test different types of cursor
    */

    lcd_init(LCD_DISP_ON);

    //uint8_t value = 255;
    //char lcd_string[3];

    lcd_gotoxy(0, 0);
    
    //itoa(value, buffer, base)
    lcd_puts("Counter:  ");

    lcd_gotoxy(0, 1);

    lcd_puts("0x");

    lcd_puts("    0b");
    
    // Display string without auto linefeed
    //lcd_puts("LCD testing");

    // TODO: Display variable value in decimal, binary, and hexadecimal

    /* Timer1
     * TODO: Configure Timer1 clock source and enable overflow 
     *       interrupt */

    TIM_config_prescaler(TIM1, TIM_PRESC_256);
    TIM_config_interrupt(TIM1, TIM_OVERFLOW_ENABLE);

    sei();/* Enable interrupts by setting the global interrupt mask */

    /* TODO: Design at least two user characters and store them in 
     *       the display memory */

    uint8_t lcd_user_symbols [] = { 0x00,
                                    0x0A,
                                    0x15,
                                    0x11,
                                    0x11,
                                    0x0A,
                                    0x04,
                                    0x00};

    // Set  pointer  to  beginning  of CG RAM  memory
    lcd_command(1<<LCD_CGRAM);

    // Store  new  characters  line by line
    lcd_data(lcd_user_symbols [0]);
    lcd_data(lcd_user_symbols [1]);
    lcd_data(lcd_user_symbols [2]);
    lcd_data(lcd_user_symbols [3]);
    lcd_data(lcd_user_symbols [4]);
    lcd_data(lcd_user_symbols [5]);
    lcd_data(lcd_user_symbols [6]);
    lcd_data(lcd_user_symbols [7]);

    // Clear  display  and  set  cursor  to home  position
    lcd_clrscr ();

    //  Display  first  user-defined  character
    lcd_putc (0x00);

    // Infinite loop
    for (;;) {
    }

    // Will never reach this
    return (0);
}

/**
 *  Brief: Timer1 overflow interrupt routine. Increment counter value.
 */
ISR(TIMER1_OVF_vect)
{
    // TODO: Increment counter value form 0 to 255

        itoa(value, lcd_string, 10);
        lcd_gotoxy(8, 0);
        lcd_puts(lcd_string); 

        lcd_gotoxy(2, 1);

        itoa(value, lcd_string, 16);
        lcd_puts(lcd_string);

        lcd_gotoxy(8, 1);

        itoa(value, lcd_string, 2);
        lcd_puts(lcd_string);

        value = value - 1;


}