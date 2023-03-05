#include "protocol.h"
#include "udp_peer.h"
#include "advio.h"

inline int PackEqual(Pack a, Pack b)
{
    return a.Type == b.Type && a.Val1 == b.Val1 && a.Val2 == b.Val2;
}

int main()
{
    Pack pk, ppk, pk1, pk2;
    pk.Type = Ping;
    pk.Val1 = 0;
    pk.Val2 = 2589;
    DumpPack(pk);
    printf("Package Encode:\n");
    char *buffer1 = PackEncode(pk);
    DumpBuffer(buffer1, 12);

    printf("\n\nPackage Decode:\n");
    ppk = PackDecode(buffer1);
    DumpPack(ppk);

    if (!PackEqual(pk, ppk))
    {
        die("Pack diff!!");
    }
    printf("==== PASS ====\n");
}