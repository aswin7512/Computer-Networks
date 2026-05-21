#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

#define PORT 1234
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in client_addr, server_addr;
    char buffer[BUFFER_SIZE] = {0}, *response = "Message Received From Client...";
    socklen_t client_len = sizeof(client_addr);

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    while (1) {
        recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr*) &client_addr, (socklen_t*) &client_len);
        printf("Client: %s\n", buffer);
        sendto(sock, response, strlen(response), 0, (struct sockaddr*)&client_addr, client_len);
        printf("Response sent to Client...\n");
        memset(buffer, 0, BUFFER_SIZE);
    }
    close(sock);
    return 0;
}