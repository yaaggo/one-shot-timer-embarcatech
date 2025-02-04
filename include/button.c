#include "button.h"

// variaveis para monitorar o estado do botão e do timer
volatile bool button_pressed = false;
volatile bool timer_running = false;

// fazer o deboucing via software
static volatile uint32_t last_a_interrupt_time = 0;
static volatile uint32_t last_b_interrupt_time = 0;

void button_callback(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    // verifica qual botão acionou a interrupção e trata o debounce
    if (gpio == BUTTON_A_PIN && !timer_running) {
        if (current_time - last_a_interrupt_time > DEBOUNCE_TIME) {
            last_a_interrupt_time = current_time;

            if (events & GPIO_IRQ_EDGE_FALL) {
                button_pressed = true;
            }
        }
    } else if (gpio == BUTTON_B_PIN) {
        if (current_time - last_b_interrupt_time > DEBOUNCE_TIME) {
            last_b_interrupt_time = current_time;

            if (events & GPIO_IRQ_EDGE_FALL) {
                reset_usb_boot(0, 0);
            }
        }
    }
}

void button_init(uint8_t pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);

    // habilita interrupções para bordas de subida
    gpio_set_irq_enabled_with_callback(
        pin,
        GPIO_IRQ_EDGE_FALL,
        true,
        &button_callback
    );
}