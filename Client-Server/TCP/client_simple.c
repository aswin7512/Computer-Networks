#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

#define PORT 1234
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    connect(sock, (struct sockaddr*) &address, sizeof(address));

    printf("Connected to server...\n");
    while (1) {
        printf("You: ");
        fgets(message, BUFFER_SIZE, stdin);

        send(sock, message, strlen(message), 0);
        read(sock, buffer, BUFFER_SIZE);
        printf("Server: %s\n", buffer);
        memset(buffer, 0, BUFFER_SIZE);
        memset(message, 0, BUFFER_SIZE);
    }
    close(sock);
    return 0;
}