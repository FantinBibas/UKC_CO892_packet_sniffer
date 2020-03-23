cmake_minimum_required(VERSION 3.10)
project(packet-sniffer)

set(CMAKE_CXX_STANDARD 17)

add_executable(sniffer sniffer.c device_handle.c capture.c device_handle.h file_handle.c file_handle.h capture.h sniffer.h)

IF (WIN32)
    add_definitions(-DWPCAP -DHAVE_REMOTE)
    include_directories(C:/WpdPack/Include)
    target_link_libraries(sniffer C:/WpdPack/Lib/x64/Packet.lib C:/WpdPack/Lib/x64/wpcap.lib)
ELSE ()
    target_link_libraries(sniffer pcap)
ENDIF ()
