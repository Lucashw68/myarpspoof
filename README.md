# MyARPSpoof

	- Binary name: myARPspoof
	- Language: C
	- Compilation: via Makefile, including re, clean and fclean rules

# Warnings

ATTENTION: Executing this program against networks where you do not have permission is considered as a crime and is therefore totally illegal.
This kind of attack is highly detectable, it can (and it will) be traced back to you, and you
will most likely be prosecuted in court for such action.

Remember, network administrators and authorities, do not care if you emitted spoofed
ARP packets unintentionally, for example by mistake while coding. They mostly look
which computer sent those packets and to whom that device belongs.

I will not be responsible for any bad usage of this program, it is made for educational purpose only.

# Project description

This program first broadcast an ARP packet in order to retrieve the corresponding MAC address of
the IPv4 address which belongs to the target/victim. After this step, the program send spoofed ARP
reply packets every 1 second (using that MAC address). Those spoofed ARP packets basically lie to
the target/victim by saying that our MAC address resolves to an IPv4 that we have provided as an argument
to the program.

## Usage

	sudo ./arpspoof [Source IP] [Target IP] [Interface] ++ [--printBroadcast | --printSpoofing [MAC address] ]

## Parameters

The program normally takes 3 parameters and root privileges are needed:
* source_ip is the source IP where we need to make it appear that the packet was sent from (look at Sender
IP Address field in the ARP header).
* dest_ip is the destination IP (look at Target IP Address in the ARP header).
* iface is the interface to use to send/receive packets.

There are additional options:
* `--printBroadcast (no root)`:
If the --printBroadcast option is passed as a parameter to the program, the program print on stdout
the ARP packet (step 1 - the ARP request packet sent to broadcast) followed by a newline and exit WITH-
OUT actually sending the packet. This also implies that no root privileges are needed when passing this
parameter to the program. More precisely, the packet is printed in hexadecimal lower case with a
space in between each hexadecimal number.

* `--printSpoof [MAC Address] (no root)`:
If the --printSpoof [MAC addr] option is passed as a parameter to the program, the program print the
spoofed ARP packet (step 3) and exit.

* `#define VERBOSE` in include/core.h can be set to true for additionnals outputs

## In-Depth Explication

Executing sudo ./myARPspoof 42.42.42.42 192.168.1.1 wlo1 perform the following steps:
1. Broadcast an ARP request packet essentially asking “Who has 192.168.1.1 ?” in order to get the MAC address of the target IP address ( dest_ip , 2nd argument passed to the program).
2. Listen for the response (if any), grab the MAC address of the target and display it to stdout with the
following message:
“ Found victim's MAC address: 'MAC_ADDRESS' ”
where MAC_ADDRESS is the MAC address of the target that we managed to retrieve.
3. Send spoofed packets continuously to the destination address every 1 second. More specifically, in order
for this to work, this spoofed packet will be crafted by respecting the following criteria:
• set the source MAC address (in the Ethernet frame header) to the MAC address of the computer that
is currently executing the program.
• set the destination MAC address (in the Ethernet frame header) to the MAC address of the target that
we managed to get from step 2)
• set the ‘Sender IP Address’ field (inside the ARP header) to 42.42.42.42
• set the ‘Target IP Address’ field (inside the ARP header) to 192.168.1.1
• Each time a spoofed packet is sent (every 1 second), the program display the following message:
“ Spoofed packet sent to 'IP_ADDRESS' ”
where IP_ADDRESS is the IP address of the target ( dest_ip , 2nd argument passed to the program).

## Useful links / Tools

* RFC 826: [rfc826](https://tools.ietf.org/html/rfc826)
* Format of ARP Packet: [ARP Packet](http://image.slidesharecdn.com/arpaddressresolutionprotocol-110519232546-phpapp01/95/arp-address-resolution-protocol-6-728.jpg)
* Ethernet frame header: [Ethernet frame header](https://1.bp.blogspot.com/-4_335OfoWcg/WlgQ0DBQnqI/AAAAAAAABq8/nIJAtzo3vzYRTnbOwr_INFqJGprh9lXFQCLcBGAs/s1600/Ethernet%2B%2528DIX%2529%2Bframe%2B11111.png)
* Man packet: [man (7) packet](http://man7.org/linux/man-pages/man7/packet.7.html)
* arpspoof (from dsniff package; pre-installed in Kali Linux)
* Wireshark
* strace (can sometimes help, speed up debugging)
