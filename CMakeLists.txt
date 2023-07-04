add_executable(independence_day_lightshow
        independence_day_lightshow.cpp
        )

# pull in common dependencies
target_link_libraries(independence_day_lightshow pico_stdlib hardware_gpio hardware_pwm hardware_timer)

# enable usb output, disable uart output
pico_enable_stdio_usb(independence_day_lightshow 1)
pico_enable_stdio_uart(independence_day_lightshow 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(independence_day_lightshow)
