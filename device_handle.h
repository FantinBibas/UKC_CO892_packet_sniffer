//
// Created by neodar on 23/03/2020.
//

#ifndef PACKET_SNIFFER__DEVICE_HANDLE_H_
#define PACKET_SNIFFER__DEVICE_HANDLE_H_

#include <pcap.h>
#include "sniffer.h"

void close_capture_handle(pcap_t *handle);
pcap_t *create_filtered_capture_handle(const char *device,
                                       const char *filter_expression,
                                       const sniffer_options_t *options);

#endif //PACKET_SNIFFER__DEVICE_HANDLE_H_
