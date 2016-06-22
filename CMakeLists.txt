cmake_minimum_required(VERSION 3.2)
project(arduino_flotilla_cplayground)

include(CMakeListsPrivate.txt)

add_definitions(-DF_CPU=8000000L)
add_definitions(-DPLATFORMIO=021003)
add_definitions(-DARDUINO_ARCH_AVR)
add_definitions(-DARDUINO_AVR_FEATHER32U4)
add_definitions(-DUSB_VID=0x239A)
add_definitions(-DUSB_PID=0x800C)
add_definitions(-DUSB_PRODUCT="Feather 32u4")
add_definitions(-DUSB_MANUFACTURER="Adafruit")
add_definitions(-DARDUINO=10608)
add_definitions(-D__AVR_ATmega32U4__)

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_PROGRAM ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target program
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOADFS ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPDATE_ALL ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion update
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(arduino_flotilla_cplayground
    src/main.cpp
)
