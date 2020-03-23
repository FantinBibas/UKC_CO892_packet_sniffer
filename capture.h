//
// Created by neodar on 23/03/2020.
//

#ifndef PACKET_SNIFFER__CAPTURE_H_
#define PACKET_SNIFFER__CAPTURE_H_

#include <pcap.h>

typedef struct packet_with_header {
  struct pcap_pkthdr *header;
  const u_char *packet;
} packet_with_header_t;

int wait_for_next_packet(pcap_t *handle, packet_with_header_t *packet);

#endif //PACKET_SNIFFER__CAPTURE_H_
