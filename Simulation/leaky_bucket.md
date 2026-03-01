## Algorithm: Leaky Bucket Traffic Shaping

**Step 1: Start**
Begin the program execution.

**Step 2: Declare and Initialize Variables**

* `bucket_size`: The maximum capacity of the "bucket" (buffer).
* `outgoing`: The constant rate at which packets leave the bucket (leak rate).
* `n`: The number of time intervals to simulate.
* `store`: Current amount of data in the bucket (initially 0).
* `incoming`: Amount of data arriving at a specific interval.

**Step 3: Get User Configuration**

* Input the maximum **Bucket Capacity**.
* Input the **Leak Rate** (outgoing rate).
* Input the **Number of intervals** for the simulation.

**Step 4: Simulation Loop (For each interval)**
For $i = 1$ to $n$:

1. **Input Incoming Data:** Read the `incoming` packet size for the current second/interval.
2. **Admission Control:**
* **If** `incoming` $\le$ (`bucket_size` - `store`):
* Accept the packets and add them to `store`.


* **Else**:
* Calculate `dropped` packets ($incoming - (bucket\_size - store)$).
* Set `store` to `bucket_size` (bucket becomes full).
* Print the number of packets dropped due to overflow.


3. **Leak Out Process:**
* **If** `store` $\ge$ `outgoing`:
* Subtract `outgoing` from `store`.


* **Else**:
* Empty the bucket by setting `store = 0`.


4. **Status Update:** Display the current packets remaining in the bucket.

**Step 5: Empty the Remaining Bucket**

* Create a loop that runs while `store > 0`.
* Continue subtracting the `outgoing` rate (or the remaining balance if less than the rate) until the bucket is completely empty.
* Display the bucket status after each step.

**Step 6: Stop**
Print "Simulation complete" and end the program.
