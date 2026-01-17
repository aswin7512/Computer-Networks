### Algorithm: Selective Repeat Server

**Step 1: Start**
Begin the program execution.

**Step 2: Initialization**

* **Variables:**
* `sockfd`: UDP socket descriptor.
* `buffer`: An array of `ReceiverWindow` structures to track the status of each packet (specifically the `received` boolean flag). Initialize all to 0 (false).
* `window_base`: Integer tracking the start of the receiving window. Set to 0.
* `incoming_pkt`: Variable to store the sequence number of the received packet.


* **Socket Setup:**
* Create a UDP socket using `socket(AF_INET, SOCK_DGRAM, 0)`.
* Bind it to `PORT` (8080) and `INADDR_ANY`.



**Step 3: Print Status**
Display "Selective Repeat Server listening..." to indicate readiness.

**Step 4: Receive Loop**
Repeat the following steps while `window_base < TOTAL_PACKETS`:

1. **Receive Packet:**
* Call `recvfrom()` to wait for a packet.
* Store the incoming sequence number in `incoming_pkt`.
* Print "Received Packet: X".


2. **Check Window Validity:**
* **Condition:** Is `incoming_pkt` within the range [`window_base`, `window_base + WINDOW_SIZE - 1`]?


3. **Process Valid Packet:**
* **If Yes (Inside Window):**
* **Mark Received:** Set `buffer[incoming_pkt].received = true`.
* **Send ACK:** Immediately send an ACK containing `incoming_pkt` back to the client. This is an **Individual ACK** (a key feature of Selective Repeat, unlike GBN's cumulative ACK).
* **Print:** "[ACK Sent]".
* **Slide Window:**
* Check the packet at `window_base`.
* **While** `buffer[window_base].received` is true (meaning the oldest expected packet has arrived):
* Increment `window_base`.


* *Note:* This ensures the window only moves forward when the contiguous block of received packets grows.




* **If No (Outside Window):**
* **Print:** "[Ignored - Outside Window]".
* Do nothing else (drop the packet).





**Step 5: Completion**

* The loop ends when `window_base` reaches `TOTAL_PACKETS`.
* (Implicitly) Stop the program.
