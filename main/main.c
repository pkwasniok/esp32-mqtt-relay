#include "setup.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    int result = app_setup();

    if (result == SETUP_SUCCESS) {
        printf("Success!\n");
    } else {
        printf("Error!\n");
    }

    while (1) {
        printf("Hello, world!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

