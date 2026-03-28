#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
    int total_frames, frames_sent_count = 0;
    int current_frame = 1;

    // Seed the random number generator
    srand(time(NULL));

    printf("--- Stop-and-Wait Protocol Simulation ---\n");
    printf("Enter total number of frames to transmit: ");
    scanf("%d", &total_frames);
    printf("-----------------------------------------\n\n");

    while (current_frame <= total_frames) {
        // 1. Transmit the current single frame
        printf("Sending Frame %d...\n", current_frame);
        frames_sent_count++;

        // 2. Wait for Acknowledgment
        // Randomly simulate success or failure (20% chance of failure)
        int ack_status = rand() % 5; 
        sleep(1); // Small delay to simulate network travel and timeout timers

        if (ack_status != 0) {
            printf("Acknowledgment for Frame %d received.\n\n", current_frame);
            // 3. Move to the next frame only after a successful ACK
            current_frame++; 
        } else {
            printf("--> ERROR: Acknowledgment for Frame %d lost or corrupted!\n", current_frame);
            printf("--> Action: Timeout occurred. Retransmitting Frame %d...\n\n", current_frame);
            // current_frame does NOT increment, forcing the loop to retransmit it
        }
    }

    printf("-----------------------------------------\n");
    printf("Simulation Complete.\n");
    printf("Total original frames: %d\n", total_frames);
    printf("Total frames transmitted (including retransmissions): %d\n", frames_sent_count);

    return 0;
}


/*
O/P
--- Stop-and-Wait Protocol Simulation ---
Enter total number of frames to transmit: 10
-----------------------------------------

Sending Frame 1...
Acknowledgment for Frame 1 received.

Sending Frame 2...
Acknowledgment for Frame 2 received.

Sending Frame 3...
Acknowledgment for Frame 3 received.

Sending Frame 4...
Acknowledgment for Frame 4 received.

Sending Frame 5...
Acknowledgment for Frame 5 received.

Sending Frame 6...
--> ERROR: Acknowledgment for Frame 6 lost or corrupted!
--> Action: Timeout occurred. Retransmitting Frame 6...

Sending Frame 6...
Acknowledgment for Frame 6 received.

Sending Frame 7...
--> ERROR: Acknowledgment for Frame 7 lost or corrupted!
--> Action: Timeout occurred. Retransmitting Frame 7...

Sending Frame 7...
Acknowledgment for Frame 7 received.

Sending Frame 8...
Acknowledgment for Frame 8 received.

Sending Frame 9...
Acknowledgment for Frame 9 received.

Sending Frame 10...
Acknowledgment for Frame 10 received.

-----------------------------------------
Simulation Complete.
Total original frames: 10
Total frames transmitted (including retransmissions): 12
*/