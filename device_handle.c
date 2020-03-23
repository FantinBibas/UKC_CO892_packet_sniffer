//
// Created by neodar on 23/03/2020.
//

#include <pcap.h>
#include "device_handle.h"

static pcap_t *create_capture_handle(const char *device) {
  char error_buffer[PCAP_ERRBUF_SIZE];
  pcap_t *handle = pcap_open_live(device, BUFSIZ, 1, 500, error_buffer);

  if (!handle) {
    fprintf(stderr, "Error while opening device %s for capture: %s\n", device, error_buffer);
  }
  return handle;
}

static int apply_filter_to_handle(pcap_t *handle, const char *device, const char *filter_expression) {
  char error_buffer[PCAP_ERRBUF_SIZE];
  bpf_u_int32 netmask;
  bpf_u_int32 ip_address;
  struct bpf_program compiled_filter;

  if (pcap_lookupnet(device, &ip_address, &netmask, error_buffer) < 0) {
    fprintf(stderr, "Error while getting network information from device %s: %s\n", device, error_buffer);
    netmask = PCAP_NETMASK_UNKNOWN;
  }
  if (pcap_compile(handle, &compiled_filter, filter_expression, 1, netmask)) {
    fprintf(stderr, "Error while compiling network filter \"%s\": %s\n", filter_expression, pcap_geterr(handle));
    return -2;
  }
  if (pcap_setfilter(handle, &compiled_filter)) {
    fprintf(stderr, "Error while setting network filter \"%s\": %s\n", filter_expression, pcap_geterr(handle));
    return -3;
  }
  return 0;
}

void close_capture_handle(pcap_t *handle) {
  if (handle) {
    pcap_close(handle);
  }
}

pcap_t *create_filtered_capture_handle(const char *device,
                                       const char *filter_expression,
                                       const sniffer_options_t *options) {
  pcap_t *handle;

  if (options->verbose) {
    printf("Creating capture handle...\n");
  }
  handle = create_capture_handle(device);
  if (handle) {
    if (options->verbose) {
      printf("-> Success!\nApplying filter \"%s\" to capture handle...\n", filter_expression);
    }
    if (apply_filter_to_handle(handle, device, filter_expression) < 0) {
      close_capture_handle(handle);
      return NULL;
    }
    if (options->verbose) {
      printf("-> Success!\n");
    }
  }
  return handle;
}
