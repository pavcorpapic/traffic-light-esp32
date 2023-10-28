#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define GREEN_LED_PIN GPIO_NUM_2  
#define YELLOW_LED_PIN GPIO_NUM_4 
#define RED_LED_PIN GPIO_NUM_5    

void setupTrafficLight() {
    gpio_pad_select_gpio(GREEN_LED_PIN);
    gpio_set_direction(GREEN_LED_PIN, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(YELLOW_LED_PIN);
    gpio_set_direction(YELLOW_LED_PIN, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(RED_LED_PIN);
    gpio_set_direction(RED_LED_PIN, GPIO_MODE_OUTPUT);
}

void trafficLightControl() {
    while (1) {
        // Green light (Green on, Yellow off, Red off)
        gpio_set_level(GREEN_LED_PIN, 1);
        gpio_set_level(YELLOW_LED_PIN, 0);
        gpio_set_level(RED_LED_PIN, 0);
        vTaskDelay(3000 / portTICK_PERIOD_MS); 

        
        gpio_set_level(GREEN_LED_PIN, 0);
        gpio_set_level(YELLOW_LED_PIN, 1);
        gpio_set_level(RED_LED_PIN, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS); 

        
        gpio_set_level(GREEN_LED_PIN, 0);
        gpio_set_level(YELLOW_LED_PIN, 0);
        gpio_set_level(RED_LED_PIN, 1);
        vTaskDelay(3000 / portTICK_PERIOD_MS); 
    }
}

void app_main() {
    setupTrafficLight();
    xTaskCreate(trafficLightControl, "traffic_light_task", 4096, NULL, 5, NULL);
}
