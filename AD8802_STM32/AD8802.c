#include "AD8802.h"

//                    --- AD8802 SPI data transmission ---
// _________________________________________________________________________
// |  0     0     0     0  |  0     0     0     0     0     0     0     0  |
// |        A3 - A0        |                    D7 - D0                    |
// |     Output address    |        Output value [0 - 255 = 0 - Vcc]       |
//
// SPI mode : 0

// Constructor to initialize the DAC object
void AD8802_init(AD8802* ad8802, uint16_t CS, GPIO_TypeDef* peripheral, SPI_HandleTypeDef spi_handler,
		void(*setup)(AD8802*), uint8_t(*output)(AD8802*)) {

	HAL_GPIO_WritePin(peripheral, CS, GPIO_PIN_SET);

	ad8802->OX = 12;
    ad8802->CS = CS;
    ad8802->peripheral = peripheral;
    ad8802->spi_handler = spi_handler;

    ad8802->setup = setup;
    ad8802->output = output;
}

// Function to initialize the DAC outputs to 0
void AD8802_setup(AD8802* ad8802)
{
    for (uint8_t i = 0; i < ad8802->OX; i++) // should replace with OX
    {
        ad8802->output(ad8802, i, 0x00);
    }
}

// Function to set output on a specific DAC pin
uint8_t AD8802_output(AD8802* ad8802, uint8_t pinID, uint8_t val)
{
    if (pinID > 0x0B || val > 0xFF)
    {
        return -1;
    }
    uint8_t data[2];
    data[1] = pinID;
    data[0] = val;
    HAL_GPIO_WritePin(ad8802->peripheral, ad8802->CS, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&(ad8802->spi_handler), &data, 1, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(ad8802->peripheral, ad8802->CS, GPIO_PIN_SET);
    return 0;
}
