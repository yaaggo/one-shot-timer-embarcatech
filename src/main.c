#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "include/led.h"

#define BUTTON_A_PIN 5

volatile bool button_pressed = false;
volatile bool timer_running = false;
volatile uint8_t state = 0;


const bool leds[][3] = {
    {1, 1, 1},
    {0, 1, 1},
    {0, 0, 1},
    {0, 0, 0}
};

int64_t oneshot_timer_callback(alarm_id_t id, void *user_data) {
    led_state(LED_RED_PIN, leds[state][0]);
    led_state(LED_BLUE_PIN, leds[state][1]);
    led_state(LED_GREEN_PIN, leds[state][2]);

    state++;

    if (state >= 4) {
        timer_running = false;
        return 0;
    }

    return 3000 * 1000;
} 

void button_callback(uint gpio, uint32_t events) {
    if (!timer_running) {
        button_pressed = true;
    }
}

int main() {
    stdio_init_all();

    led_init(LED_RED_PIN);
    led_init(LED_GREEN_PIN);
    led_init(LED_BLUE_PIN);

    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    gpio_set_irq_enabled_with_callback(
        BUTTON_A_PIN,
        GPIO_IRQ_EDGE_FALL,
        true,
        &button_callback
    );

    while (1) {
        if (button_pressed && !timer_running) {
            button_pressed = false;
            timer_running = true;
            state = 0;

            add_alarm_in_ms(
                0, 
                oneshot_timer_callback,
                NULL,
                false
            );
        }
        sleep_ms(10);
    }
}
