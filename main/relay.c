#include "relay.h"
#include "config.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define TAG "RELAY"

#define GPIO_RELAY_A CONFIG_GPIO_RELAY_A
#define GPIO_RELAY_B CONFIG_GPIO_RELAY_B

void relay_setup(void) {
    gpio_set_direction(GPIO_RELAY_A, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_RELAY_B, GPIO_MODE_OUTPUT);

    relay_disable(RELAY_CH_A);
    relay_disable(RELAY_CH_B);
}

void relay_enable(int channel) {
    switch (channel) {
        case RELAY_CH_A:
            gpio_set_level(GPIO_RELAY_A, 0);
            ESP_LOGI(TAG, "Enabled channel A");
            break;
        case RELAY_CH_B:
            gpio_set_level(GPIO_RELAY_B, 0);
            ESP_LOGI(TAG, "Enabled channel B");
            break;
    }
}

void relay_disable(int channel) {
    switch (channel) {
        case RELAY_CH_A:
            gpio_set_level(GPIO_RELAY_A, 1);
            ESP_LOGI(TAG, "Disabled channel A");
            break;
        case RELAY_CH_B:
            gpio_set_level(GPIO_RELAY_B, 1);
            ESP_LOGI(TAG, "Disabled channel B");
            break;
    }
}

