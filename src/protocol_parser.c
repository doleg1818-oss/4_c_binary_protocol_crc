#include "protocol_parser.h"

void protocol_parser_init(protocol_parser_t *parser)
{
    if(parser == NULL)
    {
        return;
    }

    parser->state = PARSER_WAIT_HEADER_1;
    parser->index = 0;
    parser->payload_len = 0;
}

bool protocol_parser_process_byte(
    protocol_parser_t *parser,
    uint8_t byte,
    protocol_packed_t *out_packet
)
{
    if(parser == NULL || out_packet == NULL)
    {
        return false;
    }

    switch(parser -> state)
    {
        case PARSER_WAIT_HEADER_1:
        if(byte == PROTOCOL_HEADER_1)
        {
            parser -> buffer[0] = byte;
            parser -> index = 1;
            parser -> state = PARSER_WAIT_HEADER_2;
        }
        break;

        case PARSER_WAIT_HEADER_2:
            if(byte == PROTOCOL_HEADER_2)
            {
                parser -> buffer[1] = byte;
                parser -> index = 2;
                parser -> state = PARSER_READ_LENGTH;
            }
            else    // If will be wrong HEADER 2 than reset parser, and waite HEADER 1 again.
            {
                parser -> state = PARSER_WAIT_HEADER_1;
                parser -> index = 0;
            }   
            break;

        case PARSER_READ_LENGTH:
            if(byte > PROTOCOL_MAX_PAYLOAD_SIZE)
            {
                protocol_parser_init(parser);
                break;
            }
            else
            {
                parser -> payload_len = byte;
                parser ->buffer[parser->index++] = byte;
                parser->state = PARSER_READ_TYPE;
            }
            break;

        case PARSER_READ_TYPE:
            parser->buffer[parser->index++] = byte;
            if(parser->payload_len == 0)
            {
                parser->state = PARSER_READ_CRC;
            }
            else
            {
                parser->state = PARSER_READ_PAYLOAD;
            }
            break;

        case PARSER_READ_PAYLOAD:
            parser->buffer[parser->index++] = byte;
            if(parser->index == (size_t)(4U + parser->payload_len))
            {
                parser->state = PARSER_READ_CRC;
            }    
            break;

        case PARSER_READ_CRC:
            parser->buffer[parser->index++] = byte;
            bool status = protocol_parse_packet(parser->buffer, parser->index, out_packet);
            protocol_parser_init(parser);
            return status;
        break;

        default:
            protocol_parser_init(parser);
            break;
    }
    return false;
}