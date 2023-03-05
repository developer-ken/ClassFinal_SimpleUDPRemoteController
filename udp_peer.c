#include "udp_peer.h"
#include "advio.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

HUdpPeer UDPCreate(int port)
{
    struct sockaddr_in maddr;
    static HUdpPeer peer;
    int yes = 1;
    if ((peer.sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        die("Socket init failed");
    }

    maddr.sin_family = AF_INET;
    maddr.sin_port = htons(port);
    maddr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&(maddr.sin_zero), '\0', 8);
    if (bind(peer.sock, (struct sockaddr *)&maddr, sizeof(struct sockaddr)) == -1)
    {
        die("Socket bind failed");
    };
    return peer;
}

ReceivedPack UDPReceive(HUdpPeer h)
{
    int addr_len = sizeof(struct sockaddr_in),
        numbytes;
    char readbuffer[12];
    ReceivedPack rpack;
    if ((numbytes = recvfrom(h.sock, readbuffer, 12, 0, (struct sockaddr *)&rpack.ClientAddr, &addr_len)) == -1)
    {
        die("Socket recv failed");
    }
    printf("\n[RecvPack]\n");
    DumpBuffer(readbuffer, 12);
    rpack.Package = PackDecode(readbuffer);
    DumpPack(rpack.Package);
    return rpack;
}

void UDPSend(HUdpPeer h, struct sockaddr_in addr, Pack pk)
{
    printf("\n[SendPack]\n");
    DumpPack(pk);
    char *buffer = PackEncode(pk);
    DumpBuffer(buffer, 12);
    if ((sendto(h.sock, buffer, 12, 0, (struct sockaddr *)&addr, sizeof(struct sockaddr))) == -1)
    {
        die("Socket send failed");
    }
}

struct sockaddr_in NetworkDiscovery(HUdpPeer peer, int port)
{
    ReceivedPack tmp;
    struct sockaddr_in server_addr;
    Pack pk;
    int yes = 1;

    if (setsockopt(peer.sock, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes)) < 0)
    {
        die("Can't reconfigure socket.");
    }

    server_addr.sin_family = AF_INET;
    //server_addr.sin_addr.s_addr = INADDR_BROADCAST;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET,"192.168.1.255",&server_addr.sin_addr.s_addr);

    pk.Type = Ping;
    pk.Val1 = 0;
    pk.Val2 = 0;

    UDPSend(peer, server_addr, pk);
    do
    {
        tmp = UDPReceive(peer);
    } while (tmp.Package.Type != Pong);
    return tmp.ClientAddr;
}

void DumpBuffer(char *buf, int len)
{
    int i = 0;
    printf("[DEBUG] PackEncoded:");
    for (i = 0; i < len; i++)
    {
        printf(" 0x%02X", buf[i]);
    }
    printf("\n");
}

void DumpPack(Pack pk)
{
    if (pk.Type < 1 || pk.Type > 4)
    {
        printf("[DEBUG]<Invalid> Pack: Type=0x%.2x, Val1=%d, Val2=%d\n", pk.Type, pk.Val1, pk.Val2);
    }
    else
    {
        printf("[DEBUG] Pack: Type=0x%.2x, Val1=%d, Val2=%d\n", pk.Type, pk.Val1, pk.Val2);
    }
}