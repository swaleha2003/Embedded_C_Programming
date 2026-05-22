#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Hardware Register Pointers (Global scope for task access)
volatile uint32_t *GPIO_ENABLE_REG = (volatile uint32_t *)0x3FF44020;
volatile uint32_t *GPIO_OUT_REG    = (volatile uint32_t *)0x3FF44004;

// Task 1: Heartbeat (Blue LED on GPIO 2) - Symmetric Toggling
void heartbeat_task(void *pvParameters) {
    while (1) {
        // Symmetric toggle using Bitwise XOR (^)
        *GPIO_OUT_REG ^= (1 << 2);
        
        // Wait 500ms before toggling again (500ms ON, 500ms OFF)
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// Task 2: Hazard Beacon (Red LED on GPIO 4) - Asymmetric Pulsing
void hazard_task(void *pvParameters) {
    while (1) {
        // Turn Red LED ON (Set Bit 4)
        *GPIO_OUT_REG |= (1 << 4);
        vTaskDelay(pdMS_TO_TICKS(100));

        // Turn Red LED OFF (Clear Bit 4)
        *GPIO_OUT_REG &= ~(1 << 4);
        vTaskDelay(pdMS_TO_TICKS(900));
    }
}

void app_main(void) {
    // ---- Hardware Initialization Phase ----
    // Configure BOTH GPIO 2 and GPIO 4 as outputs by setting their bits to 1
    *GPIO_ENABLE_REG |= (1 << 2);
    *GPIO_ENABLE_REG |= (1 << 4);

    // ---- RTOS Scheduler Phase ----
    // Spawn the System Heartbeat Task (Priority 1)
    xTaskCreate(
        heartbeat_task,     // Function name
        "heartbeat",        // Debug name
        2048,               // Stack size in words
        NULL,               // No parameters passed
        1,                  // Priority
        NULL                // No task handle needed
    );

    // Spawn the Hazard Beacon Task (Priority 1)
    xTaskCreate(
        hazard_task,        // Function name
        "hazard",           // Debug name
        2048,               // Stack size in words
        NULL,               // No parameters passed
        1,                  // Priority
        NULL                // No task handle needed
    );

    // app_main finishes and exits here. The FreeRTOS scheduler takes over
    // and jumps between heartbeat_task and hazard_task automatically.
}