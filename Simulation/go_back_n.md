**Algorithm: Go-Back-N Sliding Window Protocol**

**Step 1: Start** Begin the program execution.
**Step 2: Declare Variables**
*   Define integer variables for `window_size`, `total_frames`, `frames_sent`, and initialize `current_frame` to 1.
*   Seed the random number generator to simulate network unpredictability.
**Step 3: Input Simulation Parameters**
*   Read the `window_size` from the user.
*   Read the `total_frames` to be transmitted.
**Step 4: Transmission Loop**
*   Start a `while` loop that continues as long as `current_frame <= total_frames`.
*   Initialize a local counter `successful_acks = 0` at the start of each iteration.
**Step 5: Send Frames in Current Window**
*   Iterate a loop from `current_frame` up to `current_frame + window_size` (ensuring it doesn't exceed `total_frames`).
*   Print the transmission of each frame and increment the `frames_sent` counter.
**Step 6: Wait for Acknowledgments**
*   Iterate a second loop through the same window of sent frames.
*   Generate a random number to simulate the acknowledgment status.
*   If the ACK is successful: Print a success message and increment `successful_acks`.
*   If the ACK is lost or corrupted: Print an error message, indicate a Go-Back-N retransmission trigger, and `break` the loop to discard any subsequent ACKs in the current window.
**Step 7: Slide the Window**
*   Update `current_frame` by adding the number of `successful_acks` to it.
**Step 8: Display Final Results**
*   Print the total original frames requested and the total frames actually transmitted (including retransmissions).
**Step 9: Stop** End the program.