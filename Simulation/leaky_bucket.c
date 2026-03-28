#include <stdio.h>

int main() {
    int incoming, outgoing, bucket_size, n, store = 0, dropped = 0;

    printf("Enter the bucket capacity: ");
    scanf("%d", &bucket_size);

    printf("Enter the outgoing rate (leak rate): ");
    scanf("%d", &outgoing);

    printf("Enter the number of time intervals to simulate: ");
    scanf("%d", &n);

    // Simulation loop for each time interval
    for (int i = 0; i < n; i++) {
        printf("\n--- Time Interval %d ---\n", i + 1);
        printf("Enter the incoming packet size: ");
        scanf("%d", &incoming);

        // Check if the incoming packets exceed available space
        if (incoming <= (bucket_size - store)) {
            store += incoming;
            printf("Accepted %d packets.\n", incoming);
        } else {
            // Calculate how many packets to drop
            dropped = incoming - (bucket_size - store);
            printf("Bucket overflow! Dropped %d packets.\n", dropped);
            store = bucket_size; // Bucket is now full
        }

        // Leak the packets at the constant outgoing rate
        if (store >= outgoing) {
            store -= outgoing;
            printf("Leaked %d packets. ", outgoing);
        } else {
            printf("Leaked %d packets. ", store);
            store = 0; // Bucket becomes empty
        }

        printf("Current bucket status: %d / %d\n", store, bucket_size);
    }

    // After inputs finish, let the remaining packets in the bucket leak out
    printf("\n--- Processing remaining packets in the bucket ---\n");
    while (store > 0) {
        if (store >= outgoing) {
            store -= outgoing;
            printf("Leaked %d packets. ", outgoing);
        } else {
            printf("Leaked %d packets. ", store);
            store = 0;
        }
        printf("Current bucket status: %d / %d\n", store, bucket_size);
    }

    printf("\nBucket is empty. Simulation complete.\n");

    return 0;
}


/*
O/P
Enter the bucket capacity: 10
Enter the outgoing rate (leak rate): 4
Enter the number of time intervals to simulate: 3

--- Time Interval 1 ---
Enter the incoming packet size: 9
Accepted 9 packets.
Leaked 4 packets. Current bucket status: 5 / 10

--- Time Interval 2 ---
Enter the incoming packet size: 7
Bucket overflow! Dropped 2 packets.
Leaked 4 packets. Current bucket status: 6 / 10

--- Time Interval 3 ---
Enter the incoming packet size: 2
Accepted 2 packets.
Leaked 4 packets. Current bucket status: 4 / 10

--- Processing remaining packets in the bucket ---
Leaked 4 packets. Current bucket status: 0 / 10

Bucket is empty. Simulation complete.
*/