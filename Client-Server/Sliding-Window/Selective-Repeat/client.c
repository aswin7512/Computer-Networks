#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define WINDOW_SIZE 4
#define TOTAL_PACKETS 10

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    bool acked[TOTAL_PACKETS] = {false};
    int base = 0, ack_num;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Short timeout to detect "lost" packets
    struct timeval tv = {1, 0};
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    while (base < TOTAL_PACKETS) {
        // 1. Send all packets in the current window that haven't been acked
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_PACKETS; i++) {
            if (!acked[i]) {
                printf("Sending/Retransmitting Packet: %d\n", i);
                sendto(sockfd, &i, sizeof(i), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
            }
        }

        // 2. Wait for ACKs
        while (1) {
            if (recvfrom(sockfd, &ack_num, sizeof(ack_num), 0, NULL, NULL) > 0) {
                printf("Received ACK for: %d\n", ack_num);
                acked[ack_num] = true;
                
                // If base is acked, slide the window
                while (base < TOTAL_PACKETS && acked[base]) {
                    base++;
                }
            } else {
                // Timeout occurred - break inner loop to retransmit un-acked packets
                printf("Timeout! Checking window...\n");
                break;
            }
        }
    }

    printf("Success: All packets acknowledged.\n");
    close(sockfd);
    return 0;
}

/*
O/P
Sending/Retransmitting Packet: 0
Sending/Retransmitting Packet: 1
Sending/Retransmitting Packet: 2
Sending/Retransmitting Packet: 3
Received ACK for: 0
Received ACK for: 1
Received ACK for: 2
Received ACK for: 3
Timeout! Checking window...
Sending/Retransmitting Packet: 4
Sending/Retransmitting Packet: 5
Sending/Retransmitting Packet: 6
Sending/Retransmitting Packet: 7
Received ACK for: 4
Received ACK for: 5
Received ACK for: 6
Received ACK for: 7
Timeout! Checking window...
Sending/Retransmitting Packet: 8
Sending/Retransmitting Packet: 9
Received ACK for: 8
Received ACK for: 9
Timeout! Checking window...
Success: All packets acknowledged.
*/