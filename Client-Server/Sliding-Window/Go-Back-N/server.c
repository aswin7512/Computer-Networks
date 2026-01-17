#include "protocol.h"
#include <time.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int expected_seq = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    srand(time(NULL));

    printf("Receiver listening on port %d...\n", PORT);

    while (expected_seq < TOTAL_PACKETS) {
        Packet p;
        recvfrom(sockfd, &p, sizeof(p), 0, (struct sockaddr*)&client_addr, &addr_len);

        // Simulate 20% packet loss
        if (rand() % 5 == 0) {
            printf("Dropped Packet %d (Simulated Loss)\n", p.seq_num);
            continue; 
        }

        if (p.seq_num == expected_seq) {
            printf("Received Packet %d. Sending ACK %d\n", p.seq_num, expected_seq);
            AckPacket ack;
            ack.ack_num = expected_seq;
            sendto(sockfd, &ack, sizeof(ack), 0, (struct sockaddr*)&client_addr, addr_len);
            expected_seq++;
        } else {
            printf("Out of order Packet %d ignored. Expected %d\n", p.seq_num, expected_seq);
        }
    }

    printf("All packets received. Exiting.\n");
    close(sockfd);
    return 0;
}

/*
O/P
Receiver listening on port 8080...
Received Packet 0. Sending ACK 0
Received Packet 1. Sending ACK 1
Received Packet 2. Sending ACK 2
Received Packet 3. Sending ACK 3
Dropped Packet 4 (Simulated Loss)
Dropped Packet 5 (Simulated Loss)
Out of order Packet 6 ignored. Expected 4
Dropped Packet 7 (Simulated Loss)
Dropped Packet 4 (Simulated Loss)
Out of order Packet 5 ignored. Expected 4
Out of order Packet 6 ignored. Expected 4
Out of order Packet 7 ignored. Expected 4
Received Packet 4. Sending ACK 4
Dropped Packet 5 (Simulated Loss)
Out of order Packet 6 ignored. Expected 5
Out of order Packet 7 ignored. Expected 5
Dropped Packet 8 (Simulated Loss)
Dropped Packet 5 (Simulated Loss)
Out of order Packet 6 ignored. Expected 5
Out of order Packet 7 ignored. Expected 5
Out of order Packet 8 ignored. Expected 5
Received Packet 5. Sending ACK 5
Received Packet 6. Sending ACK 6
Dropped Packet 7 (Simulated Loss)
Out of order Packet 8 ignored. Expected 7
Out of order Packet 9 ignored. Expected 7
Received Packet 7. Sending ACK 7
Received Packet 8. Sending ACK 8
Received Packet 9. Sending ACK 9
All packets received. Exiting.
*/