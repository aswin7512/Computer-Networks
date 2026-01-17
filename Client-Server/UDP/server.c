#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server address configuration
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;           // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Listen on any IP
    server_addr.sin_port = htons(SERVER_PORT);  // Port

    // Bind socket to IP and port
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Server listening on port %d...\n", SERVER_PORT);

    while (1) {
        // Receive message from client
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (n < 0) {
            perror("Receive failed");
            continue;
        }
        buffer[n] = '\0';  // Null-terminate the string
        
        //Exit condition
        if (strcmp(buffer, "exit") == 0) {
            printf("Exit Signal Received, Shutting down server...\n");
            break;
        }
        
        printf("Received from client: %s\n", buffer);

        // Send response to client
        char response[BUFFER_SIZE];
        printf("Enter message: ");
        fgets(response, BUFFER_SIZE, stdin);
        response[strcspn(response, "\n")] = 0;  // Remove newline
        sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&client_addr, client_addr_len);
    }

    close(sockfd);
    return 0;
}

/*
O/P
UDP Server listening on port 12345...
Received from client: Hi
Enter message: Hello
Received from client: How are you?
Enter message: Fine
Exit Signal Received, Shutting down server...
*/