//
// Created by neodar on 23/03/2020.
//

#include <string.h>
#include <pcap.h>

void print_usage(const char *executable)
{
  printf("USAGE: %s DEVICE FILENAME\n\tDEVICE\t\tNetwork interface to use\n", executable);
  printf("\tFILENAME\tFilename to use for the output capture file\n");
}

int main(int ac, char **av)
{
  if (ac < 2 || !strcmp(av[1], "-h")) {
    print_usage(av[0]);
    return (ac < 2 ? 1 : 0);
  }
  return 0;
}
