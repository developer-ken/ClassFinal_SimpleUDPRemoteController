#include "protocol.h"

union Int2Char4
{
    int intvar;
    char bytevar[4];
};

int Read4Byte(char *buffer, int offset)
{
    union Int2Char4 uu;
    uu.intvar = 0;
    uu.bytevar[0] = buffer[offset];
    uu.bytevar[1] = buffer[offset + 1];
    uu.bytevar[2] = buffer[offset + 2];
    uu.bytevar[3] = buffer[offset + 3];
    return uu.intvar;
}

void Put4Byte(char *buffer, int data, int offset)
{
    union Int2Char4 uu;
    uu.intvar = data;
    buffer[offset] = uu.bytevar[0];
    buffer[offset+1] = uu.bytevar[1];
    buffer[offset+2] = uu.bytevar[2];
    buffer[offset+3] = uu.bytevar[3];
}

Pack PackDecode(char data[12])
{
    Pack pk;
    pk.Type = Read4Byte(data, 4 * 0);
    pk.Val1 = Read4Byte(data, 4 * 1);
    pk.Val2 = Read4Byte(data, 4 * 2);
    return pk;
}

char *PackEncode(Pack pk)
{
    static char buffer[12];
    Put4Byte(buffer, pk.Type, 4 * 0);
    Put4Byte(buffer, pk.Val1, 4 * 1);
    Put4Byte(buffer, pk.Val2, 4 * 2);
    return buffer;
}