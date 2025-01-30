#ifndef UART_PROTOCOL_H
#define UART_PROTOCOL_H

#include "protocol.h"

/**
 * @brief UART configuration structure
 */
typedef struct
{
    int baud_rate; // Baud rate
    int data_bits; // Data bits
    int stop_bits; // Stop bits
    char parity;   // Parity
    char *port;    // Port
} uart_config_t;

/**
 * @brief Initialize the UART protocol
 * @param config UART configuration
 * @return 0 if successful, otherwise -1
 */
int uart_init(uart_config_t *config);

/**
 * @brief Send data using the UART protocol
 * @param data Data to send
 * @param len Length of the data
 * @return Number of bytes sent
 */
int uart_send(const char *data, int len);

/**
 * @brief Receive data using the UART protocol
 * @param buffer Buffer to store the received data
 * @param len Length of the buffer
 * @return Number of bytes received
 */
int uart_receive(char *buffer, int len);

/** 
 * @brief UART protocol structure
 */
extern protocol_t uart_protocol;

#endif // UART_PROTOCOL_H