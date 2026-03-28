#include <stdio.h>

#define MAX_NODES 20
#define INF 9999

// Structure to hold the routing table for each node
struct RoutingTable {
    unsigned dist[MAX_NODES];
    unsigned next_hop[MAX_NODES];
} rt[MAX_NODES];

int main() {
    int cost_matrix[MAX_NODES][MAX_NODES];
    int nodes, i, j, k, update_count = 0;

    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);

    printf("\nEnter the cost matrix (use %d for infinity/no direct link):\n", INF);
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            scanf("%d", &cost_matrix[i][j]);
            
            // Distance to itself is 0
            if (i == j) {
                cost_matrix[i][i] = 0;
            }
            
            // Initialize the routing table with the cost matrix
            rt[i].dist[j] = cost_matrix[i][j];
            rt[i].next_hop[j] = j; 
        }
    }

    // Distance Vector Routing logic
    do {
        update_count = 0;
        for (i = 0; i < nodes; i++) { // For each node
            for (j = 0; j < nodes; j++) { // For each destination
                for (k = 0; k < nodes; k++) { // Check each possible intermediate neighbor
                    
                    // If going through node k is strictly cheaper than the current known distance
                    if (rt[i].dist[j] > cost_matrix[i][k] + rt[k].dist[j]) {
                        rt[i].dist[j] = cost_matrix[i][k] + rt[k].dist[j];
                        rt[i].next_hop[j] = k; // Update the next hop
                        update_count++;
                    }
                }
            }
        }
    // Continue until no routing tables are updated in a full pass
    } while (update_count != 0);

    // Display the final routing tables
    printf("\n--- Final Routing Tables ---\n");
    for (i = 0; i < nodes; i++) {
        printf("\nRouting Table for Router %d:\n", i + 1);
        printf("Destination\tNext Hop\tDistance\n");
        for (j = 0; j < nodes; j++) {
            printf("%d\t\t%d\t\t%d\n", j + 1, rt[i].next_hop[j] + 1, rt[i].dist[j]);
        }
    }

    return 0;
}

/*
O/P
Enter the number of nodes: 4

Enter the cost matrix (use 9999 for infinity/no direct link):
0 2 4 9999
1 0 3 4
5 4 0 3
9999 2 2 0

--- Final Routing Tables ---

Routing Table for Router 1:
Destination     Next Hop        Distance
1               1               0
2               2               2
3               3               4
4               2               6

Routing Table for Router 2:
Destination     Next Hop        Distance
1               1               1
2               2               0
3               3               3
4               4               4

Routing Table for Router 3:
Destination     Next Hop        Distance
1               1               5
2               2               4
3               3               0
4               4               3

Routing Table for Router 4:
Destination     Next Hop        Distance
1               2               3
2               2               2
3               3               2
4               4               0
*/