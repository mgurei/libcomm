#include "uart_protocol.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

static int uart_fd = -1;

static int configure_uart(uart_config_t *config) {
    struct termios tty;

    if (tcgetattr(uart_fd, &tty) != 0) {
        perror("tcgetattr");
        return -1;
    }

    // Set baud rate
    speed_t speed;
    switch(config->baud_rate) {
        case 9600:   speed = B9600;   break;
        case 115200: speed = B115200; break;
        default:     speed = B9600;   break;
    }
    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    // 8N1 configuration
    tty.c_cflag &= ~PARENB;        // No parity
    tty.c_cflag &= ~CSTOPB;        // 1 stop bit
    tty.c_cflag &= ~CSIZE;         // Clear size bits
    tty.c_cflag |= CS8;            // 8 bits per byte
    tty.c_cflag |= CREAD | CLOCAL; // Enable READ & ignore ctrl lines

    // Non-canonical mode
    tty.c_lflag &= ~ICANON; // Disable canonical mode  
    tty.c_lflag &= ~ECHO;   // Disable echo
    tty.c_lflag &= ~ECHOE;  // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG;   // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Disable software flow control
    tty.c_iflag &= ~(ICRNL | INLCR);        // Disable translation of carriage return and line feed
    tty.c_oflag &= ~OPOST;                 // Disable output processing

    // Set read timeout
    tty.c_cc[VMIN] = 0;  // Minimum number of characters to read
    tty.c_cc[VTIME] = 10; // Time to wait for data (tenths of a second)

    // Set attributes
    if (tcsetattr(uart_fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        return -1;
    }

    return 0;
}

int uart_init(uart_config_t *config) {
    uart_fd = open(config->port, O_RDWR);
    if (uart_fd < 0) {
        perror("open");
        return -1;
    }

    if (configure_uart(config) < 0) {
        close(uart_fd);
        uart_fd = -1;
        return -1;
    }

    printf("UART initialized on port %s\n", config->port);
    return 0;
}

int uart_send(const char *data, int len) {
    if (uart_fd < 0) {
        perror("write");
        return -1;
    }
    int bytes_sent = write(uart_fd, data, len);
    if (bytes_sent < 0) {
        perror("write");
        return -1;
    }

    return bytes_sent;
}

int uart_receive(char *buffer, int len) {
    if (uart_fd < 0) {
        return -1;
    }
    int bytes_received = read(uart_fd, buffer, len);
    if (bytes_received < 0) {
        perror("read");
        return -1;
    }

    return bytes_received;
}