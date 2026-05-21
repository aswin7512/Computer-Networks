#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

#define PORT 1234
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE] = {0}, response[BUFFER_SIZE] = {0};

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        printf("You: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, addr_len);
        recvfrom(sock, response, BUFFER_SIZE, 0, NULL, NULL);
        printf("Server: %s\n", response);
        memset(buffer, 0, BUFFER_SIZE);
        memset(response, 0, BUFFER_SIZE);
    }
    close(sock);
    return 0;
}