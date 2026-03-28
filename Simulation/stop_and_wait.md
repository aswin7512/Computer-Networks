**Algorithm: Stop-and-Wait Protocol**

**Step 1: Start** Begin the program execution.
**Step 2: Declare Variables**
*   Define integer variables for `total_frames` and `frames_sent_count`.
*   Initialize `current_frame` to 1.
*   Seed the random number generator.
**Step 3: Input Simulation Parameters**
*   Read the `total_frames` to transmit.
**Step 4: Transmission Loop**
*   Start a `while` loop that continues as long as `current_frame <= total_frames`.
**Step 5: Send Single Frame**
*   Print the transmission message for `current_frame`.
*   Increment the `frames_sent_count`.
**Step 6: Wait for Acknowledgment (Timeout Logic)**
*   Generate a random number to simulate the acknowledgment status and timeout timer.
*   If the ACK is successful: Print a success message and increment `current_frame` by 1 to move to the next sequential frame.
*   If the ACK is lost (Timeout): Print an error message and a retransmission notice. Do not increment `current_frame`, forcing the loop to resend the exact same frame on the next iteration.
**Step 7: Display Final Results**
*   Print the total original frames and the total frames transmitted (including any retransmissions caused by timeouts).
**Step 8: Stop** End the program.