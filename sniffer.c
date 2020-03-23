//
// Created by neodar on 23/03/2020.
//

#include <string.h>
#include <pcap.h>

#include "device_handle.h"
#include "capture.h"
#include "file_handle.h"
#include "sniffer.h"

int print_usage(const char *executable, int error) {
  FILE *output = error ? stderr : stdout;
  fprintf(output, "Packet sniffer.\n");
  fprintf(output, "\nUsage:\n");
  fprintf(output, "  %s -h | --help\n", executable);
  fprintf(output, "  %s device filename [-v]...\n", executable);
  fprintf(output, "\nOptions\n");
  fprintf(output, "  filename\tFilename to use for the output capture file\n");
  fprintf(output, "  device\tNetwork interface to use\n");
  fprintf(output, "  -h --help\tShow this help message\n");
  fprintf(output, "  -v\t\tVerbose output\n");
  return error;
}

int parse_option(const char *argument, sniffer_options_t *options) {
  if (strlen(argument) != 2 || argument[0] != '-') {
    return -1;
  }
  switch (argument[1]) {
    case 'v':
      options->verbose = 1;
      break;
    default:
      return -1;
  }
  return 0;
}

int parse_options(int ac, const char **av, sniffer_options_t *options) {
  for (int i = 0; i < ac; ++i) {
    if (parse_option(av[i], options) < 0) {
      return -1;
    }
  }
  return 0;
}

int perform_capture(const char *device, const char *filename, const sniffer_options_t *options) {
  pcap_t *handle = create_filtered_capture_handle(device, "port 23", options);
  pcap_dumper_t *file;
  packet_with_header_t packet;

  if (!handle) {
    return -1;
  }
  if (options->verbose) {
    printf("Opening output capture file \"%s\"...\n", filename);
  }
  file = open_output_capture_file(handle, filename);
  if (!file) {
    return -2;
  }
  if (options->verbose) {
    printf("-> Success!\nStarting the packet capture...\n");
  }
  for (int i = 0; i < 10; ++i) {
    if (options->verbose) {
      printf("\tCapturing packet %i on %i...\n", i + 1, 10);
    }
    if (wait_for_next_packet(handle, &packet) < 0) {
      return -3;
    }
    if (options->verbose) {
      printf("\t-> Success!\n\t\tSaving packet...\n");
    }
    save_packet_to_file(file, &packet);
    if (options->verbose) {
      printf("\t\t-> Success!\n");
    }
  }
  if (options->verbose) {
    printf("Packet capture finished ! Closing handle and capture file...\n");
  }
  close_output_capture_file(file);
  close_capture_handle(handle);
  if (options->verbose) {
    printf("-> Success!\nQuitting, bye !\n");
  }
  return 0;
}

int main(int ac, const char **av) {
  sniffer_options_t options;

  if (ac == 2 && (!strcmp(av[1], "-h") || !strcmp(av[1], "--help"))) {
    return print_usage(av[0], 0);
  } else if (ac < 3 || parse_options(ac - 3, av + 3, &options)) {
    return print_usage(av[0], 1);
  }
  return perform_capture(av[1], av[2], &options) < 0 ? 1 : 0;
}
