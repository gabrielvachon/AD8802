#ifndef AD8802_H_
#define AD8802_H_

#include <stdint.h>
#include "stm32l4xx_hal.h"

typedef struct AD8802 {

    uint8_t OX; // Number of DAC outputs (AD8802)
    uint16_t CS;       // Chip select pin for DAC
    GPIO_TypeDef* peripheral;
    SPI_HandleTypeDef spi_handler;

    void (*setup)(struct AD8802* ad8802);
    uint8_t (*output)(struct AD8802* ad8802, uint8_t pinID, uint8_t val);
} AD8802;

void AD8802_init(AD8802* ad8802, uint16_t CS, GPIO_TypeDef* peripheral, SPI_HandleTypeDef handler,
		void(*setup)(AD8802*), uint8_t(*output)(AD8802*));

void AD8802_setup(AD8802* ad8802);

uint8_t AD8802_output(AD8802* ad8802, uint8_t pinID, uint8_t val);

#endif
