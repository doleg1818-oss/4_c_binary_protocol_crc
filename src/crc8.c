#include "crc8.h"

#define CRC8_POLYNOMIAL 0x07U
#define CRC8_INITIAL   0x00U


uint8_t crc8_calculate(const uint8_t *data, size_t length)
{
    uint8_t crc = CRC8_INITIAL;

    if(data == NULL)
    {
        return 0;
    }

    for(size_t i = 0; i < length; i++)     // all bytes 
    {
        crc = crc ^ data[i];                    // XOR
        for(uint8_t bit = 0; bit < 8; bit++)    // do with all 8 bits
        {
            if((crc & 0x80) != 0)           // Check the older bit (MSB). if bit was set?     
            {
                crc = (uint8_t)((crc << 1) ^ CRC8_POLYNOMIAL);  // Shift left and apply the generator polinomial.
            }
            else        
            {
                crc <<= 1;  
            }
        }
    }
    return crc;
}