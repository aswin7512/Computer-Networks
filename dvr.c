#include<stdio.h>

#define MAX_NODES 20
#define INF 999

struct RoutingTable {
    int dist[MAX_NODES];
    int next_hop[MAX_NODES];
} rt[MAX_NODES];

int main() {
    int nodes, update;
    int cost_matrix[MAX_NODES][MAX_NODES];
    printf("Enter No. of Nodes: ");
    scanf("%d", &nodes);

    printf("Enter Cost Matrix: ");
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            scanf("%d", &cost_matrix[i][j]);
            if (i == j)
                cost_matrix[i][j] = 0;
            rt[i].dist[j] = cost_matrix[i][j];
            rt[i].next_hop[j] = j;
        }
    }

    do {
        update = 0;
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                for (int k = 0; k < nodes; k++) {
                    if (rt[i].dist[j] > rt[i].dist[k] + rt[k].dist[j]){
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].next_hop[j] = k;
                        update++;
                    }
                }
            }
        }
    } while (update > 0);

    for (int i = 0; i < nodes; i++) {
        printf("\nRouter %d\n", i+1);
        printf("%10s%10s%10s\n", "Sno.", "Distance", "Next Hop");
        for (int j = 0; j < nodes; j++) {
            printf("%10d%10d%10d\n", j+1, rt[i].dist[j], rt[i].next_hop[j]+1);
        }
    }
}