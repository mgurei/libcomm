#include "../src/protocols/uart_protocol.h"
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

    int result = uart_init(&config);
    printf("UART init result: %s\n", result == 0 ? "PASS" : "FAIL");
}

void test_uart_send(void) {
    const char *data = "Hello, UART!";
    int len = strlen(data);

    int result = uart_send(data, len);
    printf("UART send result: %s\n", result == len ? "PASS" : "FAIL");

    char buffer[256] = {0};
    read(master_fd, buffer, sizeof(buffer));
    printf("Data received on master: %s\n", buffer);
}

void test_uart_receive(void) {
    const char *data = "Hello from master!";
    write(master_fd, data, strlen(data));

    char buffer[256] = {0};
    int len = sizeof(buffer);

    int result = uart_receive(buffer, len);
    printf("UART receive result: %d\n", result);
    if (result > 0) {
        printf("Received data: %s\n", buffer);
    }
}

int main(void) {
    setup_pty();

    printf("Testing UART protocol...\n");
    test_uart_init();
    
    test_uart_send();
    test_uart_receive();

    close(master_fd);
    close(slave_fd);
    
    return 0;
}