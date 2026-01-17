### Algorithm: Selective Repeat Client Implementation

**Step 1: Start**
Begin the program execution.

**Step 2: Initialization**

* **Variables:**
* `sockfd`: UDP socket descriptor.
* `acked`: A boolean array to track the acknowledgment status of each packet. Initialize all indices to `false`.
* `base`: Integer tracking the start of the sender window (oldest unacknowledged packet). Set to 0.
* `ack_num`: Variable to store incoming acknowledgment numbers.


* **Socket Setup:**
* Create a UDP socket using `socket()`.
* Configure the destination `server_addr` (IP "127.0.0.1", Port 8080).


* **Timeout Configuration:**
* Set a `timeval` structure to 1 second.
* Apply this timeout to the socket using `setsockopt`. This allows the program to wake up and retransmit if ACKs stop arriving.



**Step 3: Main Transmission Loop**
Repeat the following steps while `base < TOTAL_PACKETS`:

1. **Sending Phase (Scan Window):**
* Iterate through the current window from `i = base` up to `base + WINDOW_SIZE`.
* **Check:** If `acked[i]` is `false` (meaning the packet has either never been sent or was sent but not yet acknowledged):
* Print "Sending/Retransmitting Packet: i".
* Call `sendto()` to transmit the packet.




2. **Listening Phase (Wait for ACKs):**
* Enter an inner loop to receive responses.
* Call `recvfrom()`.
* **Case A: ACK Received**
* Mark `acked[ack_num] = true`.
* Print "Received ACK for: [ack_num]".
* **Slide Window:** Check if the packet at `base` is now acknowledged.
* **While** `acked[base]` is true: Increment `base`.




* **Case B: Timeout**
* If `recvfrom` returns  (timeout):
* Print "Timeout! Checking window...".
* **Break** the inner listening loop.


* *Note:* Breaking the inner loop returns control to **Step 3.1**, causing the program to re-scan the window and retransmit *only* the missing packets (where `acked` is still false).



**Step 4: Completion**

* Once the loop finishes (all packets acknowledged), print "Success."

**Step 5: Cleanup**

* Close the socket (`close(sockfd)`).

**Step 6: Stop**
End the program.
