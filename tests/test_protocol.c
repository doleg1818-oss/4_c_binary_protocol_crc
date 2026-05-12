#include <stdio.h>
#include "stddef.h"
#include <assert.h>

#include "crc8.h"
#include "protocol_porser.h"
#include "protocol.h"


int main(void)
{
    uint8_t data1[] = {0x01, 0x02, 0x03};

    uint8_t crc1 = crc8_calculate(data1, sizeof(data1));
    printf("CRC1 = 0x%002X\n", crc1);

    assert(crc8_calculate(NULL, 3) == 0);

    printf("CRC8 test passed\n");

    return 0;
}