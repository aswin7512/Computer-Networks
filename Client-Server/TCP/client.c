#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE];

    // 1. Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // 2. Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    printf("Connected to server. Type 'exit' to quit.\n");

    // 3. Communication loop
    while(1) {
        printf("You: ");
        fgets(message, BUFFER_SIZE, stdin);
        
        // Remove trailing newline character from fgets
        message[strcspn(message, "\n")] = 0;

        // Send message to server
        send(sock, message, strlen(message), 0);

        if (strncmp(message, "exit", 4) == 0) {
            printf("Exiting...\n");
            break;
        }

        // Read response from server
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(sock, buffer, BUFFER_SIZE);
        printf("Server: %s\n", buffer);
    }

    // 4. Close the socket
    close(sock);
    return 0;
}

/*
O/P
Connected to server. Type 'exit' to quit.
You: Hi
Server: Message received by server
You: Hello
Server: Message received by server
You: How are you?
Server: Message received by server
You: exit
Exiting...
*/