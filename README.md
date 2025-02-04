# Atividade 2: Temporizador de um disparo (One Shot)

## Descrição
Este projeto implementa um sistema de temporização para o acionamento de LEDs, controlado por um botão (pushbutton). Ao pressionar o botão, os LEDs seguem uma sequência de iluminação baseada em um temporizador de 3 segundos.

---

## Componentes Utilizados
1. Microcontrolador Raspberry Pi Pico W
2. 03 LEDs (azul, vermelho e verde)
3. 03 Resistores de 330 Ω
4. 01 Botão (pushbutton)

---

## Funcionamento do Programa
1. Quando o usuário pressiona o botão, todos os LEDs são ligados.
2. A cada 3 segundos, um LED é desligado até que todos estejam apagados.
3. Durante a sequência de temporização, o botão não pode reiniciar o processo.
4. Um debounce por software foi implementado para evitar leituras erradas do botão.

---

## Estrutura do Código
O programa utiliza as bibliotecas `pico/stdlib.h`, `hardware/gpio.h` e `hardware/timer.h` para manipulação dos LEDs e do botão. A função `add_alarm_in_ms()` é utilizada para criar o temporizador de 3 segundos.

---

### Principais Funções
- **`oneshot_timer_callback()`**: Callback do temporizador que altera o estado dos LEDs a cada 3 segundos.
- **`button_callback()`**: Callback da interrupção do botão, que inicia a sequência de LEDs caso não haja uma em andamento.
  
---

## Experimento com BitDogLab
Foi realizado um teste com a ferramenta educacional BitDogLab, utilizando um LED RGB nos GPIOs 11, 12 e 13 e um botão no GPIO 05 para validar a funcionalidade da implementação.

---

## Como Executar o Projeto

1) **Configurar o ambiente**:
   - Instale o Raspberry Pi Pico SDK.
   - Configure o ambiente de desenvolvimento.

2) **Compilar o código**:
   - Clone o repositório no diretório que você quer compilar utilizando:
     ```bash
     git clone https://github.com/yaaggo/one-shot-timer-embarcatech.git
     ```
   - Compile utilizando as ferramentas do SDK do Pico.
   - (opcional) Se estiver utilizando a exntensão do Raspberry Pi Pico SDK no vscode, importe o projeto e compile pela extensão

4) **Fazer upload para a placa**:
   - Conecte a Raspberry Pi Pico via USB.
   - Envie o binário gerado para a placa.

5) **Executar o código**:
   - Observe os LEDs alternando a cada 3 segundos.
   - Acompanhe as mensagens no console serial.

---

## Observações

- Este projeto demonstra o uso de temporizadores periódicos na Raspberry Pi Pico.
- `add_repeating_timer_ms()` facilita a execução de funções em intervalos regulares.
- O loop principal garante que o programa continue rodando enquanto o temporizador gerencia os LEDs.
