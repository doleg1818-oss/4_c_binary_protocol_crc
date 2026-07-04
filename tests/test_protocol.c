#include <stdio.h>
#include "stddef.h"
#include <assert.h>

#include "crc8.h"
#include "protocol_parser.h"
#include "protocol.h"

#include "assert.h"
#include <stdio.h>

#include "protocol.h"

static void print_buffer_hex(const uint8_t *buffer, size_t length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%02X ", buffer[i]);
    }
    printf("\n");
}

int main(void)
{
    // uint8_t data1[] = {0x01, 0x02, 0x03};

    // uint8_t crc1 = crc8_calculate(data1, sizeof(data1));
    // printf("CRC1 = 0x%002X\n", crc1);

    // assert(crc8_calculate(NULL, 3) == 0);

    // printf("CRC8 test passed\n");

    ///////////////////////////////////// BUILD PACKET
    uint8_t payload[] = 
    {
        0x19,
        0x32,
        0x48
    };

    uint8_t packet[64] = {0,};
    size_t packet_len = 0;

    bool status = protocol_build_packet(0x01, payload, sizeof(payload), packet, sizeof(packet), &packet_len);

    assert(status == true);

    print_buffer_hex(packet, packet_len);

    printf("Packet build test passed\n");


    //////////////////////////////////////// PARSE PACKET
    protocol_packed_t parsed_packet;   
    bool parse_status = protocol_parse_packet(
        packet, packet_len, &parsed_packet);

    assert(parse_status == true);
    assert(parsed_packet.type == 0x01);
    assert(parsed_packet.payload_len == 3);
    assert(parsed_packet.payload[0] == 0x19);
    assert(parsed_packet.payload[1] == 0x32);
    assert(parsed_packet.payload[2] == 0x48);
    printf("Packet parse test passed\n");

    //////////////////////////////////////// STREAM PARSER TEST
    protocol_parser_t parser;
    protocol_parser_init(&parser);

    protocol_packed_t stream_packet;

    bool packet_ready = false;

    for(size_t i = 0; i < packet_len; i++)
    {
        packet_ready = protocol_parser_process_byte(
            &parser,
            packet[i],
            &stream_packet
        );
    }

    assert(packet_ready == true);

    assert(stream_packet.type == 0x01);
    assert(stream_packet.payload_len == 3);
    assert(stream_packet.payload[0] == 0x19);
    assert(stream_packet.payload[1] == 0x32);
    assert(stream_packet.payload[2] == 0x48);

    printf("Stream parser test passed\n");
        
        return 0;
}



