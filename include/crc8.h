#ifndef CRC8_H
#define CRC8_H

#include "stdint.h"
#include "stddef.h"

uint8_t crc8_calculate(const uint8_t *data, size_t lenght);

#endif