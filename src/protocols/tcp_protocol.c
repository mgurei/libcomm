#include "tcp_protocol.h"
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 12345
#define SERVER_IP "127.0.0.1" // Localhost

static int sockfd = -1;

void tcp_init(void) {
    // Initialize the TCP protocol
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
    
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sockfd);
        sockfd = -1;
        return;
    }

    printf("TCP protocol initialized and connected to server.\n");
}

int tcp_send(const char *data, int len) {
    // Send data using TCP protocol
    if (sockfd < 0) {
        return -1;
    }

    int bytes_len = send(sockfd, data, len, 0);
    if (bytes_len < 0) {
        perror("send");
        return -1;
    }
    printf("Sent data using TCP: %s\n", data);
    return bytes_len; // Return num bytes sent
}

int tcp_receive(char *buffer, int len) {
    // Receive data using TCP protocol
    if (sockfd < 0) {
        return -1;
    }
    int bytes_received = recv(sockfd, buffer, len, 0);
    if (bytes_received < 0) {
        perror("recv");
        return -1;
    }
    return bytes_received; // Return num bytes received
}
