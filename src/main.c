#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#include "include/led.h"
#include "include/button.h"

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

    puts("passei pela oneshot");

    state++;

    if (state >= 4) {
        timer_running = false;
        return 0;
    }

    return 3000 * 1000;
} 



int main() {
    stdio_init_all();
    // inicizaliando os leds
    led_init(LED_RED_PIN);
    led_init(LED_GREEN_PIN);
    led_init(LED_BLUE_PIN);

    // inicializando o botão
    button_init(BUTTON_A_PIN);
    button_init(BUTTON_B_PIN);

    while (1) {
        puts("nao entrei no if");
        // se o botao foi pressionado e o tempo não estava em execução
        if (button_pressed && !timer_running) {
            puts("entrei no if");
            button_pressed = false; // altera o botao para não pressionado
            timer_running = true;   // altera o timer para ativo
            state = 0;              // define o estado da rotina de leds para 0

            // inicializa o alarme
            add_alarm_in_ms(
                1, 
                oneshot_timer_callback,
                NULL,
                false
            );
        }

        // evitar a sobrecarga da CPU
        sleep_ms(100);
    }
}
