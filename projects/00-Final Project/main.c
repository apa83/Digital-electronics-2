/**
 * Copyright (c) 2017-2018, Łukasz Marcin Podkalicki <lpodkalicki@gmail.com>
 *
 * This is ATtiny13 "Running Digits" example using attiny-tm1637-library,
 * https://github.com/lpodkalicki/attiny-tm1637-library .
 *
 */

/* Includes ----------------------------------------------------------*/
#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "tm1637.h"

/* Typedef -----------------------------------------------------------*/
/* Define ------------------------------------------------------------*/
#define BTN1   PD2
#define BTN2   PD3

/* Variables ---------------------------------------------------------*/
/* Function prototypes -----------------------------------------------*/
/* Functions ---------------------------------------------------------*/

int main(void)
{
    int8_t k;
    int8_t k1 = 0;

    int8_t i;
    int8_t i1 = 0;

	int8_t j;
    int8_t j1 = 9;

	/* setup */
	TM1637_init(1/*enable*/, 15/*brightness*/);
    TM1637_clear();

    //TM1637_display_digit(0, 0);
    TM1637_display_digit(1, 0);
    TM1637_display_digit(2, 0);
    TM1637_display_digit(3, 9);
    TM1637_display_colon(1);

    //PUSH BUTTON1 -> Start / Stop / Reset
    //   set    bits    to   low
    DDRD |= ~_BV(BTN1);

    //PUSH BUTTON2 -> Increment value of the counter
    //   set    bits    to   low
    DDRD |= ~_BV(BTN2);

    here:

    while(1)
    {
        if(bit_is_set(PIND, BTN2))
        {
            i1++;

            if(i1 > 5)
            {
                k1++;
                i1 = 0;
            }

            TM1637_display_digit(1, k1);
            TM1637_display_digit(2, i1);
            TM1637_display_digit(3, j1);
            _delay_ms(500);
        }
        
        if(bit_is_set(PIND, BTN1))
        {
            break;
        }
    }

    _delay_ms(500);

    while(1)
    {
        if(bit_is_set(PIND, BTN1))
        {
            TM1637_clear();

            for(k = k1; k >= 0; k--)
            {
                TM1637_display_digit(1, k);

                for(i = i1; i >= 0; i--)
                {          
                    TM1637_display_digit(2, i);
                    
                    for(j = j1; j >= 0; j--)
                    {
                        TM1637_display_digit(3, j);
                        TM1637_display_colon(0);
                        _delay_ms(500);
                        TM1637_display_colon(1);
                        _delay_ms(500);               
                    }
                }

                i1 = 5;
            }

            break;
        }        
    }

    //PARPADEO CUANDO LLEGUE LA CUENTA A CERO
    while(1)
    {
        if(bit_is_set(PIND, BTN2))
        {

            k1 = 0;
            i1 = -1;
            j1 = 9;
            goto here;
        }

        TM1637_init(0/*disable*/, 15/*brightness*/);
        _delay_ms(100);
        TM1637_init(1/*enable*/, 15/*brightness*/);
        _delay_ms(100);
    }

	/* loop que funciona*/
/*
	while (1)
    {
		for (n = 0; n < TM1637_POSITION_MAX; ++n)
        {
			TM1637_display_digit(n, (k + n) % 0x10);
		}

		TM1637_display_colon(1);
		_delay_ms(200);
		TM1637_display_colon(0);
		_delay_ms(200);

		k++;
	}
*/
}
