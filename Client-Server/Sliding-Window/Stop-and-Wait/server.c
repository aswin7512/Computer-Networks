#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_size;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    addr_size = sizeof(client_addr);

    printf("Receiver is ready to receive frames...\n");

    int expected_frame = 0;
    while (expected_frame < 5) {
        recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size);
        printf("Received: %s\n", buffer);

        // Simulate sending ACK
        printf("Sending ACK for frame %d\n", expected_frame);
        sendto(sockfd, "ACK", 4, 0, (struct sockaddr*)&client_addr, addr_size);
        expected_frame++;
    }

    close(sockfd);
    return 0;
}

/*
O/P
Receiver is ready to receive frames...
Received: Frame 0
Sending ACK for frame 0
Received: Frame 1
Sending ACK for frame 1
Received: Frame 2
Sending ACK for frame 2
Received: Frame 3
Sending ACK for frame 3
Received: Frame 4
Sending ACK for frame 4
*/