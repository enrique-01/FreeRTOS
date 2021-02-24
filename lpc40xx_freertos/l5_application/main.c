#include "FreeRTOS.h"
#include "board_io.h"
#include "common_macros.h"
#include "delay.h"
#include "gpio.h"
#include "gpio_isr.h"
#include "gpio_lab.h"
#include "lpc40xx.h"
#include "lpc_peripherals.h"
#include "periodic_scheduler.h"
#include "semphr.h"
#include "sj2_cli.h"
#include "task.h"
#include <stdio.h>

void gpio_interrupt(void);

/* Part 0
void gpio_interrupt(void) {
  fprintf(stderr, "INTERUPPTEDDDDD");
  LPC_GPIOINT->IO0IntClr = (1 << 30);
}*/

/* //Part 0
void main(void) {

  lpc_peripheral__enable_interrupt(LPC_PERIPHERAL__GPIO, gpio_interrupt, "unused");

  LPC_GPIO0->DIR &= ~(1 << 30);        // P0_30 as switch
  LPC_GPIOINT->IO0IntEnF |= (1 << 30); // falling edge port 0

  // LPC_GPIO1->DIR |= (1 << 18);

  NVIC_EnableIRQ(GPIO_IRQn);
  // gpio1__set_as_output(18);

  while (1) {
    if (LPC_GPIOINT->IO0IntStatF & (1 << 30)) {
      gpio1__set_low(18);
      delay__ms(100);
      gpio1__set_high(18);
    }
  }
}*/

/*///////////////////////////////////////////////////////////////////////////Part 1
static SemaphoreHandle_t switch_pressed_signal;

void sleep_on_sem_task(void *p) {
  while (1) {
    // xSemaphoreTake(switch_pressed_signal, 1);
    if ((switch_pressed_signal)) {
      xSemaphoreTake(switch_pressed_signal, portMAX_DELAY);
      gpio1__set_low(18);
      delay__ms(100);
      gpio1__set_high(18);
    }
  }
}

void gpio_interrupt(void) { // part 1
  fprintf(stderr, "ISR Entry");
  xSemaphoreGiveFromISR(switch_pressed_signal, NULL);
  LPC_GPIOINT->IO0IntClr = (1 << 30);
}

void main(void) {
  lpc_peripheral__enable_interrupt(LPC_PERIPHERAL__GPIO, gpio_interrupt, "unused");
  LPC_GPIO1->DIR |= (1 << 18);
  gpio1__set_as_output(18);
  switch_pressed_signal = xSemaphoreCreateBinary();

  LPC_GPIO0->DIR &= ~(1 << 30);        // P0_30 as switch
  LPC_GPIOINT->IO0IntEnF |= (1 << 30); // falling edge port 0

  // gpio_interrupt();
  NVIC_EnableIRQ(GPIO_IRQn);

  xTaskCreate(sleep_on_sem_task, "sem", (512U * 4) / sizeof(void *), NULL, PRIORITY_LOW, NULL);
  vTaskStartScheduler();
}

*//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pin29_isr(void) {
  GPIO__set_low(1, 24);
  delay__ms(100);
  GPIO__set_high(1, 24);
}
void pin30_isr(void) {
  GPIO__set_low(1, 18);
  delay__ms(100);
  GPIO__set_high(1, 18);
}

int main(void) {

  lpc_peripheral__enable_interrupt(LPC_PERIPHERAL__GPIO, gpio0__interrupt_dispatcher, "NAME TRACE");

  gpio0__attach_interrupt(30, GPIO_INTR__RISING_EDGE, pin30_isr);
  gpio0__attach_interrupt(29, GPIO_INTR__FALLING_EDGE, pin29_isr);
}
