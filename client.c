#include <netdb.h>
#include <string.h>
#include <stdio.h>

#include "protocol.h"
#include "udp_peer.h"
#include "advio.h"

void SendPackAndDieIfNak(HUdpPeer h, struct sockaddr_in addr, Pack pk);
void UDPPing(HUdpPeer h, struct sockaddr_in addr);

int main(int argc, char *argv[])
{
    struct hostent *he;
    struct sockaddr_in server_addr;
    char inputbuf[250];

    HUdpPeer peer = UDPCreate(CLIENT_PORT);

    if (argc != 2)
    {
        WColor(YELLOW, "No ip addr provided.");
        WColor(GREEN, "Running network discovery...");
        server_addr = NetworkDiscovery(peer, SERVER_PORT);
        WColor(GREEN, "[OK] Server found.");
    }
    else
    {
        if ((he = gethostbyname(argv[1])) == NULL)
        {
            die("Error get host info");
        }
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(SERVER_PORT);
        server_addr.sin_addr = *((struct in_addr *)he->h_addr);
    }

    UDPPing(peer, server_addr);
    Pack pack;
    int symb = 1;
    while (true)
    {
        pack.Type = 0;
        pack.Val1 = 0;
        pack.Val2 = 0;
        char cmd;
        fflush(stdin);
        scanf("%s", inputbuf);
        cmd = inputbuf[0];
        fflush(stdin);
        if ((cmd >= 'a' && cmd <= 'z') || (cmd >= 'A' && cmd <= 'Z') || (cmd >= '0' && cmd <= '9'))
        {
            printf("[QCommandStdIn] %c", cmd);
            switch (cmd)
            {
            case 'V':
            case 'v':
            {
                pack.Type = Command;
                pack.Val1 = Stepper;
                {
                    if (inputbuf[1] == 0)
                    {
                        pack.Val2 = 0;
                    }
                    else if (inputbuf[2] == 0)
                    {
                        pack.Val2 = (inputbuf[1] - '0');
                    }
                    else if (inputbuf[3] == 0)
                    {
                        pack.Val2 = (inputbuf[1] - '0') * 10 + (inputbuf[2] - '0');
                    }
                    else if (inputbuf[4] == 0)
                    {
                        pack.Val2 = (inputbuf[1] - '0') * 100 + (inputbuf[2] - '0') * 10 + (inputbuf[3] - '0');
                    }
                }
                pack.Val2 = -pack.Val2;
            }
            break;
            
            case 'H':
            case 'h':
            {
                pack.Type = Command;
                pack.Val1 = Stepper;
                {
                    if (inputbuf[1] == 0)
                    {
                        pack.Val2 = 0;
                    }
                    else if (inputbuf[2] == 0)
                    {
                        pack.Val2 = (inputbuf[1] - '0');
                    }
                    else if (inputbuf[3] == 0)
                    {
                        pack.Val2 = (inputbuf[1] - '0') * 10 + (inputbuf[2] - '0');
                    }
                    else if (inputbuf[4] == 0)
                    {
                        pack.Val2 = (inputbuf[1] - '0') * 100 + (inputbuf[2] - '0') * 10 + (inputbuf[3] - '0');
                    }
                }
            }
            break;

            case 'I':
            case 'i':
            {
                pack.Type = Command;
                pack.Val1 = LED;
                pack.Val2 = inputbuf[1] - '0';
            }
            break;

            default:
            {
                pack.Type = Command;
                pack.Val1 = SegDigit;
                if (cmd >= 'A' && cmd <= 'F')
                    pack.Val2 = cmd - 'A' + 10;
                else if (cmd >= 'a' && cmd <= 'f')
                    pack.Val2 = cmd - 'a' + 10;
                else if (cmd >= '0' && cmd <= '9')
                    pack.Val2 = cmd - '0';
            }
            break;
            }
            SendPackAndDieIfNak(peer, server_addr, pack);
        }
    }
}

void SendPackAndDieIfNak(HUdpPeer h, struct sockaddr_in addr, Pack pk)
{
    ReceivedPack tmp;
    UDPSend(h, addr, pk);
    tmp = UDPReceive(h);
    if (tmp.Package.Type != Ack)
    {
        printf("[Comm Err]\n");
        DumpPack(tmp.Package);
        die("Communication error.");
    }
}

void UDPPing(HUdpPeer h, struct sockaddr_in addr)
{
    ReceivedPack tmp;
    Pack pk;
    pk.Type = Ping;
    pk.Val1 = 0;
    pk.Val2 = 0;

    UDPSend(h, addr, pk);
    tmp = UDPReceive(h);
    if (tmp.Package.Type != Pong)
    {
        printf("[Ping Err]\n");
        DumpPack(tmp.Package);
        die("Communication error.");
    }
}