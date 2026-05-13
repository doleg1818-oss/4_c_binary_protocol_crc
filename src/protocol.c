#include "protocol.h"
#include "crc8.h"

bool protocol_build_packet(
    uint8_t type,
    const uint8_t *payload,
    uint8_t payload_len,
    uint8_t *out_buffer,
    size_t out_buffer_size,
    size_t *out_packet_len
)
{
    if(payload == NULL || out_buffer == NULL || out_packet_len == NULL)
    {
        return false;
    }
    if(payload_len > PROTOCOL_MAX_PAYLOAD_SIZE)
    {
        return false;
    }
    size_t total_packet_size = payload_len + PROTOCOL_OWERHEAD_SIZE;

    if(out_buffer_size < total_packet_size)
    {
        return false;
    }

    out_buffer[0] = PROTOCOL_HEADER_1;
    out_buffer[1] = PROTOCOL_HEADER_2;
    out_buffer[2] = payload_len;
    out_buffer[3] = type;

    for(uint8_t i = 0; i < payload_len; i++)  // Copy payload into out buffer
    {
        out_buffer[4 + i] = payload[i];
    }
    uint8_t crc = crc8_calculate(out_buffer, total_packet_size - 1); // copy CRC into buffer
    out_buffer[total_packet_size - 1] = crc;

    *out_packet_len = total_packet_size;

    return true;
}

bool protocol_parse_packet(const uint8_t *packet, size_t packet_len, protocol_packed_t *out_packet)
{
    if(packet == NULL ||  out_packet == NULL)
    {
        return false;
    }
    
    if(packet_len < PROTOCOL_OWERHEAD_SIZE)
    {
        return false;
    }

    if(packet[0] != PROTOCOL_HEADER_1 || packet[1] != PROTOCOL_HEADER_2)
    {
        return false;
    }

    uint8_t payload_len = packet[2];

    if(payload_len > PROTOCOL_MAX_PAYLOAD_SIZE)
    {
        return false;
    }

    size_t expected_packet_size = payload_len + PROTOCOL_OWERHEAD_SIZE;

    if(packet_len != expected_packet_size)
    {
        return false;
    }

    uint8_t received_crc = packet[packet_len - 1];
    uint8_t calculated_crc = crc8_calculate(packet, packet_len - 1);
    
    if(received_crc != calculated_crc)
    {
        return false;
    }

    out_packet->type = packet[3];
    out_packet->payload_len = payload_len;

    for(uint8_t i = 0; i < payload_len; i++)
    {
        out_packet->payload[i] = packet[4+i];
    }

    return true;
}