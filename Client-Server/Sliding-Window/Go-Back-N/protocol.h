#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 8080
#define WINDOW_SIZE 4
#define TOTAL_PACKETS 10
#define TIMEOUT_SEC 2

typedef struct {
    int seq_num;
    char data[1024];
} Packet;

typedef struct {
    int ack_num;
} AckPacket;