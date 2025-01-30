#include "comm.h"
#include "protocols/protocol.h"
#include <stdio.h>

static protocol_t *current_protocol = NULL;

void comm_init(protocol_t *protocol) {
    current_protocol = protocol;
    current_protocol->init();
    printf("Communication module initialized\n");
}

int comm_send(const char *data, int len) {
    if (current_protocol == NULL) {
        fprintf(stderr, "Communication module not initialized\n");
        return -1;
    }
    return current_protocol->send(data, len);
}

int comm_receive(char *buffer, int len) {
    if(current_protocol == NULL) {
        fprintf(stderr, "Communication module not initialized\n");
        return -1;
    }
    return current_protocol->receive(buffer, len);
}