#include "AD8802.h"
#include <Arduino.h>
#include "component_utils.h"
#include "SPI.h"
#include <stdint.h>

//                    --- AD8802 SPI data transmission ---
// _________________________________________________________________________
// |  0     0     0     0  |  0     0     0     0     0     0     0     0  |
// |        A3 - A0        |                    D7 - D0                    |
// |     Output address    |        Output value [0 - 255 = 0 - Vcc]       |
//
// SPI mode : 0

// Constructor to initialize the DAC object
AD8802::AD8802(uint8_t csPin, int speed) : CS(csPin), SPIspeed(speed)
{
    pinMode(CS, OUTPUT);
    digitalWrite(CS, HIGH);
}

// Function to initialize the DAC outputs to 0
void AD8802::setup()
{
    for (uint8_t i = 0; i < 10; i++) // should replace with OX
    {
        this->output(i, 0x00);
    }
}

// Function to set output on a specific DAC pin
uint16_t AD8802::output(uint8_t pinID, uint8_t val)
{
    if (pinID > 0x0B || val > 0xFF)
    {
        return -1;
    }
    uint16_t data = 0;
    data = (pinID << 8);
    data = (data |= val);
    SPI.beginTransaction(SPISettings(SPIspeed, MSBFIRST, SPI_MODE0));
    digitalWrite(CS, LOW);
    SPI.transfer16(data);
    digitalWrite(CS, HIGH);
    SPI.endTransaction();
    return 0;
}

// Debugging function for DAC
void AD8802::debug()
{
    for (int i = 0; i < OX; i++)
    {
        Serial.print("Output    : ");
        Serial.println(i);
        Serial.println("Value : 255");
        output(i, 0xFF);
        delay(4000);
        Serial.println("Value : 128");
        output(i, 0x80);
        delay(4000);
        Serial.println("Value : 0");
        output(i, 0x00);
        delay(4000);
    }
}
