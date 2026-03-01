## Algorithm: Distance Vector Routing

**Step 1: Start**
Begin the program execution.

**Step 2: Declare Variables and Structures**

* Define a `RoutingTable` structure containing arrays for `distance` and `next_hop`.
* Initialize a 2D array `cost_matrix[MAX_NODES][MAX_NODES]` and an array of structures `rt[MAX_NODES]`.
* Declare counters for nodes ($i, j, k$) and an `update_count` to track changes.

**Step 3: Input Network Topology**

* Read the number of `nodes`.
* Input the **Cost Matrix**:
* If a direct link exists, enter the weight.
* If no direct link exists, enter a large value (`INF`).
* Distance to self is always 0.


**Step 4: Initialize Routing Tables**

* For every router $i$:
* Set the initial distance to destination $j$ as the cost from the `cost_matrix`.
* Set the initial `next_hop` to $j$.


**Step 5: Iterative Update (The Distance Vector Logic)**

* Start a `do-while` loop that continues as long as `update_count > 0`.
* Reset `update_count = 0` at the start of each iteration.
* **Triple Loop Optimization:**
1. For each source router **$i$**.
2. For each destination router **$j$**.
3. For each intermediate neighbor **$k$**.


* **Apply Bellman-Ford Equation:**
* **If** $rt[i].dist[j] > cost\_matrix[i][k] + rt[k].dist[j]$:
* Update $rt[i].dist[j]$ to the new, smaller value.
* Update $rt[i].next\_hop[j]$ to $k$.
* Increment `update_count`.


**Step 6: Display Final Tables**

* For each router, print its final routing table showing the **Destination**, the **Next Hop** (the first step in the shortest path), and the total **Distance**.

**Step 7: Stop**
End the program.
