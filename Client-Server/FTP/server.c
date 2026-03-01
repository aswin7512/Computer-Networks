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
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    FILE *file;

    // 1. Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Configure server address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Listen on all available interfaces
    address.sin_port = htons(PORT);

    // 3. Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 4. Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("FTP Server listening on port %d...\n", PORT);

    // 5. Accept a connection from a client
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Client connected.\n");

    // 6. Receive the requested filename from the client
    recv(new_socket, buffer, BUFFER_SIZE, 0);
    printf("Client requested file: %s\n", buffer);

    // 7. Open the file and send it
    file = fopen(buffer, "rb");
    if (file == NULL) {
        char *error_msg = "ERROR: File not found.";
        send(new_socket, error_msg, strlen(error_msg), 0);
        printf("File not found. Error message sent to client.\n");
    } else {
        printf("Sending file...\n");
        int bytes_read;
        // Read the file in chunks and send through the socket
        while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            send(new_socket, buffer, bytes_read, 0);
        }
        fclose(file);
        printf("File transfer complete.\n");
    }

    // 8. Close sockets
    close(new_socket);
    close(server_fd);
    return 0;
}