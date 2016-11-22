#include <stdio.h>
#include <stdlib.h>
#include "packet.pb-c.h"

int main(int argc, const char *argv[]) {

    Packet packet = PACKET__INIT;
    void *buf;
    unsigned len;

    if(argc != 2 && argc != 3 ) {
        fprintf(stderr, "usage: packet a [b]");
        return 1;
    }

    packet.a = atoi(argv[1]);

    if(argc == 3) {
        packet.has_b = 1;
        packet.b = atoi(argv[2]);
    }

    len = packet__get_packed_size(&packet);

    buf = malloc(len);
    packet__pack(&packet, buf);

    fprintf(stderr, "Writing %d serialized bytes\n", len);
    fwrite(buf, len, 1, stdout);

    free(buf);
    return 0;

}
