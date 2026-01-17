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
    struct sockaddr_in server_addr;
    socklen_t addr_len = sizeof(server_addr);

    // Create UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Server address configuration
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP

    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;  // Remove newline

        // Send message to server
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, addr_len);
        
        //Exit condition
        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting client...\n");
            break;
        }

        // Receive response from server
        int n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
        if (n < 0) {
            perror("Receive failed");
            continue;
        }
        buffer[n] = '\0';
        printf("Server response: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}

/*
O/P
Enter message: Hi
Server response: Hello
Enter message: How are you?
Server response: Fine
Enter message: exit
Exiting client...
*/