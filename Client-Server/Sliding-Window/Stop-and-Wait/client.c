#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024];
    struct timeval tv;
    tv.tv_sec = 2;  // 2 second timeout
    tv.tv_usec = 0;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    // Set receive timeout
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int frame_to_send = 0;
    while (frame_to_send < 5) {
        char msg[20];
        sprintf(msg, "Frame %d", frame_to_send);

        printf("Sending: %s\n", msg);
        sendto(sockfd, msg, strlen(msg) + 1, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

        // Wait for ACK
        if (recvfrom(sockfd, buffer, 1024, 0, NULL, NULL) < 0) {
            printf("Timeout! Resending %s...\n", msg);
        } else {
            printf("Received: %s\n", buffer);
            frame_to_send++;
        }
        sleep(1);
    }

    close(sockfd);
    return 0;
}

/*
O/P
Sending: Frame 0
Received: ACK
Sending: Frame 1
Received: ACK
Sending: Frame 2
Received: ACK
Sending: Frame 3
Received: ACK
Sending: Frame 4
Received: ACK
*/