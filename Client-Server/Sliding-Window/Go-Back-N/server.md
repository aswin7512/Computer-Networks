### Algorithm: Go-Back-N Server (with Simulated Loss)

**Step 1: Start**
Begin the program execution.

**Step 2: Initialization**

* **Variables:**
* `sockfd`: UDP socket descriptor.
* `server_addr`, `client_addr`: Address structures.
* `expected_seq`: Integer to track the next required packet sequence number (initialized to 0).


* **Socket Creation:** Create a UDP socket using `socket(AF_INET, SOCK_DGRAM, 0)`.
* **Bind:** Configure `server_addr` (Port defined in headers) and bind the socket.
* **Random Seed:** Initialize the random number generator using `srand(time(NULL))` for simulating packet loss.

**Step 3: Print Status**
Display "Receiver listening..." to indicate readiness.

**Step 4: Receive Loop**
Repeat the following steps while `expected_seq < TOTAL_PACKETS`:

1. **Receive Packet:**
* Call `recvfrom()` to wait for a `Packet` struct from the client.
* Store sender details in `client_addr`.


2. **Simulate Packet Loss:**
* Generate a random number.
* **Check:** If `rand() % 5 == 0` (approx. 20% chance):
* Print "Dropped Packet (Simulated Loss)".
* **Continue** to the start of the loop (Step 4.1), effectively ignoring this packet.




3. **Validate Sequence Number:**
* **If** `p.seq_num` matches `expected_seq`:
* Print "Received Packet X".
* **Prepare ACK:** Create an `AckPacket` with `ack_num` set to `expected_seq`.
* **Send ACK:** Transmit the ACK back to the client using `sendto()`.
* **Increment:** Increase `expected_seq` by 1.


* **Else** (Packet is out of order or duplicate):
* Print "Out of order Packet ignored".
* Do not send an ACK (or send previous ACK depending on specific protocol variant logic, though this code simply ignores it).





**Step 5: Completion**

* Once the loop finishes (all packets received), print "All packets received."

**Step 6: Cleanup**

* Close the socket (`close(sockfd)`).

**Step 7: Stop**
End the program.
