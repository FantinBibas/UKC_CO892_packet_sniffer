cmake_minimum_required(VERSION 3.10)
project(packet-sniffer)

set(CMAKE_CXX_STANDARD 17)

add_executable(sniffer sniffer.c device_handle.c capture.c device_handle.h file_handle.c file_handle.h capture.h sniffer.h)

target_link_libraries(sniffer pcap)
