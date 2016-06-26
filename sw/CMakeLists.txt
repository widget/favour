# This is a dummy cmake to suppress some of CLion's many many complaints.
#
# DO NOT USE THIS TO ACTUALLY BUILD THE PROJECT

cmake_minimum_required(VERSION 3.5)
project(favour)

SET(CMAKE_SYSTEM_NAME Generic)

SET(DEVICE "at90usb162")
SET(FREQ "8000000")

SET(CMAKE_C_COMPILER avr-gcc)
SET(CMAKE_CXX_COMPILER avr-g++)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -IConfig/ -mcu=${DEVICE} -DF_CPU=${FREQ}UL -Os")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 -IConfig/ -mcu=${DEVICE} -DF_CPU=${FREQ}UL -Os")

set(SOURCE_FILES
    Descriptors.c
    Descriptors.h
    Favour.c
    Favour.h
    Patterns.h
    Board/Board.h
    Board/Buttons.h
    Board/LEDs.h)

add_executable(favour ${SOURCE_FILES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-objcopy -O ihex -R.eeprom ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex)
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load"  --change-section-lma .eeprom=0 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.eep)
ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME} POST_BUILD COMMAND avr-size ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} --mcu=${DEVICE} --format=avr)