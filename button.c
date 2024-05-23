/*
 * button.c
 *
 *  MIT License
 *
 * Copyright (c) 2024 Jernej Pangerc
 */

#include "button.h"

/**
  * @brief  Initialises button_t structure
  * @param  hbutton pointer to button_t structure
  * @retval None
  */
void button_init(button_t *hbutton)
{
  hbutton->l_curr_state = !hbutton->pressed_state;
  hbutton->l_prev_state = !hbutton->pressed_state;
  hbutton->l_curr_time = 0;
  hbutton->l_prev_time = 0;
}

/**
  * @brief  Debounces push button and calls callback function if button is pressed.
  * @param  hbutton pointer to button_t structure
  * @param  p1 pointer to parameter for callback function
  * @param  hold_ms button debounce time. How long should button be pressed for recognition
  * @retval None
  */
void button_callback(button_t *hbutton, void *p1, uint32_t hold_ms)
{
  if(hbutton->button_callback == 0)
  {
    return;
  }

  hbutton->l_curr_state = DIGITAL_PIN_READ((GPIO_TypeDef* )hbutton->gpio_port, hbutton->gpio_pin);
  hbutton->l_curr_time = GET_TIME();

  if((hbutton->l_curr_state != hbutton->l_prev_state) && (hbutton->l_curr_state == hbutton->pressed_state))
  {
    if((hbutton->l_curr_time - hbutton->l_prev_time) > hold_ms)
    {
      (*hbutton->button_callback)(p1);
      hbutton->l_prev_state = hbutton->l_curr_state;
    }
  }
  else
  {
    hbutton->l_prev_state = hbutton->l_curr_state;
    hbutton->l_prev_time = hbutton->l_curr_time;
  }
}

/**
  * @brief  Debounces push button and returns button status - pressed, released.
  * @param  hbutton pointer to button_t structure
  * @param  hold_ms button debounce time. How long should button be pressed for recognition.
  * @retval uint8_t if 1 button is pressed, if 0 button is released
  */
uint8_t button_flag(button_t *hbutton, uint32_t hold_ms)
{
  static uint8_t retval = 0;

  hbutton->l_curr_state = DIGITAL_PIN_READ((GPIO_TypeDef* )hbutton->gpio_port, hbutton->gpio_pin);
  hbutton->l_curr_time = GET_TIME();

  if((hbutton->l_curr_state != hbutton->l_prev_state) && (hbutton->l_curr_state == hbutton->pressed_state))
  {
    if((hbutton->l_curr_time - hbutton->l_prev_time) > hold_ms)
    {
      retval = 1;
      hbutton->l_prev_state = hbutton->l_curr_state;
    }
  }
  else
  {
    if(hbutton->l_curr_state != hbutton->l_prev_state)
    {
      retval = 0;
    }
    hbutton->l_prev_state = hbutton->l_curr_state;
    hbutton->l_prev_time = hbutton->l_curr_time;
  }
  return retval;
}
