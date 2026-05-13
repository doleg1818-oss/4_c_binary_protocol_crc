#ifndef PROTOCOL_PARSER_H
#define PROTOCOL_PARSER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include <protocol.h>

typedef enum 
{
    PARSER_WAIT_HEADER_1 = 0,
    PARSER_WAIT_HEADER_2,
    PARSER_READ_LENGTH,
    PARSER_READ_TYPE,
    PARSER_READ_PAYLOAD,
    PARSER_READ_CRC
} protocol_parser_state_t;

typedef struct 
{
    protocol_parser_state_t state;
    uint8_t buffer[PROTOCOL_MAX_PACKET_SIZE];
    size_t index;
    uint8_t payload_len;
}protocol_parser_t;

void protocol_parser_init(protocol_parser_t *parser);
bool protocol_parser_process_byte(
    protocol_parser_t *parser,
    uint8_t byte,
    protocol_packed_t *out_packet
);



#endif