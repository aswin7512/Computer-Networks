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
    char filename[256];
    FILE *file;

    // 1. Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 2. Convert IPv4 addresses from text to binary form (localhost here)
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // 3. Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("Connected to the FTP Server.\n");

    // 4. Request a file
    printf("Enter the name of the file you want to download: ");
    scanf("%s", filename);
    send(sock, filename, strlen(filename), 0);

    // 5. Receive the file data and save it
    int bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
    
    // Check if the server sent an error message
    if (strncmp(buffer, "ERROR:", 6) == 0) {
        printf("%s\n", buffer);
    } else {
        // Open a new file to save the downloaded content
        char new_filename[300];
        snprintf(new_filename, sizeof(new_filename), "downloaded_%s", filename);
        file = fopen(new_filename, "wb");
        
        if (file == NULL) {
            perror("Could not create local file");
            return -1;
        }

        // Write the first chunk
        fwrite(buffer, 1, bytes_received, file);

        // Continue receiving and writing until the connection is closed by the server
        while ((bytes_received = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
            fwrite(buffer, 1, bytes_received, file);
        }

        printf("File downloaded successfully as '%s'.\n", new_filename);
        fclose(file);
    }

    // 6. Close the socket
    close(sock);
    return 0;
}