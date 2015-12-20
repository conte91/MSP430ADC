SET(CMAKE_C_COMPILER msp430-gcc)
SET(CMAKE_C_FLAGS "-mmcu=msp430g2553 -Wall -g -O0")

ADD_LIBRARY(msp_adc adc.c)

