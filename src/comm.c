#include "comm.h"
#include <stdio.h>

void comm_init(void) {
    // TODO: Communication module initialization
    printf("Communication module initialized\n");
}

int comm_send_data(const char *data, int len) {
    // TODO: Send data code here
    printf("Sending data: %.*s\n", len, data);
    return len;
}

int comm_receive_data(char *buffer, int len) {
    // TODO: Receive data code here
    // For now, simulate receiving data
    const char *received_data = "Hello, World!";
    int received_len = strlen(received_data);
    if (len < received_len) {
        return -1;
    }
    strcpy(buffer, received_data);
    printf("Received data: %s\n", buffer);
    return received_len; // Return num bytes received
}