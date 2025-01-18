#ifndef COMM_H
#define COMM_H

/**
 * @brief Communication module
 */

/**
 * @brief Initialize the communication module
 */
void comm_init(void);

/**
 * @brief Send data
 * @param data Data to send
 * @param len Length of the data
 * @return Number of bytes sent
 */
int comm_send_data(const char *data, int len);

/**
 * @brief Receive data
 * @param buffer Buffer to store the received data
 * @param len Length of the buffer
 * @return Number of bytes received
 */
int comm_receive_data(char *buffer, int len);

#endif // COMM_H