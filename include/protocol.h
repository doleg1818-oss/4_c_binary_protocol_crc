#ifndef PROTOCOL_H 
#define PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define PROTOCOL_HEADER_1 0xAAU
#define PROTOCOL_HEADER_2 0x55U

#define PROTOCOL_MAX_PAYLOAD_SIZE 32U       // bits
#define PROTOCOL_OWERHEAD_SIZE 5U           // bayts

#define PROTOCOL_MAX_PACKET_SIZE \
    (PROTOCOL_MAX_PAYLOAD_SIZE + PROTOCOL_OWERHEAD_SIZE)

typedef struct 
{
    uint8_t type;
    uint8_t payload[PROTOCOL_MAX_PAYLOAD_SIZE];
    uint8_t payload_len;
} protocol_packed_t;

bool protocol_build_packet(
    uint8_t type,
    const uint8_t *payload,
    uint8_t pyuload_len,
    uint8_t *out_buffer,
    size_t out_buffer_size,
    size_t *out_packet_len
);

bool protocol_parse_packet(
    const uint8_t *packet, size_t packet_len, 
    protocol_packed_t *out_packet);




#endif

