#include "relay.h"
#include "config.h"
#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

EventGroupHandle_t event_group_relay;

#define GPIO_RELAY_A CONFIG_GPIO_RELAY_A
#define GPIO_RELAY_B CONFIG_GPIO_RELAY_B

#define BIT_ENABLE_A  BIT0
#define BIT_DISABLE_A BIT1
#define BIT_ENABLE_B  BIT2
#define BIT_DISABLE_B BIT3

void relay_setup(void) {
    gpio_set_direction(GPIO_RELAY_A, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_RELAY_B, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_RELAY_A, 1);
    gpio_set_level(GPIO_RELAY_B, 1);

    event_group_relay = xEventGroupCreate();
}

void relay_enable(int channel) {
    switch (channel) {
        case RELAY_CH_A:
            xEventGroupSetBits(event_group_relay, BIT_ENABLE_A);
            break;
        case RELAY_CH_B:
            xEventGroupSetBits(event_group_relay, BIT_ENABLE_A);
            break;
    }
}

void relay_disable(int channel) {
    switch (channel) {
        case RELAY_CH_A:
            xEventGroupSetBits(event_group_relay, BIT_DISABLE_A);
            break;
        case RELAY_CH_B:
            xEventGroupSetBits(event_group_relay, BIT_DISABLE_B);
            break;
    }
}

void relay_task(void* pvParameters) {
    while (1) {
        EventBits_t event_bits = xEventGroupWaitBits(event_group_relay, BIT_ENABLE_A | BIT_DISABLE_A | BIT_ENABLE_A | BIT_DISABLE_B, pdTRUE, pdFALSE, portMAX_DELAY);

        if (event_bits & BIT_ENABLE_A) {
            gpio_set_level(GPIO_RELAY_A, 0);
        }

        if (event_bits & BIT_DISABLE_A) {
            gpio_set_level(GPIO_RELAY_A, 1);
        }

        if (event_bits & BIT_ENABLE_B) {
            gpio_set_level(GPIO_RELAY_B, 0);
        }

        if (event_bits & BIT_DISABLE_B) {
            gpio_set_level(GPIO_RELAY_B, 1);
        }
    }
}

