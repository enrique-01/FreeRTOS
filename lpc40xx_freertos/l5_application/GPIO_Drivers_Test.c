/*
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "board_io.h"
#include "common_macros.h"
#include "periodic_scheduler.h"
#include "sj2_cli.h"

#include "gpio_lab.h"
#include "semphr.h"

static SemaphoreHandle_t switch_press_indication;

static void create_blinky_tasks(void);
static void create_uart_task(void);
static void blink_task(void *params);
static void uart_task(void *params);

void choose_p1_26_as_io_pin(void) {
  uint32_t *iocon_p1_26 = (uint32_t *)0x4002C0E8;
  *iocon_p1_26 &= ~(0b111 << 0); // setting last 3 bits to 0 to set it to IO mode?
}

void choose_p1_26_as_output_direction(void) {
  uint32_t *dir_port1 = (uint32_t *)(0x20098000 + 0x020);
  *dir_port1 |= pin26; // Set to Output
}

void blinky_task(void *p) {
  choose_p1_26_as_io_pin();
  choose_p1_26_as_output_direction(); // PART 0

  uint32_t *port1_pin = (uint32_t *)(0x20098000 + 0x034);
  while (1) {
    *port1_pin |= pin26;
    vTaskDelay(100);

    *port1_pin &= ~pin26;
    vTaskDelay(100);
  }
}
*/

/*

typedef struct {

  uint8_t pin;
} port_pin_s;
void led_task_part_2(void *task_parameter) {
  // Type-cast the paramter that was passed from xTaskCreate()
  const port_pin_s *led = (port_pin_s *)(task_parameter);

  while (true) {
    gpio1__set_high(led->pin); /// part 2
    vTaskDelay(100);

    gpio1__set_low(led->pin);
    vTaskDelay(100);
  }
}

void led_task(void *task_parameter) {
  // type cast
  const port_pin_s *led = (port_pin_s *)(task_parameter);

  while (true) {
    if (xSemaphoreTake(switch_press_indication, 1000)) {
      // TODO: Blink the LED
      gpio1__set_high(led->pin);

    } else {
      puts("Timeout: No switch press indication for 1000ms");
      gpio1__set_low(led->pin);
    }
  }
}

void switch_task(void *task_parameter) {
  const port_pin_s *switch_one = (port_pin_s *)task_parameter; // Part 3

  while (true) {

    if (gpio1__get_level(switch_one->pin)) {
      xSemaphoreGive(switch_press_indication);
    }

    vTaskDelay(100);
  }
}


int main(void) {
  // create_blinky_tasks();
  // create_uart_task();

  switch_press_indication = xSemaphoreCreateBinary();


  static port_pin_s switch_one = {15}; // pin 1?
  static port_pin_s led = {24};        // check slack comment for diagram

  static port_pin_s led0 = {18}; // Task 2
  static port_pin_s led1 = {24}; // Task 2

  xTaskCreate(led_task, "LED", 2048 / sizeof(void *), &led, 1, NULL);              // task 3
  xTaskCreate(switch_task, "SWITCH", 2048 / sizeof(void *), &switch_one, 1, NULL); // task 3

  // xTaskCreate(led_task_part_2, "LED", 2048 / sizeof(void *), &led0, 1, NULL); //task 2
  // xTaskCreate(led_task_part_2, "LED", 2048 / sizeof(void *), &led1, 1, NULL); //task 2

  // xTaskCreate(blinky_task, "LED", 2048 / sizeof(void *), NULL, PRIORITY_LOW, NULL); // TASK 0
  puts("Starting RTOS");
  vTaskStartScheduler();

  return 0;
}

*/
