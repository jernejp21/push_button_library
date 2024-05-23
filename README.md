# C library for push button

This library is meant to be used by any microcontroller and any hardware application layer.

It is already configured for Arduino and STM32 HAL. You can easily configure it for other framework.

# Example for STM32

## Using callback function

Example below increases number by 1 everytime a button is pressed for at least 500 ms.

```C
#ifndef USE_HAL_DRIVER
#define USE_HAL_DRIVER
#endif

#include "button.h"

button_t button;
uint32_t number;

void increase_number(uint32_t *number)
{
    (*number)++;
}

int main(void)
{
    /* HAL and GPIO should be initialised by now */
    button.button_callback = (void (*)(void*))increase_number;
    button.gpio_port = B_UP_GPIO_Port;
    button.gpio_pin = B_UP_Pin;
    button.pressed_state = 0;

    while(1)
    {
        /* param1 Pointer to button_t structure
        *  param2 pointer to parameter for callback function
        *  param3 button debounce time in ms
        */
        button_callback(&button, &number, 500);
    }
}
```

## Using status flag

Example below increases number by 1 while a button is pressed for at least 500 ms.

```C
#ifndef USE_HAL_DRIVER
#define USE_HAL_DRIVER
#endif

#include "button.h"

button_t button;
uint32_t number;
uint8_t is_button_pressed;

int main(void)
{
    /* HAL and GPIO should be initialised by now */
    button.gpio_port = B_UP_GPIO_Port;
    button.gpio_pin = B_UP_Pin;
    button.pressed_state = 0;

    while(1)
    {
        /* param1 Pointer to button_t structure
        *  param3 button debounce time in ms
        */
        is_button_pressed = button_flag(&button, 500);
        
        if(is_button_pressed)
        {
            number++;
        }
    }
}
```

# Example for Arduino

## Using callback function

Sample below increases number by 1 everytime a button is pressed for at least 500 ms.

```C
#ifndef ARDUINO
#define ARDUINO
#endif

#include "button.h"

button_t button;
uint32_t number;

void increase_number(uint32_t *number)
{
    (*number)++;
}

void setup()
{
    button.button_callback = (void (*)(void*))increase_number;
    button.gpio_pin = 10;
    button.pressed_state = LOW;

    pinMode(10, INPUT);
}

void loop()
{
    /* param1 Pointer to button_t structure
    *  param2 pointer to parameter for callback function
    *  param3 button debounce time in ms
    */
    button_callback(&button, &number, 500);
}
```

## Using status flag

Example below increases number by 1 while a button is pressed for at least 500 ms.

```C
#ifndef ARDUINO
#define ARDUINO
#endif

#include "button.h"

button_t button;
uint32_t number;
uint8_t is_button_pressed;

void setup()
{
    button.gpio_pin = 10;
    button.pressed_state = LOW;

    pinMode(10, INPUT);
}

void loop()
{
    /* param1 Pointer to button_t structure
    *  param3 button debounce time in ms
    */
    is_button_pressed = button_flag(&button, 500);
    
    if(is_button_pressed)
    {
        number++;
    }
}
```