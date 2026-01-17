#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <arpa/inet.h>

#define PORT 8080
#define WINDOW_SIZE 4
#define TOTAL_PACKETS 10

typedef struct {
    int seq_num;
    bool received;
} ReceiverWindow;

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);
    
    ReceiverWindow buffer[TOTAL_PACKETS] = {0};
    int window_base = 0;
    int incoming_pkt;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("Selective Repeat Server listening...\n");

    while (window_base < TOTAL_PACKETS) {
        recvfrom(sockfd, &incoming_pkt, sizeof(incoming_pkt), 0, (struct sockaddr*)&client_addr, &addr_size);
        
        printf("Received Packet: %d ", incoming_pkt);

        // Accept if within current window
        if (incoming_pkt >= window_base && incoming_pkt < window_base + WINDOW_SIZE) {
            buffer[incoming_pkt].received = true;
            // Send individual ACK for this specific packet
            sendto(sockfd, &incoming_pkt, sizeof(incoming_pkt), 0, (struct sockaddr*)&client_addr, addr_size);
            printf("[ACK Sent]\n");

            // Slide window if the base packet was received
            while (window_base < TOTAL_PACKETS && buffer[window_base].received) {
                window_base++;
            }
        } else {
            printf("[Ignored - Outside Window]\n");
        }
    }
    return 0;
}

/*
O/P
Selective Repeat Server listening...
Received Packet: 0 [ACK Sent]
Received Packet: 1 [ACK Sent]
Received Packet: 2 [ACK Sent]
Received Packet: 3 [ACK Sent]
Received Packet: 4 [ACK Sent]
Received Packet: 5 [ACK Sent]
Received Packet: 6 [ACK Sent]
Received Packet: 7 [ACK Sent]
Received Packet: 8 [ACK Sent]
Received Packet: 9 [ACK Sent]
*/