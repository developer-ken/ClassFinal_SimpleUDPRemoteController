#include "protocol.h"
#include "udp_peer.h"
#include "advio.h"

#include "./hwdrivers/Segdisp.h"
#include "./hwdrivers/Led.h"
#include "./hwdrivers/Stepper.h"

void DoCommand(int, int, Pack *);

int main()
{
#ifndef DRY
    StepperMThreadInit();
#endif
    HUdpPeer peer = UDPCreate(SERVER_PORT);
    while (true)
    {
        ReceivedPack pack;
        Pack reply;
        reply.Type = 0;
        reply.Val1 = 0;
        reply.Val2 = 0;
        pack = UDPReceive(peer);
        switch (pack.Package.Type)
        {
        case Ping:
            WriteLine("Ping <-> Pong");
            reply.Type = Pong;
            reply.Val1 = 0;
            reply.Val2 = 0;
            break;

        case Command:
            WriteLine("New Command...");
            reply.Type = Ack;
            DoCommand(pack.Package.Val1, pack.Package.Val2, &reply);
            break;

        default:
            break;
        }
        UDPSend(peer, pack.ClientAddr, reply);
    }
}

void DoCommand(int cmd, int arg0, Pack *reply)
{
    switch (cmd)
    {
    case LED:
    {
#ifndef DRY
        reply->Val2 = LedSwitch(arg0);
#endif
    }
    break;
    case Stepper:
    {
#ifndef DRY
        StepperSetSpeed(arg0);
#endif
    }
    break;
    case SegDigit:
    {
#ifndef DRY
        SegDispShow(arg0);
#endif
    }
    break;
    }
}