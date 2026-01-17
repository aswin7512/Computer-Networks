#include "protocol.h"

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    int base = 0;
    int next_seq = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Set a timeout for receiving ACKs
    struct timeval tv;
    tv.tv_sec = TIMEOUT_SEC;
    tv.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    printf("Starting GBN Sender (Window Size: %d)\n", WINDOW_SIZE);

    while (base < TOTAL_PACKETS) {
        // Send packets within the window
        while (next_seq < base + WINDOW_SIZE && next_seq < TOTAL_PACKETS) {
            Packet p;
            p.seq_num = next_seq;
            sprintf(p.data, "Payload %d", next_seq);
            
            sendto(sockfd, &p, sizeof(p), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
            printf("--> Sent Packet %d\n", next_seq);
            next_seq++;
        }

        // Wait for ACK
        AckPacket ack;
        if (recvfrom(sockfd, &ack, sizeof(ack), 0, NULL, NULL) > 0) {
            printf("<-- Received ACK %d\n", ack.ack_num);
            if (ack.ack_num >= base) {
                base = ack.ack_num + 1; // Cumulative ACK: Slide window
            }
        } else {
            // Timeout occurred
            printf("!!! Timeout! Resending from Packet %d\n", base);
            next_seq = base; // Go Back N
        }
    }

    printf("All packets sent and acknowledged successfully.\n");
    close(sockfd);
    return 0;
}

/*
O/P
Starting GBN Sender (Window Size: 4)
--> Sent Packet 0
--> Sent Packet 1
--> Sent Packet 2
--> Sent Packet 3
<-- Received ACK 0
--> Sent Packet 4
<-- Received ACK 1
--> Sent Packet 5
<-- Received ACK 2
--> Sent Packet 6
<-- Received ACK 3
--> Sent Packet 7
!!! Timeout! Resending from Packet 4
--> Sent Packet 4
--> Sent Packet 5
--> Sent Packet 6
--> Sent Packet 7
!!! Timeout! Resending from Packet 4
--> Sent Packet 4
--> Sent Packet 5
--> Sent Packet 6
--> Sent Packet 7
<-- Received ACK 4
--> Sent Packet 8
!!! Timeout! Resending from Packet 5
--> Sent Packet 5
--> Sent Packet 6
--> Sent Packet 7
--> Sent Packet 8
!!! Timeout! Resending from Packet 5
--> Sent Packet 5
--> Sent Packet 6
--> Sent Packet 7
--> Sent Packet 8
<-- Received ACK 5
--> Sent Packet 9
<-- Received ACK 6
!!! Timeout! Resending from Packet 7
--> Sent Packet 7
--> Sent Packet 8
--> Sent Packet 9
<-- Received ACK 7
<-- Received ACK 8
<-- Received ACK 9
All packets sent and acknowledged successfully.
*/