#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/timer.h"

//define the hardware gpio pins for each LED. Code below this is optimized to allow
//changes to these numbers based on how you want to wire to the RP2040
const uint led_pins[9] = {15, 14, 13, 12, 11, 10, 16, 17, 18};

//define pins for rgb led
const uint red = 1;
const uint green = 2;
const uint blue = 3;
//define pwm slices for rgb led pins
uint red_slice = pwm_gpio_to_slice_num(red);
uint green_slice = pwm_gpio_to_slice_num(green);
uint blue_slice = pwm_gpio_to_slice_num(blue);

//General function for changing the RGB_LED with three simple parameters
void changeColor(uint16_t red_lev, uint16_t green_lev, uint16_t blue_lev) //Change the pwm params of each RGB LED color to the RGB value of desired color
{

    //if statements set PWM Channel to A if gpio pin is even and to B if odd
    pwm_set_chan_level(red_slice, PWM_CHAN_B, red_lev);
    pwm_set_chan_level(green_slice, PWM_CHAN_A, green_lev);
    pwm_set_chan_level(blue_slice, PWM_CHAN_B, blue_lev);
    return;
}

//Functions to display the colors Red White and Blue
void redLight()
{
    changeColor(255, 0, 0);
    return;
}
void whiteLight()
{
    changeColor(255, 255, 255);
    return;
}
void blueLight()
{
    changeColor(0, 0, 255);
    return;
}

//Begin main function
int main()
{
    stdio_init_all(); //enable serial communication over USB connection

    //initialize all regular LEDS and configure to output
    for(int i = 0; (unsigned)i < sizeof(led_pins)/sizeof(int); i++)
    {
        gpio_init(led_pins[i]);
        gpio_set_dir(led_pins[i], GPIO_OUT);
    }
    bool gpio_values[sizeof(led_pins)/sizeof(int)];
    for(int i = 0; (unsigned)i < (sizeof(gpio_values)/sizeof(int)); i++)
    {
        gpio_values[i] = 0;
    }

    //assign rbg pins to the pwm
    gpio_set_function(red, GPIO_FUNC_PWM);
    gpio_set_function(green, GPIO_FUNC_PWM);
    gpio_set_function(blue, GPIO_FUNC_PWM);
    //set rgb pwm wraps
    pwm_set_wrap(red_slice, 255);
    pwm_set_wrap(green_slice, 255);
    pwm_set_wrap(blue_slice, 255);

    //set rgb initial pwm channel levels to allow for rewiring between even and odd
    //gpio pins with minimal code changes
    pwm_set_chan_level(red_slice, PWM_CHAN_B, 0);
    pwm_set_chan_level(green_slice, PWM_CHAN_A, 0);
    pwm_set_chan_level(blue, PWM_CHAN_B, 0);
    //enable all pwm channels
    pwm_set_enabled(red_slice, true);
    pwm_set_enabled(green_slice, true);
    pwm_set_enabled(blue_slice, true);

    //initialize variables to be changed randomly in every iteration of the main loop
    int toggle_index, rgb_color;

    while(1) //begin main infinite loop
    {
        srand(time(0));
        
        toggle_index = rand() % (sizeof(led_pins)/sizeof(int));
        if(gpio_values[toggle_index] == 1)
        {
            gpio_put(led_pins[toggle_index], 0);
            gpio_values[toggle_index] = 0;
        }
        else
        {
            gpio_put(led_pins[toggle_index], 1);
            gpio_values[toggle_index] = 1;
        }

        //randomly change the rgb_led
        rgb_color = rand() % 3;
        if(rgb_color == 0)
        {
            redLight();
        }
        else if(rgb_color == 1)
        {
            whiteLight();
        }
        else if(rgb_color == 2)
        {
            blueLight();
        }

        //randomly choose a delay between 1/10 second to 1 seconds to wait before next loop
        sleep_ms((rand()%10)*100);
    }
    return 5;
}