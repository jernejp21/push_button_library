/*
 * button.h
 *
 *  MIT License
 *
 * Copyright (c) 2024 Jernej Pangerc
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#if defined(USE_HAL_DRIVER)
  #include "main.h"
  #define DIGITAL_PIN_READ(port, pin) HAL_GPIO_ReadPin(port, pin)
  #define GET_TIME() HAL_GetTick()
#elif defined(ARDUINO)
  #include <Arduino.h>
  #define DIGITAL_PIN_READ(port, pin) digitalRead(pin)
  #define GET_TIME() millis()
#else
  #error "Define DIGITAL_PIN_READ and DIGITAL_PIN_WRITE"
#endif

/**
  * @brief   Button structure definition
  */
typedef struct
{
  uint32_t l_curr_time;  // do not edit value
  uint32_t l_prev_time;  // do not edit value
  uint8_t l_curr_state;  // do not edit value
  uint8_t l_prev_state;  // do not edit value
  uint8_t pressed_state;  // When button pressed logic; input is HIGH (1) or LOW (0)
  void *gpio_port;
  uint16_t gpio_pin;
  void (*button_callback)(void *p1);
} button_t;

void button_init(button_t *hbutton);
void button_callback(button_t *hbutton, void *p1, uint32_t hold_ms);
uint8_t button_flag(button_t *hbutton, uint32_t hold_ms);

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_BUTTON_H_ */
