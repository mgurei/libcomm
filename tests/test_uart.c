#include "../src/comm.h"
#include "../src/protocols/uart_protocol.h"
#include "test_framework.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <pty.h>

int master_fd, slave_fd;
char slave_name[100];

void setup_pty(void) {
    if (openpty(&master_fd, &slave_fd, slave_name, NULL, NULL) < 0) {
        perror("openpty");
        exit(EXIT_FAILURE);
    }
    printf("Psuedo-terminal created: %s\n", slave_name);
}

void test_uart_init(void) {
    uart_config_t config = {
        .baud_rate = 9600,
        .data_bits = 8,
        .stop_bits = 1,
        .parity = 'N',
        //.port = "/dev/pts/0"    // Adjusted based on available ports
        .port = slave_name
    };

    comm_init((protocol_t *)&uart_protocol);
    int result = uart_init(&config);
    ASSERT(result == 0);    
}

void test_uart_send(void) {
    const char *data = "Hello, UART!";
    int len = strlen(data);

    int result = uart_send(data, len);
    ASSERT(result == len);

    char buffer[256] = {0};
    read(master_fd, buffer, sizeof(buffer));
    ASSERT(strcmp(data, buffer) == 0);   
}

void test_uart_receive(void) {
    const char *data = "Hello from master!";
    write(master_fd, data, strlen(data));

    char buffer[256] = {0};
    int len = sizeof(buffer);

    int result = uart_receive(buffer, len);
    ASSERT(result == (int)strlen(data));
    ASSERT(strcmp(data, buffer) == 0);
}

int main(void) {
    REGISTER_TEST_FILE("UART Tests", "Tests for UART protocol implementation");

    setup_pty();

    REGISTER_TEST(test_uart_init, "Initialize UART with pseudo-terminal");
    REGISTER_TEST(test_uart_send, "Send data through UART and verify transmission");
    REGISTER_TEST(test_uart_receive, "Receive data through UART and verify reception");

    RUN_TESTS();

    close(master_fd);
    close(slave_fd);
    
    return 0;
}