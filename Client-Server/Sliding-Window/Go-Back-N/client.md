### Algorithm: Go-Back-N Client Implementation

**Step 1: Start**
Begin the program execution.

**Step 2: Initialization**

* **Variables:**
* `sockfd`: UDP socket descriptor.
* `base`: Integer tracking the start of the window (oldest unacknowledged packet). Set to 0.
* `next_seq`: Integer tracking the next sequence number to send. Set to 0.


* **Socket Setup:**
* Create a UDP socket (`AF_INET`, `SOCK_DGRAM`).
* Configure the target `server_addr`.


* **Timeout Configuration:**
* Create a `timeval` structure setting the timeout duration (`TIMEOUT_SEC`).
* Apply this timeout to the socket using `setsockopt` (Option: `SO_RCVTIMEO`). This ensures `recvfrom` does not block forever if packets are lost.



**Step 3: Transmission Loop**
Repeat the following steps while `base < TOTAL_PACKETS` (until all packets are acknowledged):

1. **Sending Window (Inner Loop):**
* **Condition:** While the window is not full (`next_seq < base + WINDOW_SIZE`) **AND** there are still packets to send (`next_seq < TOTAL_PACKETS`):
* **Create Packet:** Assign `seq_num = next_seq` and fill payload.
* **Send:** Transmit packet using `sendto`.
* **Log:** Print "Sent Packet X".
* **Increment:** Increase `next_seq` by 1.




2. **Wait for Acknowledgement:**
* Call `recvfrom` to listen for an ACK from the receiver.


3. **Process Result:**
* **Case A: ACK Received (Success)**
* **Check:** If `ack.ack_num >= base`:
* **Slide Window:** Update `base = ack.ack_num + 1`. This uses **Cumulative ACKs** (acknowledging packet X implies all packets up to X are received).


* **Case B: Timeout (Packet Loss/Delay)**
* **Log:** Print "Timeout! Resending from Packet [base]".
* **Go Back N:** Reset `next_seq` to `base`.
* *Note:* In the next iteration of the loop, Step 3.1 will naturally re-send all packets starting from the reset `next_seq`.





**Step 4: Completion**

* Once the loop finishes (meaning `base` has reached `TOTAL_PACKETS`), print "All packets sent and acknowledged."

**Step 5: Cleanup**

* Close the socket (`close(sockfd)`).

**Step 6: Stop**
End the program.