#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *response = "Message received by server";

    // 1. Create socket file descriptor
    // AF_INET = IPv4, SOCK_STREAM = TCP
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Bind the socket to the network address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Bind to any available interface
    address.sin_port = htons(PORT);       // Host to Network Short

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 3. Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // 4. Accept a connection
    // This blocks the process until a client connects
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 5. Communication loop
    while(1) {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        
        if (valread <= 0) {
            printf("Client disconnected.\n");
            break;
        }

        printf("Client: %s\n", buffer);

        // Send response to client
        send(new_socket, response, strlen(response), 0);
        printf("Response sent to client.\n");
        
        // Exit condition
        if (strncmp(buffer, "exit", 4) == 0) {
            printf("Exit signal received. Shutting down.\n");
            break;
        }
    }

    // 6. Close the socket
    close(new_socket);
    close(server_fd);
    return 0;
}

/*
O/P
Server listening on port 8080...
Client: Hi
Response sent to client.
Client: Hello
Response sent to client.
Client: How are you?
Response sent to client.
Client: exit
Response sent to client.
Exit signal received. Shutting down.
*/