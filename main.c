#include <stdbool.h>
#include <stdint.h>
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "boards.h"

#define ID_SIZE 4
#define BUTTON_PIN BSP_BUTTON_0 // Assuming there is a BUTTON_0 defined in boards.h

void led_on(uint32_t led_pin) {
    nrf_gpio_pin_set(led_pin);
}

void led_off(uint32_t led_pin) {
    nrf_gpio_pin_clear(led_pin);
}

bool is_button_pressed() {
    // Assuming active low button
    return nrf_gpio_pin_read(BUTTON_PIN) == 0; 
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    int blink_pattern[ID_SIZE] = {7, 2, 0, 3};
    int current_led = 0; // Start from the first LED
    int blink_count = 0; // Blink count for the current LED

    // Initialize button and LEDs
    bsp_board_init(BSP_INIT_LEDS);
    nrf_gpio_cfg_input(BUTTON_PIN, NRF_GPIO_PIN_PULLUP); // Configure the button with a pull-up resistor

    while (true)
    {
        if (is_button_pressed())
        {
            // If button is pressed and we have not finished blinking the current LED
            printf("Button is pressed.\n");
            if (blink_count < blink_pattern[current_led])
            {
                led_on(current_led);
                nrf_delay_ms(2000);
                led_off(current_led);
                nrf_delay_ms(2000);
                blink_count++;
            }
            else
            {
                // Move to the next LED and reset blink count
                current_led = (current_led + 1) % ID_SIZE;
                blink_count = 0;
                nrf_delay_ms(2000); // Delay between different LEDs
            }
        }
        else
        {
            // If button is not pressed, ensure all LEDs are off and maintain current state
            for (int i = 0; i < ID_SIZE; i++)
            {
                led_off(i);
            }
            blink_count = blink_pattern[current_led] > 0 ? blink_count : 0; // Reset blink_count only if it finished for the current led
            // No delay here as we want to check the button state continuously
        }
    }
}
