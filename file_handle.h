//
// Created by neodar on 23/03/2020.
//

#ifndef PACKET_SNIFFER__FILE_HANDLE_H_
#define PACKET_SNIFFER__FILE_HANDLE_H_

#include <pcap.h>
#include "capture.h"

void close_output_capture_file(pcap_dumper_t *file);
pcap_dumper_t *open_output_capture_file(pcap_t *handle, const char *filename);
void save_packet_to_file(pcap_dumper_t *file, packet_with_header_t *packet);

#endif //PACKET_SNIFFER__FILE_HANDLE_H_
