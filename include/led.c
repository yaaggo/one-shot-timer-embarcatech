#include "led.h"

void led_init(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

void led_state(uint8_t pin, uint8_t state) {
    gpio_put(pin, state);
}