#!/bin/bash
gcc -o remotecli_x86 advio.c protocol.c udp_peer.c client.c
arm-linux-gcc -o remotecli advio.c protocol.c udp_peer.c client.c