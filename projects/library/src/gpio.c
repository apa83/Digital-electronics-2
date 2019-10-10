#include "gpio.h"
#define DDR(x) (*(&x-1))


/*  Functions  ---------------------------------------------------------*/
void  GPIO_config_output(volatile  uint8_t *reg_name , uint8_t  pin_num)
{
    // Body of the  function
    *reg_name  |= _BV(pin_num);
}

void  GPIO_config_input_nopull(volatile  uint8_t *reg_name , uint8_t  pin_num)
{
    // Body of the  function
    *reg_name &= _BV(pin_num);
    DDR(*reg_name) &= ~_BV(pin_num);
}

void  GPIO_config_input_pullup(volatile  uint8_t *reg_name , uint8_t  pin_num)
{
    // Body of the  function
    *reg_name |= _BV(pin_num);
    DDR(*reg_name) &= ~_BV(pin_num);
}

void  GPIO_write(volatile  uint8_t *reg_name, uint8_t  pin_num, uint8_t pin_val)
{
    // Body of the  function
    if(pin_val==1)
    {
        //Si queremos poner un 1, hacemos la operacion OR
        *reg_name |= _BV(pin_num);
    }
    else
    {
        //Si queremos poner un 0, hacemos la operacion AND con la ~ que invierte todo el bit, PARA QUE AL HACER LA OPERACION AND LUEGO TE QUEDE SOLO UN BIT ENCENDIDO
        *reg_name &= ~_BV(pin_num);
    }  
}

void  GPIO_toggle(volatile  uint8_t *reg_name , uint8_t  pin_num)
{
    // Parpadeo
    *reg_name ^= _BV(pin_num); 
}

void  GPIO_read(volatile  uint8_t *reg_name , uint8_t  pin_num)
{
    // Return bit_is_clear(*reg_name, pin_num);
    return((*reg_name & _BV(pin_num)) >> pin_num);

    // si hay por ejemplo un 1 en posicion 4, hacemos operacion & _BV
    //que pone un bit a uno en la posicion pin_num, al hacer la oper. and
    //se queda en la pos 4 el bit a 1, pero hay que moverle a la posicion 0
    // de tal manera que sepamos si es un 1 o no
}