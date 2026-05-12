cmake_minimum_required(VERSION 3.16)

project(c_binary_protocol_crc C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(example_binary_protocol
    example/main.c
    src/crc8.c
    src/protocol_parser.c
    src/protocol.c
)

add_executable(test_binary_protocol
    tests/test_protocol.c
    src/crc8.c
    src/protocol_parser.c
    src/protocol.c
)