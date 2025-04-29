#include "setup.h"
#include "nvs_flash.h"

#define SUCCESS 0
#define ERROR   1

#define STATE_SETUP_NVS   0
#define STATE_SUCCESS     1
#define STATE_ERROR       2

/*
 * Non-volatile storage (NVS) library is designed to store key-value pairs in flash.
*/
int nvs_setup(void) {
    esp_err_t err = nvs_flash_init();

    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        if (nvs_flash_erase() == ESP_OK) {
            err = nvs_flash_init();
        }
    }

    if (err != ESP_OK) {
        return ERROR;
    }

    return SUCCESS;
}

int app_setup(void) {
    int state = STATE_SETUP_NVS;

    while (1) {
        switch (state) {

            case STATE_SETUP_NVS:
                if (nvs_setup() == SUCCESS)
                    state = STATE_SUCCESS;
                else
                    state = STATE_ERROR;
                break;

            case STATE_SUCCESS:
                return SETUP_SUCCESS;
                break;

            case STATE_ERROR:
                return SETUP_ERROR;
                break;

        }
    }

    return SETUP_SUCCESS;
}

