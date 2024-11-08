#ifndef AD8802_H_
#define AD8802_H_
#include <stdint.h>

class AD8802
{
private:
    const uint8_t OX = 12; // Number of DAC outputs (AD8802)
    uint8_t CS;       // Chip select pin for DAC
    int SPIspeed;

public:
    // Constructor to initialize the DAC object
    AD8802(uint8_t csPin, int speed);
    void setup();
    uint16_t output(uint8_t pinID, uint8_t val);
    void debug();
};

#endif
