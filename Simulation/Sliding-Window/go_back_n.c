#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    int window_size, total_frames, frames_sent = 0;
    int current_frame = 1;

    // Seed the random number generator
    srand(time(NULL));

    printf("--- Go-Back-N Protocol Simulation ---\n");
    printf("Enter window size: ");
    scanf("%d", &window_size);
    printf("Enter total number of frames to transmit: ");
    scanf("%d", &total_frames);
    printf("-------------------------------------\n\n");

    while (current_frame <= total_frames) {
        int successful_acks = 0;

        // 1. Transmit frames within the current window limit
        for (int k = current_frame; k < current_frame + window_size && k <= total_frames; k++) {
            printf("Sending Frame %d...\n", k);
            frames_sent++;
        }

        // 2. Wait for Acknowledgments
        for (int k = current_frame; k < current_frame + window_size && k <= total_frames; k++) {
            // Randomly simulate success or failure (20% chance of failure)
            int ack_status = rand() % 5; 
            sleep(1); // Small delay to simulate network travel time

            if (ack_status != 0) {
                printf("Acknowledgment for Frame %d received.\n", k);
                successful_acks++;
            } else {
                printf("--> ERROR: Acknowledgment for Frame %d lost or corrupted!\n", k);
                printf("--> Action: Go-Back-N triggered. Retransmitting from Frame %d...\n", k);
                break; // Stop waiting for further ACKs, retransmit the whole window starting here
            }
        }

        printf("\n");
        
        // 3. Slide the window forward by the number of sequential successful ACKs
        current_frame = current_frame + successful_acks; 
    }

    printf("-------------------------------------\n");
    printf("Simulation Complete.\n");
    printf("Total original frames: %d\n", total_frames);
    printf("Total frames transmitted (including retransmissions): %d\n", frames_sent);

    return 0;
}



/*
O/P
--- Go-Back-N Protocol Simulation ---
Enter window size: 4
Enter total number of frames to transmit: 10
-------------------------------------

Sending Frame 1...
Sending Frame 2...
Sending Frame 3...
Sending Frame 4...
Acknowledgment for Frame 1 received.
Acknowledgment for Frame 2 received.
Acknowledgment for Frame 3 received.
--> ERROR: Acknowledgment for Frame 4 lost or corrupted!
--> Action: Go-Back-N triggered. Retransmitting from Frame 4...

Sending Frame 4...
Sending Frame 5...
Sending Frame 6...
Sending Frame 7...
Acknowledgment for Frame 4 received.
--> ERROR: Acknowledgment for Frame 5 lost or corrupted!
--> Action: Go-Back-N triggered. Retransmitting from Frame 5...

Sending Frame 5...
Sending Frame 6...
Sending Frame 7...
Sending Frame 8...
Acknowledgment for Frame 5 received.
Acknowledgment for Frame 6 received.
Acknowledgment for Frame 7 received.
Acknowledgment for Frame 8 received.

Sending Frame 9...
Sending Frame 10...
Acknowledgment for Frame 9 received.
Acknowledgment for Frame 10 received.

-------------------------------------
Simulation Complete.
Total original frames: 10
Total frames transmitted (including retransmissions): 14
*/