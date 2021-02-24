#include "gpio_isr.h"
#include "FreeRTOS.h"
#include "delay.h"
#include "gpio_lab.h"
#include "lpc40xx.h"
#include "lpc_peripherals.h"
#include "task.h"
#include <stdint.h>
#include <stdio.h>

// void lpc_peripheral__halt_handler(void);

// lpc_peripheral__enable_interrupt(LPC_PERIPHERAL__GPIO, gpio0__interrupt_dispatcher, NULL);
static function_pointer_t gpio0_callbacks[32];

void gpio0__attach_interrupt(uint32_t pin, gpio_interrupt_e interrupt_type, function_pointer_t callback) {
  // 1) Store the callback based on the pin at gpio0_callbacks**************************<---------
  if (interrupt_type) {
    GPIO__set_as_input(0, pin);
    LPC_GPIOINT->IO0IntEnR |= (1 << pin); // Rising edge port 0
    NVIC_EnableIRQ(GPIO_IRQn);
    gpio0_callbacks[pin] = callback;
  } else {
    GPIO__set_as_input(0, pin);
    LPC_GPIOINT->IO0IntEnF |= (1 << pin); // Falling edge port 0
    NVIC_EnableIRQ(GPIO_IRQn);
    gpio0_callbacks[pin] = callback;
  }
}

// We wrote some of the implementation for you
void gpio0__interrupt_dispatcher(void) {
  int pin_that_generated_interrupt = 0;
  for (int i = 0; i <= 31; i++) {
    if ((LPC_GPIOINT->IO0IntStatF & (1 << i)) || (LPC_GPIOINT->IO0IntStatR & (1 << i))) {
      // pin_that_generated_interrupt = gpio0_callbacks[i];
      pin_that_generated_interrupt = i;
      break;
    }
  }
  function_pointer_t attached_user_handler = gpio0_callbacks[pin_that_generated_interrupt];

  // Invoke the user registered callback, and then clear the interrupt
  attached_user_handler();
  LPC_GPIOINT->IO0IntClr |= (1 << pin_that_generated_interrupt);
}
