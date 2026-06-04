#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/i2c.h"
#include "MPU6050.h"
#include "falldetect.hpp"

// Tag for logging
static const char *TAG = "MPU6050";

// I2C configuration
#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_FREQ_HZ 400000
#define I2C_MASTER_TX_BUF_DISABLE 0
#define I2C_MASTER_RX_BUF_DISABLE 0

// ESP32 I2C pins
#define I2C_MASTER_SDA_IO 21  // GPIO21 (default for many ESP32 boards)
#define I2C_MASTER_SCL_IO 22  // GPIO22 (default for many ESP32 boards)

// Function to initialize I2C
void initI2C() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master = {
            .clk_speed = I2C_MASTER_FREQ_HZ,
        },
        .clk_flags = 0,
    };
    
    ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_MASTER_NUM, conf.mode, 
                                       I2C_MASTER_RX_BUF_DISABLE, 
                                       I2C_MASTER_TX_BUF_DISABLE, 0));
    ESP_LOGI(TAG, "I2C initialized on SDA=%d, SCL=%d", I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO);
}

// Main task to read and print MPU6050 data
void mpu6050_task(void *pvParameters) {
    initI2C();
    FallDetect fall;
    fall.initialize();
    
    while (1) {
        fall.updateData();
        if (fall.isFalling()) printf("You are falling.\n");
        else printf("You are safe.\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Read every 1000ms (1Hz)
    }
}

// Simple example without DMP (Digital Motion Processor)
extern "C" void app_main() {
    ESP_LOGI(TAG, "Starting MPU6050 example...");
    
    // Create the MPU6050 reading task
    xTaskCreate(mpu6050_task, "mpu6050_task", 4096, NULL, 5, NULL);
}