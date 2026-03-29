#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Define states for our frames
#define NOT_SENT 0
#define SENT 1
#define ACKED 2

int main() {
    int window_size, total_frames, frames_sent_count = 0;
    int base = 1;

    // Seed the random number generator
    srand(time(NULL));

    printf("--- Selective Repeat Protocol Simulation ---\n");
    printf("Enter window size: ");
    scanf("%d", &window_size);
    printf("Enter total number of frames to transmit: ");
    scanf("%d", &total_frames);
    printf("--------------------------------------------\n\n");

    // Dynamically allocate an array to track the status of each frame
    // Initialized to 0 (NOT_SENT) via calloc
    int *frames = (int *)calloc(total_frames + 1, sizeof(int));
    
    if (frames == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    while (base <= total_frames) {
        // 1. Transmit or Retransmit frames within the current window
        for (int i = base; i < base + window_size && i <= total_frames; i++) {
            if (frames[i] == NOT_SENT) {
                printf("Sending Frame %d...\n", i);
                frames[i] = SENT;
                frames_sent_count++;
            }
        }

        // 2. Wait for Acknowledgments for all 'SENT' frames in the window
        for (int i = base; i < base + window_size && i <= total_frames; i++) {
            if (frames[i] == SENT) {
                // Randomly simulate success or failure (20% chance of failure)
                int ack_status = rand() % 5; 
                sleep(1); // Small delay to simulate network travel time

                if (ack_status != 0) {
                    printf("Acknowledgment for Frame %d received.\n", i);
                    frames[i] = ACKED; // Mark as successfully received
                } else {
                    printf("--> ERROR: Acknowledgment for Frame %d lost or corrupted!\n", i);
                    printf("--> Action: Tagging Frame %d for Selective Retransmission.\n", i);
                    frames[i] = NOT_SENT; // Reset status so it gets sent again in the next loop
                }
            }
        }

        printf("\n");
        
        // 3. Slide the window forward
        // The window only slides if the 'base' (oldest) frame has been acknowledged
        while (base <= total_frames && frames[base] == ACKED) {
            base++;
        }
    }

    printf("--------------------------------------------\n");
    printf("Simulation Complete.\n");
    printf("Total original frames: %d\n", total_frames);
    printf("Total frames transmitted (including retransmissions): %d\n", frames_sent_count);

    free(frames); // Clean up allocated memory
    return 0;
}


/*
O/P
--- Selective Repeat Protocol Simulation ---
Enter window size: 4
Enter total number of frames to transmit: 10
--------------------------------------------

Sending Frame 1...
Sending Frame 2...
Sending Frame 3...
Sending Frame 4...
Acknowledgment for Frame 1 received.
Acknowledgment for Frame 2 received.
--> ERROR: Acknowledgment for Frame 3 lost or corrupted!
--> Action: Tagging Frame 3 for Selective Retransmission.
Acknowledgment for Frame 4 received.

Sending Frame 3...
Sending Frame 5...
Sending Frame 6...
--> ERROR: Acknowledgment for Frame 3 lost or corrupted!
--> Action: Tagging Frame 3 for Selective Retransmission.
Acknowledgment for Frame 5 received.
--> ERROR: Acknowledgment for Frame 6 lost or corrupted!
--> Action: Tagging Frame 6 for Selective Retransmission.

Sending Frame 3...
Sending Frame 6...
Acknowledgment for Frame 3 received.
Acknowledgment for Frame 6 received.

Sending Frame 7...
Sending Frame 8...
Sending Frame 9...
Sending Frame 10...
Acknowledgment for Frame 7 received.
Acknowledgment for Frame 8 received.
Acknowledgment for Frame 9 received.
--> ERROR: Acknowledgment for Frame 10 lost or corrupted!
--> Action: Tagging Frame 10 for Selective Retransmission.

Sending Frame 10...
Acknowledgment for Frame 10 received.

--------------------------------------------
Simulation Complete.
Total original frames: 10
Total frames transmitted (including retransmissions): 14
*/