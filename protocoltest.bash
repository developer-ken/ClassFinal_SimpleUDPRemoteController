#!/bin/bash
gcc -o protocoltest_x86 advio.c protocol.c udp_peer.c test_protocol.c
./protocoltest_x86
rm ./protocoltest_x86