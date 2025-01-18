#include "comm.h"
#include "protocols/tcp_protocol.h"
#include <stdio.h>

void comm_init(void) {
    // TODO: Communication module initialization
    tcp_init();
    printf("Communication module initialized\n");
}

int comm_send_data(const char *data, int len) {
    // TODO: Send data code here
    return tcp_send(data, len);
}

int comm_receive_data(char *buffer, int len) {
    // TODO: Receive data code here
    // For now, simulate receiving data
    return tcp_receive(buffer, len);
}