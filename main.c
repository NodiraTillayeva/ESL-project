#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

#define ID_SIZE 4

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    int blink_pattern[ID_SIZE] = {7, 2, 0, 3};
    bsp_board_init(BSP_INIT_LEDS);
    while (true)
    {
        for (int i = 0; i < ID_SIZE; i++)
        {
            for (int j = 0; j < blink_pattern[i]; j++)
            {
                bsp_board_led_on(i);   
                nrf_delay_ms(500);     
                bsp_board_led_off(i);  
                nrf_delay_ms(500);    
            }
            nrf_delay_ms(1000); 
        }
    }
}
