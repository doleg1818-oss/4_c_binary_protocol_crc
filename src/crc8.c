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
    // ПОбітове виключаюче або 

    for(size_t i = 0; i < length; i++) // Проходимо весі байти бувера
    {
        crc = crc ^ data[i];    
        for(uint8_t bit = 0; bit < 8; bit++)  // ПРоходимо кожен біт в байті
        {
            if((crc & 0x80) != 0)             // порівнюємо з 7 бітом
            {
                crc = (uint8_t)((crc << 1) ^ CRC8_POLYNOMIAL);  // Додаєм поліном якщо останній байт був 1
            }
            else        // Якщо останній байт був 0 просто зсуваємо
            {
                crc <<= 1;  
            }
        }
    }
    return crc;
}