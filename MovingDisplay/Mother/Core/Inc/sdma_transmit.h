
#pragma once
#include "main.h"
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_it.h"

class SDMA_TRANSMIT{
    private:
        uint8_t rxBuf[128];
        int indexRead = 0;
        uint8_t readData = 0;
        uint8_t ID;
        uint8_t rcvBuf[5];
        //uint8_t send_array[3];
        UART_HandleTypeDef* UART;

    public:
        SDMA_TRANSMIT(UART_HandleTypeDef* uart, uint8_t id);
        void begin_dma();
        void check_buf();
//        void send_data(long data);
        volatile uint32_t index;
        uint32_t clock;
        uint8_t mode;
        uint8_t hue;
};


