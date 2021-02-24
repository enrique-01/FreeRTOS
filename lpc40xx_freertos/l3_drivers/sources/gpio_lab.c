#include "gpio_lab.h"
#include "lpc40xx.h"
#include <stdio.h>

void gpio1__set_as_input(uint8_t pin_num) { LPC_GPIO1->DIR &= ~(1 << pin_num); }

void GPIO__set_as_input(uint8_t port_num, uint8_t pin_num) {
  if (port_num == 1) {
    LPC_GPIO1->DIR &= ~(1 << pin_num);
  } else if (port_num == 2) {
    LPC_GPIO2->DIR &= ~(1 << pin_num);
  } else if (port_num == 3) {
    LPC_GPIO3->DIR &= ~(1 << pin_num);
  } else {
    printf("Port number is not valid");
  }
}

void GPIO__set_as_output(uint8_t port_num, uint8_t pin_num) {
  if (port_num == 1) {
    LPC_GPIO1->DIR |= (1 << pin_num);
  } else if (port_num == 2) {
    LPC_GPIO2->DIR |= (1 << pin_num);
  } else if (port_num == 3) {
    LPC_GPIO3->DIR |= (1 << pin_num);
  } else {
    printf("Port number is not valid");
  }
}

void GPIO__set_high(uint8_t port_num, uint8_t pin_num) {
  if (port_num == 1) {
    LPC_GPIO1->PIN |= (1 << pin_num);
  } else if (port_num == 2) {
    LPC_GPIO2->PIN |= (1 << pin_num);
  } else if (port_num == 3) {
    LPC_GPIO3->PIN |= (1 << pin_num);
  } else {
    printf("Port number is not valid");
  }
}

void GPIO__set_low(uint8_t port_num, uint8_t pin_num) {
  if (port_num == 1) {
    LPC_GPIO1->PIN &= ~(1 << pin_num);
  } else if (port_num == 2) {
    LPC_GPIO2->PIN &= ~(1 << pin_num);
  } else if (port_num == 3) {
    LPC_GPIO3->PIN &= ~(1 << pin_num);
  } else {
    printf("Port number is not valid");
  }
}

void GPIO__set(uint8_t port_num, uint8_t pin_num, bool high) {
  if (high == true) {
    LPC_GPIO1->PIN |= (1 << pin_num);
  } else {
    LPC_GPIO0->PIN &= ~(1 << pin_num);
  }
}

bool GPIO__get_level(uint8_t port_num, uint8_t pin_num) {
  {
    if (LPC_GPIO1->PIN & (1 << pin_num)) {
      return true;
    } else {
      return false;
    }
  }
}