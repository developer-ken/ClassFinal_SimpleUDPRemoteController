#!/bin/bash
gcc -o remotectld_x86 advio.c protocol.c udp_peer.c server.c -DDRY -O0
arm-linux-gcc -o remotectld -pthread advio.c protocol.c udp_peer.c ./hwdrivers/*.c server.c -O0