#include<stdio.h>

int main() {
    int bucket_size, inc, otg, store=0, drop=0, n;
    printf("Enter Bucket Capacity, Outgoing rate, No. of Time intervals: ");
    scanf("%d %d %d", &bucket_size, &otg, &n);

    for (int i = 0; i < n; i++) {
        printf("\nEnter Incoming packet size for Time Interval %d: ", i+1);
        scanf("%d", &inc);
        drop = 0;
        if (inc > (bucket_size - store)) {
            drop = inc - (bucket_size - store);
            printf("Bucket Overflow!!! Dropped %d Packets...\n", drop);
        }
        store += inc - drop;
        printf("Accepted %d Packets\n", inc-drop);

        if (store < otg) {
            printf("Leaked %d Packets\n", store);
            store = 0;
        } else {
            printf("Leaked %d Packets\n", otg);
            store -= otg;
        }
        printf("Bucket Status: %d/%d\n", store, bucket_size);
    }

    printf("Processing Remaining Packets...\n");
    while (store > 0) {
        if (store < otg) {
            printf("Leaked %d Packets\n", store);
            store = 0;
        } else {
            printf("Leaked %d Packets\n", otg);
            store -= otg;
        }
        printf("Bucket Status: %d/%d\n", store, bucket_size);
    }
    return 0;
}