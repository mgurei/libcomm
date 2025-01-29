
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define SERVER_PORT 12345

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

    while (1) {
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
    return NULL;
}

void print_test_result(const char *test_name, int result) {
    printf("%s: %s\n", test_name, result ? "FAIL" : "PASS");
}

int main() {
    pthread_t server_thread;
    pthread_create(&server_thread, NULL, mock_server, NULL);

    sleep(1); // Wait for server to start

    // Client-side code to connect to mock server
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }
    
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sockfd);
        return 1;
    }

    const char *message = "Hello, Server!";
    int send_result = send(sockfd, message, strlen(message), 0);
    print_test_result("TCP send", send_result < 0);

    int bytes_received = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("Received from server: %s\n", buffer);
    }
    print_test_result("TCP receive", bytes_received <= 0);
    
    close(sockfd);

    pthread_join(server_thread, NULL);
    return 0;
}