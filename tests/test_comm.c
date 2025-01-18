#include "comm.h"
#include <stdio.h>
#include <string.h>

int main() {
    char buffer[1024];

    // Initialize the communication module
    comm_init();

    // Send data to the server
    const char *message = "Hello, Server!";
    int bytes_sent = comm_send_data(message, strlen(message));
    printf("Sent %d bytes: %s\n", bytes_sent, message);

    // Receive data from the server
    int bytes_received = comm_receive_data(buffer, sizeof(buffer) - 1);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Received %d bytes: %s\n", bytes_received, buffer);
    } else {
        printf("Failed to receive data\n");
    }

    return 0;
}
