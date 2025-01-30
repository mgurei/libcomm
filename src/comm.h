#ifndef COMM_H
#define COMM_H

#include "protocol.h"

/**
 * @brief Communication module
 */

/**
 * @brief Initialize the communication module
 * @param protocol Protocol to use
 */
void comm_init(protocol_t *protocol);

/**
 * @brief Send data
 * @param data Data to send
 * @param len Length of the data
 * @return Number of bytes sent
 */
int comm_send(const char *data, int len);

/**
 * @brief Receive data
 * @param buffer Buffer to store the received data
 * @param len Length of the buffer
 * @return Number of bytes received
 */
int comm_receive(char *buffer, int len);

#endif // COMM_H