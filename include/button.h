#ifndef BUTTON_H
#define BUTTON_H

#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6
#define DEBOUNCE_TIME 50

#include <stdint.h>
#include <stdbool.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"

// variaveis para monitorar o estado do botão e do timer
extern volatile bool button_pressed;
extern volatile bool timer_running;

void button_init(uint8_t pin);

#endif