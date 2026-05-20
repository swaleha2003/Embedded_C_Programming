#include <stdio.h>
#include<stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main() {
volatile uint32_t *GPIO_ENABLE_REG = (volatile uint32_t *)0x3FF44020;
volatile uint32_t *GPIO_OUT_REG = (volatile uint32_t *)0x3FF44004;
/*Using your pointer to the Enable Register and the bitwise OR operator, set Bit 2 to 1. This physically connects the silicon logic to the pin pad, configuring GPIO 2 as an output.*/
*GPIO_ENABLE_REG |=(1<<2);
*GPIO_OUT_REG |=(1<<2);

}
