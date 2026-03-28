**Algorithm: Selective Repeat Sliding Window Protocol**

**Step 1: Start** Begin the program execution.

**Step 2: Declare Variables and Structures**

*   Define constants for frame states: `NOT_SENT` (0), `SENT` (1), and `ACKED` (2).
*   Declare integer variables for `window_size`, `total_frames`, `frames_sent_count`, and initialize `base` to 1.
*   Seed the random number generator.

**Step 3: Input Simulation Parameters**

*   Read the `window_size`.
*   Read the `total_frames` to transmit.

**Step 4: Initialize Frame Array**

*   Dynamically allocate an integer array `frames` of size `total_frames + 1` to track individual frame states.
*   Initialize all elements in the `frames` array to `NOT_SENT`.

**Step 5: Transmission Loop**

*   Start a `while` loop that continues as long as `base <= total_frames`.

**Step 6: Send or Retransmit Frames in Window**

*   Iterate from `base` to `base + window_size` (without exceeding `total_frames`).
*   Check the state of each frame. If it is `NOT_SENT`: 
    *   Print a transmission message.
    *   Update the frame's state to `SENT`.
    *   Increment `frames_sent_count`.

**Step 7: Wait for Acknowledgments**

*   Iterate through the current window specifically for frames marked as `SENT`.
*   Generate a random number to simulate the acknowledgment status.
*   If the ACK is successful: Update that specific frame's state in the array to `ACKED`.
*   If the ACK is lost: Print an error message and tag the frame for selective retransmission by resetting its state back to `NOT_SENT`.

**Step 8: Slide the Window**

*   Start a nested `while` loop that increments `base` as long as `base <= total_frames` AND the state of `frames[base]` is `ACKED`.

**Step 9: Display Final Results**

*   Print the total original frames and the total frames transmitted.
*   Free the dynamically allocated memory for the `frames` array.

**Step 10: Stop** End the program.