#ifndef _H_UDP_PEER_
#define _H_UDP_PEER_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "protocol.h"

struct{
    int sock;
}typedef HUdpPeer;

struct{
    struct sockaddr_in ClientAddr;
    Pack Package;
}typedef ReceivedPack;

HUdpPeer UDPCreate(int port);
ReceivedPack UDPReceive(HUdpPeer h);
void UDPSend(HUdpPeer h,struct sockaddr_in addr, Pack pk);
struct sockaddr_in NetworkDiscovery(HUdpPeer h, int port);
void DumpPack(Pack pk);
void DumpBuffer(char *buf, int len);
#endif