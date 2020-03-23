### Packet sniffer ###

Author: Fantin Bibas <frhb2@kent.ac.uk>
Student id: frhb2
Default filter used: "port 23"

This project is my submission for the second assessment of UKC CO892 Advanced Network Security: Homemade packet sniffer.

The associated sources files compile in a program that, given a network interface name and a filename, will open the
interface to listen for 10 network packets and save them in a file with the given filename in the standard "pcap" format
that can be opened by multiple software like Wireshark (http://wireshark.org/).

## Compilation ##

The program is provided with a "CMakeLists.txt" file to be used in a standard way with the cmake program. Example of
compilation in linux:

 ---
$> cmake .
$> make
 ---

An executable named "sniffer" should then be available in the current folder.

If you are having difficulties compiling the program, pre-compiled versions are available under the "bin" folder in the
root of the sources directory.

## Installation ##

The executable is portable so to make it globally available to an used its path needs to be added to the system PATH
environment variable. Example of an export on bash on linux:

 ---
$> export PATH=$PATH:$(pwd)
 ---

## Usage ##

To show the usage of the program simply run it with the "-h" or "--help" argument:

 ---
$> ./sniffer -h
Packet sniffer.

Usage:
  ./sniffer -h | --help
  ./sniffer device filename [-v]...

Options
  filename	Filename to use for the output capture file
  device	Network interface to use
  -h --help	Show this help message
  -v		Verbose output
 ---

# Examples of use: #

 ---
$> ls
sniffer
$> ./sniffer wlp2s0 output.pcap
$> ls
output.pcap sniffer
 ---

And with the verbose mode:

 ---
$> ls
sniffer
$> ./sniffer wlp2s0 output.pcap -v
Creating capture handle...
-> Success!
Applying filter "port 23" to capture handle...
-> Success!
Opening output capture file "output.pcap"...
-> Success!
Starting the packet capture...
	Capturing packet 1 on 10...
	-> Success!
		Saving packet...
		-> Success!
	Capturing packet 2 on 10...
	-> Success!
		Saving packet...
		-> Success!
	Capturing packet 3 on 10...
	-> Success!
		Saving packet...
		-> Success!
	Capturing packet 4 on 10...
	-> Success!
		Saving packet...
		-> Success!
	Capturing packet 5 on 10...
	-> Success!
		Saving packet...
		-> Success!
	Capturing packet 6 on 10...
	-> Success!
		Saving packet...
		-> Success!
	Capturing packet 7 on 10...
	-> Success!
		Saving packet...
		-> Success!
	Capturing packet 8 on 10...
	-> Success!
		Saving packet...
		-> Success!
	Capturing packet 9 on 10...
	-> Success!
		Saving packet...
		-> Success!
	Capturing packet 10 on 10...
	-> Success!
		Saving packet...
		-> Success!
Packet capture finished ! Closing handle and capture file...
-> Success!
Quitting, bye !
$> ls
output.pcap sniffer
 ---

The "output.pcap" file can then be opened by Wireshark for inspection of the 10 captured packets.

## Troubleshooting ##

If the program is locked in the "Capturing packet 1 on 10..." it is probably because you have no network traffic
corresponding to the default filter "port 23" of the program. To create some traffic you can open a telnet connection to
a public telnet server like the one of the Seattle Community Network available at "scn.org". Example on linux using the
program telnet:

 ---
$> telnet scn.org
 ---
