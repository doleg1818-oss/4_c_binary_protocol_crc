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

    for(size_t i = 0; i < length; i++) 
    {
        crc = crc ^ data[i];    
        for(uint8_t bit = 0; bit < 8; bit++)  
        {
            if((crc & 0x80) != 0)             
            {
                crc = (uint8_t)((crc << 1) ^ CRC8_POLYNOMIAL);  // add polinome? if last bite was 1
            }
            else        
            {
                crc <<= 1;  
            }
        }
    }
    return crc;
}