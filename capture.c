//
// Created by neodar on 23/03/2020.
//

#include <pcap.h>
#include "capture.h"

int wait_for_next_packet(pcap_t *handle, packet_with_header_t *packet) {
  int status;

  do {
    status = pcap_next_ex(handle, &(packet->header), &(packet->packet));
  } while (!status);
  if (status < 0) {
    fprintf(stderr, "Error while waiting for next packet to be captured: %s\n", pcap_geterr(handle));
  }
  return status;
}
