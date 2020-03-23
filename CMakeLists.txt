cmake_minimum_required(VERSION 3.10)
project(packet-sniffer)

set(CMAKE_CXX_STANDARD 17)

add_executable(sniffer main.c)

target_link_libraries(sniffer pcap)
