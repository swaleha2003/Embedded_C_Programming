#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void) {
    // Hardware Register Pointers
    volatile uint32_t *GPIO_ENABLE_REG = (volatile uint32_t *)0x3FF44020;
    volatile uint32_t *GPIO_OUT_REG    = (volatile uint32_t *)0x3FF44004;

    // Step 1: Configure GPIO 4 as an output by setting Bit 4 to 1
    *GPIO_ENABLE_REG |= (1 << 4);

    // Infinite execution loop
    while (1) {
        // Step 2: Turn Red LED ON (Set Bit 4 to 1)
        *GPIO_OUT_REG |= (1 << 4);
        // Sleep for 200 milliseconds to let background RTOS tasks run
        vTaskDelay(pdMS_TO_TICKS(200)); 

        // Step 3: Turn Red LED OFF (Clear Bit 4 to 0)
        *GPIO_OUT_REG &= ~(1 << 4);
        // Sleep for 800 milliseconds
        vTaskDelay(pdMS_TO_TICKS(800)); 
    }
}