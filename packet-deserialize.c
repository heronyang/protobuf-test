#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "packet.pb-c.h"

#define MAX_PACKET_SIZE 1024

static size_t read_buffer(unsigned max_length, uint8_t *out) {

    size_t cur_len = 0;
    size_t nread;

    while((nread = fread(out + cur_len, 1, max_length - cur_len, stdin)) != 0) {
        cur_len += nread;
        if(cur_len == max_length) {
            fprintf(stderr, "max message length exceeded \n");
            exit(1);
        }
    }

    printf("Read %zu bytes\n", cur_len);
    return cur_len;

}

int main(int argc, const char *argv[]) {

    Packet *packet;

    uint8_t buf[MAX_PACKET_SIZE];
    size_t packet_len = read_buffer(MAX_PACKET_SIZE, buf);

    packet = packet__unpack(NULL, packet_len, buf);
    if(packet == NULL) {
        fprintf(stderr, "error unpacking incoming message\n");
    }

    printf("Received: a = %d", packet->a);

    if(packet->has_b) {
        printf(" b = %d", packet->b);
    }
    printf("\n");

    packet__free_unpacked(packet, NULL);
    return 0;

}
