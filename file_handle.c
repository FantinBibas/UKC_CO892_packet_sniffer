//
// Created by neodar on 23/03/2020.
//

#include <pcap.h>
#include "file_handle.h"

pcap_dumper_t *open_output_capture_file(pcap_t *handle, const char *filename) {
  pcap_dumper_t *file = pcap_dump_open(handle, filename);

  if (!file) {
    fprintf(stderr, "Error while opening output capture file for writing \"%s\": %s\n", filename, pcap_geterr(handle));
  }
  return file;
}

void save_packet_to_file(pcap_dumper_t *file, packet_with_header_t *packet) {
  pcap_dump((u_char *) file, packet->header, packet->packet);
}

void close_output_capture_file(pcap_dumper_t *file) {
  if (file) {
    pcap_dump_close(file);
  }
}
