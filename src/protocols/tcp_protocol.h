#ifndef TCP_PROTOCOL_H
#define TCP_PROTOCOL_H

/**
 * @brief Initialize the TCP protocol
 */
void tcp_init(void);

/**
 * @brief Send data using the TCP protocol
 * @param data Data to send
 * @param len Length of the data
 * @return Number of bytes sent
 */
int tcp_send(const char *data, int len);

/**
 * @brief Receive data using the TCP protocol
 * @param buffer Buffer to store the received data
 * @param len Length of the buffer
 * @return Number of bytes received
 */
int tcp_receive(char *buffer, int len);

#endif // TCP_PROTOCOL_H