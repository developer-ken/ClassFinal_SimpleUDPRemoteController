#ifndef _H_RPROTOCOL_
#define _H_RPROTOCOL_
enum
{
    ProtocolErr = 0,
    Ping = 1,
    Pong = 2,

    Command = 3,
    Ack = 4
} typedef PackType;

enum
{
    TypeErr = 0,
    LED = 1,
    Stepper = 2,
    SegDigit = 3
} typedef CmdType;

struct
{
    PackType Type;
    int Val1;
    int Val2;
} typedef Pack;


Pack PackDecode(char[12]);
char *PackEncode(Pack);

#define SERVER_PORT 12345
#define CLIENT_PORT 12343

#define true 1
#define false 0
#endif