#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "include/led.h"

// pino do botão
#define BUTTON_A_PIN 5

// variaveis para monitorar o estado do botão e do timer
volatile bool button_pressed = false;
volatile bool timer_running = false;

// variavel para controlar qual a rotina de leds utilizar
volatile uint8_t state = 0;

// matriz com as rotinas dos leds
const bool leds[][3] = {
    {1, 1, 1},
    {0, 1, 1},
    {0, 0, 1},
    {0, 0, 0}
};


// função de callback do timer
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

    // interrupção do botão so diz que o botão esta pressionado se o timer não estiver rodando
    if (!timer_running) {
        button_pressed = true;
    }
}

int main() {
    stdio_init_all();
    // inicizaliando os leds
    led_init(LED_RED_PIN);
    led_init(LED_GREEN_PIN);
    led_init(LED_BLUE_PIN);

    // inicializando o botão
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    // atviando a interrupção quando apertar o botão
    gpio_set_irq_enabled_with_callback(
        BUTTON_A_PIN,
        GPIO_IRQ_EDGE_FALL,
        true,
        &button_callback
    );

    while (1) {
        // se o botao foi pressionado e o tempo não estava em execução
        if (button_pressed && !timer_running) {

            button_pressed = false; // altera o botao para não pressionado
            timer_running = true;   // altera o timer para ativo
            state = 0;              // define o estado da rotina de leds para 0

            // inicializa o alarme
            add_alarm_in_ms(
                0, 
                oneshot_timer_callback,
                NULL,
                false
            );
        }

        // Parte opcional para evitar o debouncing via software
        sleep_ms(50);
    }
}
