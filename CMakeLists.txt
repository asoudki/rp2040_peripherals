# CMakeLists.txt

# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

# Set project name and type
project(rp2040_peripherals C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Catch out of date Pico SDK
if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add FreeRTOS
add_subdirectory(freertos)

# Add compile options
add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

# Add common libraries
add_subdirectory(common_lib)

# Add subdirectories for peripheral libraries
add_subdirectory(hc_06)
add_subdirectory(hc_sr04)
add_subdirectory(mpu_6050)
add_subdirectory(dc_motor)

# Create the hc_06_demo executable
add_executable(hc_06_demo hc_06_demo.c)
target_link_libraries(hc_06_demo pico_stdlib hc_06)
pico_add_extra_outputs(hc_06_demo)

# Create the hc_sr_04_demo executable
add_executable(hc_sr04_demo hc_sr04_demo.c)
target_link_libraries(hc_sr04_demo pico_stdlib hc_sr04)
pico_enable_stdio_usb(hc_sr04_demo 1)
pico_enable_stdio_uart(hc_sr04_demo 0)
pico_add_extra_outputs(hc_sr04_demo)

# Create the mpu_6050_demo executable
add_executable(mpu_6050_demo mpu_6050_demo.c)
target_link_libraries(mpu_6050_demo pico_stdlib mpu_6050)
pico_enable_stdio_usb(mpu_6050_demo 1)
pico_enable_stdio_uart(mpu_6050_demo 0)
pico_add_extra_outputs(mpu_6050_demo)

# Create the mpu_6050_demo executable
add_executable(dc_motor_demo dc_motor_demo.c)
target_link_libraries(dc_motor_demo pico_stdlib dc_motor)
pico_enable_stdio_usb(dc_motor_demo 1)
pico_enable_stdio_uart(dc_motor_demo 0)
pico_add_extra_outputs(dc_motor_demo)

# Create the edf_demo executable
add_executable(edf_demo edf_demo.c)
target_link_libraries(edf_demo edf pico_stdlib hardware_timer freertos)
pico_enable_stdio_usb(edf_demo 1)
pico_enable_stdio_uart(edf_demo 0)
pico_add_extra_outputs(edf_demo)

# Create the integration_demo executable
add_executable(integration_demo integration_demo.c)
target_link_libraries(integration_demo pico_stdlib hc_06 hc_sr04 mpu_6050 edf freertos)
pico_enable_stdio_usb(integration_demo 1)
pico_enable_stdio_uart(integration_demo 0)
pico_add_extra_outputs(integration_demo)

# Repeat for any other demo executables