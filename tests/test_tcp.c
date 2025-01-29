#include "../src/protocols/tcp_protocol.h"
#include "test_framework.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define SERVER_PORT 12345
volatile int server_running = 1;

void *mock_server(void *arg) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        return NULL;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_fd);
        return NULL;
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen");
        close(server_fd);
        return NULL;
    }

    printf("Mock server listening on port %d\n", SERVER_PORT);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd < 0) {
        perror("accept");
        close(server_fd);
        return NULL;
    }

    printf("Client connected\n");

    while (server_running) {
        int bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            break;
        }
        buffer[bytes_received] = '\0';
        printf("Received: %s\n", buffer);

        const char *response = "Message received";
        send(client_fd, response, strlen(response), 0);
    }

    close(client_fd);
    close(server_fd);
    printf("Mock server stopped\n");
    return NULL;
}

void test_tcp_init(void) {
    tcp_init();
    ASSERT(tcp_get_socket() != -1);
}

void test_tcp_send(void) {
    const char *message = "Hello, Server!";
    int bytes_sent = tcp_send(message, strlen(message));
    ASSERT(bytes_sent == strlen(message));
}

void test_tcp_receive(void) {
    char buffer[1024];
    int bytes_received = tcp_receive(buffer, sizeof(buffer) - 1);
    ASSERT(bytes_received > 0);
    buffer[bytes_received] = '\0';
    ASSERT(strcmp(buffer, "Message received") == 0);
}

int main() {
    pthread_t server_thread;
    pthread_create(&server_thread, NULL, mock_server, NULL);

    sleep(1); // Wait for server to start

    // Client-side code to connect to mock server
    REGISTER_TEST(test_tcp_init);
    REGISTER_TEST(test_tcp_send);
    REGISTER_TEST(test_tcp_receive);

    RUN_TESTS();

    server_running = 0; // Signal the server to stop
    shutdown(tcp_get_socket(), SHUT_RDWR); // Close the client socket
    pthread_join(server_thread, NULL);  // Wait for the server thread to finish

    return 0;
}