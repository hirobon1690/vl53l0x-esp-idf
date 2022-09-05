/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <VL53L0X.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "i2c.h"

VL53L0X sensor;

extern "C" {
void app_main(void);
}

void app_main() {
    i2c.init();
    sensor.setTimeout(500);
    if (!sensor.init()) {
        Serial.println("Failed to detect and initialize sensor!");
        while (1) {
            vTaskDelay(10 / portTICK_RATE_MS);
        }
    }
    // Start continuous back-to-back mode (take readings as
    // fast as possible).  To use continuous timed mode
    // instead, provide a desired inter-measurement period in
    // ms (e.g. sensor.startContinuous(100)).
    sensor.startContinuous();
    while (1) {
        printf("%d",sensor.readRangeContinuousMillimeters());
        if (sensor.timeoutOccurred()) {
            printf(" TIMEOUT");
        }
        printf("\n");
        vTaskDelay(10 / portTICK_RATE_MS);
    }
}
