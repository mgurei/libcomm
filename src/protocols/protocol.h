#ifndef PROTOCOL_H
#define PROTOCOL_H

typedef struct {
    void (*init)(void);
    int (*send)(const char *data, int len);
    int (*receive)(char *buffer, int len);
} protocol_t;

#endif // PROTOCOL_H